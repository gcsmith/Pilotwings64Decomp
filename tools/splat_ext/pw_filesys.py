from pathlib import Path

import struct
import yaml
from splat.util import options
from splat.segtypes.segment import Segment
from splat.segtypes.linker_entry import LinkerEntry

class N64SegPw_filesys(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(
            rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml
        )
        self.align = 0x10
        self.fs_path = "filesys"

    # example parser for ADAT form. could be moved to own class
    def parse_ADAT(self, formBytes: bytes) -> dict:
        pw64CharMap = {
            0x00: '0', 0x01: '1', 0x02: '2', 0x03: '3', 0x04: '4',
            0x05: '5', 0x06: '6', 0x07: '7', 0x08: '8', 0x09: '9',
            0x0A: 'A', 0x0B: 'B', 0x0C: 'C', 0x0D: 'D', 0x0E: 'E',
            0x0F: 'F', 0x10: 'G', 0x11: 'H', 0x12: 'I', 0x13: 'J',
            0x14: 'K', 0x15: 'L', 0x16: 'M', 0x17: 'N', 0x18: 'O',
            0x19: 'P', 0x1A: 'Q', 0x1B: 'R', 0x1C: 'S', 0x1D: 'T',
            0x1E: 'U', 0x1F: 'V', 0x20: 'W', 0x21: 'X', 0x22: 'Y',
            0x23: 'Z', 0x24: 'a', 0x25: 'b', 0x26: 'c', 0x27: 'd',
            0x28: 'e', 0x29: 'f', 0x2A: 'g', 0x2B: 'h', 0x2C: 'i',
            0x2D: 'j', 0x2E: 'k', 0x2F: 'l', 0x30: 'm', 0x31: 'n',
            0x32: 'o', 0x33: 'p', 0x34: 'q', 0x35: 'r', 0x36: 's',
            0x37: 't', 0x38: 'u', 0x39: 'v', 0x3A: 'w', 0x3B: 'x',
            0x3C: 'y', 0x3D: 'z', 0x3E: '-', 0x3F: '#', 0x40: '<',
            0x41: '>', 0x42: ' ', 0x43: '\"', 0x44: '(', 0x45: ')',
            0x46: '*', 0x47: '&', 0x48: ',',  0x49: '.', 0x4A: '/',
            0x4B: '!', 0x4C: '?', 0x4D: '\'', 0x4E: '＞', 0x4F: ':',
            0xD4: '%d',
            0xFE: '\n', 0xFD: '\t'
        }
        def encode(data: bytes) -> str:
            res = ""
            isBold = False
            for code, in struct.iter_unpack(">H", data):
                if code >= 0x60 and code < 0xB0:
                    code -= 0x60
                    if not isBold:
                        res += "{"
                    isBold = True
                elif isBold:
                    res += "}"
                    isBold = False
                if code in pw64CharMap:
                    res += pw64CharMap[code]
                elif code == 0xFF: # terminator
                    break
                else:
                    res += f"%x{code:04x}"
            if isBold:
                res += "}"
            return res
        adat = {'pad_count': 0, 'entries': []}
        ftag, flen, tag = struct.unpack(">4s L 4s", formBytes[:0xC])
        ftag = ftag.decode("utf-8")
        tag = tag.decode("utf-8")
        assert ftag == "FORM", f"Expected 'FORM', got ${ftag}"
        assert tag == "ADAT", f"Expected 'ADAT', got ${tag}"
        aBytes = formBytes[0x8:]
        idx = 4
        aSize = 0
        aName = ""
        while idx < flen:
            atag, alen = struct.unpack(">4s L", aBytes[idx:idx+8])
            idx += 8
            if atag == b'PAD ':
                adat['pad_count'] += 1
            elif atag == b'SIZE':
                aSize, = struct.unpack(">L", aBytes[idx:idx+4])
            elif atag == b'NAME':
                aName = aBytes[idx:idx+alen].decode("utf-8").rstrip('\x00')
            elif atag == b'DATA':
                aDataRaw = aBytes[idx:idx+alen]
                aData = encode(aDataRaw)
                adat['entries'].append({'name': aName, 'data': aData})
            idx += alen
        assert len(adat['entries']) == aSize, f"Mismatch length: {len(adat['entries'])} != {aSize}"
        return adat

    def scan(self, rom_bytes):
        fsFiles = []
        idx = self.rom_start
        # iterate over filesystem 'FORM' entries and store their tags and offsets
        while idx + 0xC < self.rom_end:
            ftag, length, tag = struct.unpack(">4s L 4s", rom_bytes[idx:idx+0xC])
            ftag = ftag.decode("utf-8")
            tag = tag.decode("utf-8")
            assert ftag == "FORM", f"Expected 'FORM', got ${ftag}"
            form = {'tag': tag, 'length': length, 'offset': idx}
            fsFiles.append(form)
            idx += 8 + length
        self.fs_files = fsFiles

    def split(self, rom_bytes):
        extractors = {
            'ADAT': self.parse_ADAT
        }
        path = options.opts.asset_path / self.dir / self.fs_path
        path.mkdir(parents=True, exist_ok=True)
        # split out raw binary blobs of each FORM
        for form in self.fs_files:
            basename = f"FORM_{form['tag']}_{form['offset']:06X}"
            start = form['offset']
            end = start + form['length'] + 8
            formData = rom_bytes[start:end]
            if form['tag'] in extractors:
                fname = basename + ".yaml"
                fpath = options.opts.asset_path / self.dir / self.fs_path / fname
                fdata = extractors[form['tag']](formData)
                with open(fpath, "w", newline="\n") as fout:
                    yaml.dump(fdata, fout, allow_unicode=True, sort_keys=False)
            else:
                fname = basename + ".raw"
                fpath = options.opts.asset_path / self.dir / self.fs_path / fname
                with open(fpath, 'wb') as fout:
                    fout.write(formData)

    def get_linker_entries(self):
        return [
            LinkerEntry(
                self,
                [options.opts.asset_path / self.dir / f"{self.name}.bin"],
                options.opts.asset_path / self.dir / f"{self.name}",
                self.get_linker_section_order(),
                self.get_linker_section_linksection(),
                self.is_noload(),
            )
        ]
