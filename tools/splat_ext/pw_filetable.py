import crunch64
import hashlib
import struct
import yaml
from splat.util import options
from splat.segtypes.segment import Segment
from splat.segtypes.linker_entry import LinkerEntry

class N64SegPw_filetable(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(
            rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml
        )
        self.align = 0x10
        self.fs_path = "filesys"

    # MIO0 compression doesn't yet match Paradigm's algo
    # collect compressed window information to be used during rebuild
    def mio0_matching_info(self, mio0Data: bytes) -> list:
        mio0Info = []
        magic = mio0Data[:4]
        assert magic == b'MIO0', f"Expected 'MIO0', got {magic}"
        dLen, cOff, uOff = struct.unpack('>LLL', mio0Data[0x4:0x10])
        flags = mio0Data[0x10:cOff]
        flagIdx = 0
        outSize = 0
        while outSize < dLen:
            flagOff = flagIdx // 8
            flagBit = 1 << (7 - (flagIdx % 8))
            flagIdx += 1
            if flags[flagOff] & flagBit != 0:
                outSize += 1
            else: # compressed
                windowInfo, = struct.unpack('>H', mio0Data[cOff:cOff+2])
                cOff += 2
                winOff = (windowInfo & 0x0FFF) + 1
                winLen = (windowInfo >> 12) + 3
                mio0Info.append({'file_offset': outSize, 'offset': winOff, 'length': winLen})
                outSize += winLen
        return mio0Info

    def parse_table(self, rom_bytes: bytes, idx: int) -> dict:
        formTag, formLen = struct.unpack(">4s L", rom_bytes[idx:idx+8])
        print(f"form 0x{idx:x} 0x{formLen:x}")
        assert formTag == b"FORM", f"Expected 'FORM', got {formTag}"
        idx += 8
        fsDataStart = (((idx + formLen) + 15) // 16) * 16
        rtag, = struct.unpack(">4s", rom_bytes[idx:idx+4])
        assert rtag == b"UVRM", f"Expected 'UVRM', got {rtag}"
        idx += 4
        table = {
            'tag': formTag.decode("utf-8"),
            'length': formLen,
            'type': rtag.decode("utf-8"),
            'pad_count': 0,
            'contents': []
        }
        cur = 0
        fsDataOffset = fsDataStart
        while cur < formLen:
            tag, length = struct.unpack(">4s L", rom_bytes[cur+idx:cur+idx+8])
            cur += 8
            data = rom_bytes[cur+idx:cur+idx+length]
            # compressed data, unwrap MIO0 compression first
            if tag == b"GZIP":
                tag, dlength = struct.unpack(">4s L", rom_bytes[cur+idx:cur+idx+8])
                cur += 8
                cdata = rom_bytes[cur+idx:cur+idx+length-8]
                data = crunch64.mio0.decompress(cdata)
                assert len(data) == dlength, f"Expected {len(data)} == {dlength}"
                table['mio0_matching_info'] = {
                    'sha1sum': hashlib.sha1(data).hexdigest(),
                    'comp_blocks': self.mio0_matching_info(cdata)
                }
            if tag == b"PAD ":
                table['pad_count'] += 1
            elif tag == b"TABL":
                for entryTag, entryLen in struct.iter_unpack(">4s L", data):
                    table['contents'].append({
                        'tag': entryTag.decode("utf-8"),
                        'offset': fsDataOffset,
                        'length': entryLen
                    })
                    fsDataOffset += entryLen
            cur += length
        return table

    def scan(self, rom_bytes):
        self.fs_table = self.parse_table(rom_bytes, self.rom_start)

    def split(self, rom_bytes):
        # TODO: dual maintenance of this list and parsers in filesys
        exts = {
            'ADAT': 'yaml'
        }
        path = options.opts.asset_path / self.dir / self.fs_path
        path.mkdir(parents=True, exist_ok=True)
        # assign file path and name which align with pw_filesys
        for form in self.fs_table['contents']:
            ext = exts[form['tag']] if form['tag'] in exts else 'raw'
            form['file'] = f"FORM_{form['tag']}_{form['offset']:06X}.{ext}"
        # emit top-level filetable yaml
        assert self.fs_table and path, f"Unexpected {self.fs_table} {path}"
        with open(path / f"{self.name}.yaml", "w", newline="\n") as fout:
            yaml.dump(self.fs_table, fout, encoding='utf-8', sort_keys=False, default_flow_style=None)

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
