from pathlib import Path

import struct
import yaml
from splat.util import options
from splat.segtypes.segment import Segment
from splat.segtypes.linker_entry import LinkerEntry
from tools.pw64 import filesys as pw64_fs

class N64SegPw_filesys(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(
            rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml
        )
        self.align = 0x10
        self.fs_path = "filesys"

    def scan(self, rom_bytes):
        fsFiles = []
        idx = self.rom_start
        # iterate over filesystem 'FORM' entries and store their tags and offsets
        while idx + 0xC < self.rom_end:
            ftag, length, tag = struct.unpack_from(">4s L 4s", rom_bytes, idx)
            assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
            tag = tag.decode()
            form = {"tag": tag, "length": length, "offset": idx}
            fsFiles.append(form)
            idx += 8 + length
        self.fs_files = fsFiles

    def split(self, rom_bytes):
        path = options.opts.asset_path / self.dir / self.fs_path
        path.mkdir(parents=True, exist_ok=True)
        # split out raw binary blobs of each FORM
        for form in self.fs_files:
            basename = f"FORM_{form["tag"]}_{form["offset"]:06X}"
            start = form["offset"]
            end = start + form["length"] + 8
            formData = rom_bytes[start:end]
            className = f"FORM_{form["tag"]}" if form["tag"][0].isdigit() else form["tag"]
            if hasattr(pw64_fs, className):
                fname = basename + ".yaml"
                fpath = options.opts.asset_path / self.dir / self.fs_path / fname
                dClass = getattr(pw64_fs, className)
                fdata = dClass.from_bytes(formData).as_dict()
                with open(fpath, "w", newline="\n") as fout:
                    yaml.dump(fdata, fout, allow_unicode=True, sort_keys=False)
            else:
                fname = basename + ".raw"
                fpath = options.opts.asset_path / self.dir / self.fs_path / fname
                with open(fpath, "wb") as fout:
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
