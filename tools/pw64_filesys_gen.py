#!/bin/env python3

import crunch64
import hashlib
import struct
import yaml
import pw64.filesys as pw64_fs

def read_table(tablePath):
    return yaml.safe_load(open(tablePath, 'r'))

# wrapper for matching compression workaround
def mio0_compress(data: bytes, mio0Info: dict) -> bytes:
    def PUT_BIT(buf, bit, val):
        mask = 1 << (7 - (bit % 8))
        offset = bit // 8
        while len(buf) < offset + 1:
            buf.append(0)
        buf[offset] = (buf[offset] & ~(mask)) | (mask if val else 0)

    if not mio0Info or hashlib.sha1(data).hexdigest() != mio0Info['sha1sum']:
        cData = crunch64.mio0.compress(data)
    else:
        uBuf = b''
        cBuf = b''
        flags = []
        offset = 0x0
        bitIdx = 0
        for m in mio0Info['comp_blocks']:
            uLen = m['file_offset'] - offset
            uBuf += data[offset:offset + uLen]
            offset += uLen
            for i in range(uLen):
                PUT_BIT(flags, bitIdx, 1)
                bitIdx += 1
            windowInfo = ((m['length'] - 3) << 12) | (m['offset'] - 1)
            cBuf += struct.pack(">H", windowInfo)
            PUT_BIT(flags, bitIdx, 0)
            bitIdx += 1
            offset += m['length']
        uLen = len(data) - offset
        uBuf += data[offset:offset + uLen]
        offset += uLen
        for i in range(uLen):
            PUT_BIT(flags, bitIdx, 1)
            bitIdx += 1

        bitLength = (bitIdx + 7) // 8
        compOffset = (((0x10 + bitLength) + 3) // 4) * 4
        uncompOffset = compOffset + len(cBuf)
        cData = b'MIO0' + struct.pack(">L", len(data)) + struct.pack(">L", compOffset) + struct.pack(">L", uncompOffset)
        cData += bytes(flags) + cBuf + uBuf
    return cData

def generate_PAD(padCount: int) -> bytes:
    padding = b''
    for _ in range(padCount):
        padding += struct.pack(">4s L L", "PAD ".encode("utf-8"), 4, 0)
    return padding

def generate_bins(table: dict, fileDir: str, tableFile: str, filesysFile: str):
    # 1. output filesystem binary and accumulate sizes
    with open(filesysFile, 'wb') as fsBin:
        offset = 0
        for form in table["contents"]:
            filePath = fileDir + "/" + form["file"]
            if form["file"].endswith(".raw"):
                formData = open(filePath, "rb").read()
            elif form["file"].endswith(".yaml"):
                assert hasattr(pw64_fs, form["tag"]), f"Unknown tag '{form['tag']}"
                generator = getattr(pw64_fs, form["tag"])
                fileDat = yaml.safe_load(open(filePath, 'r'))
                formData = bytes(generator.from_dict(fileDat))
            else:
                formData = b''
            formLen = len(formData)
            if formLen != form['length']:
                print(f"Warning: length mismatch {form['file']} {form['length']} != {formLen}")
            form['length'] = formLen
            offset += formLen
            fsBin.write(formData)

    # 2. generate filetable, compress, and output file
    tableData = bytes()
    for form in table['contents']:
        tableData += struct.pack(">4s L", form['tag'].encode("utf-8"), form['length'])
    tableLen = len(tableData)

    # until matching MIO0 compression is found, use workaround instead of crunch64
    # cTableData = crunch64.mio0.compress(tableData)
    cTableData = mio0_compress(tableData, table['mio0_matching_info'])

    cTableLen = (((len(cTableData) + 8) + 3) // 4) * 4 # round up to 4-byte boundary
    uvRm = struct.pack(">4s", "UVRM".encode("utf-8"))
    uvRm += generate_PAD(table['pad_count'])
    uvRm += struct.pack(">4s L", "GZIP".encode("utf-8"), cTableLen)
    uvRm += struct.pack(">4s L", "TABL".encode("utf-8"), tableLen)
    uvRm += cTableData
    uvRmLen = ((len(uvRm) + 3) // 4) * 4 # round up to 4 byte boundary
    with open(tableFile, 'wb') as tableBin:
        tableBin.write(struct.pack(">4s L", "FORM".encode("utf-8"), uvRmLen))
        tableBin.write(uvRm)

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--table", "-t", action="store", default='./bin/filesys/filetable.yaml')
    parser.add_argument("--dir", "-d", action="store", default='./bin/filesys')
    args = parser.parse_args()
    table = read_table(args.table)
    generate_bins(table, args.dir, 'bin/filetable.bin', 'bin/filesys.bin')

if __name__ == "__main__":
    main()
