#!/bin/env python3

import struct

class ADAT:
    """
    ADAT stores string identifiers and data strings encoded in custom u16 chars.
    """
    def __init__(self, tag=None, pad_count=0, entries=None):
        self.tag = tag if tag is not None else self.__class__.__name__
        self.pad_count = pad_count
        self.entries = entries if entries is not None else {}

    @staticmethod
    def str_decode(data: bytes) -> str:
        """
        decode from raw bytes to UTF-8 string representation

        Supports:
            - [0-9A-Za-z-#<> "()*&,./!?':\n\t]
            - Wide `>` arrow used in sound settings
            - Bold font, enclosed with {}
            - Replacement token, replaced with `%d`
        """
        pw64CharMap = {
            0x00: '0', 0x01: '1', 0x02: '2', 0x03: '3', 0x04: '4', 0x05: '5', 0x06: '6', 0x07: '7',
            0x08: '8', 0x09: '9', 0x0A: 'A', 0x0B: 'B', 0x0C: 'C', 0x0D: 'D', 0x0E: 'E', 0x0F: 'F',
            0x10: 'G', 0x11: 'H', 0x12: 'I', 0x13: 'J', 0x14: 'K', 0x15: 'L', 0x16: 'M', 0x17: 'N',
            0x18: 'O', 0x19: 'P', 0x1A: 'Q', 0x1B: 'R', 0x1C: 'S', 0x1D: 'T', 0x1E: 'U', 0x1F: 'V',
            0x20: 'W', 0x21: 'X', 0x22: 'Y', 0x23: 'Z', 0x24: 'a', 0x25: 'b', 0x26: 'c', 0x27: 'd',
            0x28: 'e', 0x29: 'f', 0x2A: 'g', 0x2B: 'h', 0x2C: 'i', 0x2D: 'j', 0x2E: 'k', 0x2F: 'l',
            0x30: 'm', 0x31: 'n', 0x32: 'o', 0x33: 'p', 0x34: 'q', 0x35: 'r', 0x36: 's', 0x37: 't',
            0x38: 'u', 0x39: 'v', 0x3A: 'w', 0x3B: 'x', 0x3C: 'y', 0x3D: 'z', 0x3E: '-', 0x3F: '#',
            0x40: '<', 0x41: '>', 0x42: ' ', 0x43: '\"', 0x44: '(', 0x45: ')', 0x46: '*', 0x47: '&',
            0x48: ',', 0x49: '.', 0x4A: '/', 0x4B: '!', 0x4C: '?', 0x4D: '\'', 0x4E: '＞', 0x4F: ':',
            0xD4: '%d', 0xFE: '\n', 0xFD: '\t'
        }
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

    @staticmethod
    def str_encode(uStr: str) -> bytes:
        """
        encode UTF-8 string to PW64 u16 string encoding
        """
        import string
        encData = b''
        isBold = False
        inSpecial = False
        hexLeft = 0
        hexVal = 0
        for c in uStr:
            val = -1
            if inSpecial:
                inSpecial = False
                if c == 'd':
                    val = 0xD4
                elif c == 'x':
                    hexLeft = 4
                    hexVal = 0
            elif hexLeft > 0:
                hexVal = (hexVal * 0x10) + int(c, 16)
                hexLeft -= 1
                val = hexVal if hexLeft == 0 else -1
            elif c == '{':
                isBold = True
            elif c == '}':
                isBold = False
            elif c == '%':
                inSpecial = True
            else:
                if c in string.digits:
                    val = ord(c) - ord('0')
                elif c in string.ascii_uppercase:
                    val = ord(c) - ord('A') + 0x0A
                elif c in string.ascii_lowercase:
                    val = ord(c) - ord('a') + 0x24
                else:
                    lut = {
                        '-': 0x3E, '#': 0x3F, '<': 0x40, '>': 0x41, ' ': 0x42, '\"': 0x43, '(': 0x44, ')': 0x45,
                        '*': 0x46, '&': 0x47, ',':  0x48, '.': 0x49, '/': 0x4A, '!': 0x4B, '?': 0x4C, '\'': 0x4D,
                        '＞': 0x4E, ':': 0x4F, '\n': 0xFE, '\t': 0xFD
                    }
                    assert c in lut, f"Unknown char {c}"
                    if c in lut:
                        val = lut[c]
                if isBold and val >= 0 and val < 0x60:
                    val += 0x60
            if val >= 0:
                encData += struct.pack(">H", val)
        encData += struct.pack(">H", 0xFF)
        return encData

    @classmethod
    def from_dict(cls, d: dict):
        """Construct ADAT from dictionary"""
        return cls(d["tag"], d["pad_count"], d["entries"])

    @classmethod
    def from_bytes(cls, formBytes: bytes):
        pad_count = 0
        entries = []
        ftag, flen, tag = struct.unpack(">4s L 4s", formBytes[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        assert tag == b'ADAT', f"Expected 'ADAT', got ${tag}"
        aBytes = formBytes[8:]
        idx = 4
        aSize = 0
        aName = ""
        while idx < flen:
            atag, alen = struct.unpack(">4s L", aBytes[idx:idx+8])
            idx += 8
            if atag == b'PAD ':
                pad_count += 1
            elif atag == b'SIZE':
                aSize, = struct.unpack(">L", aBytes[idx:idx+4])
            elif atag == b'NAME':
                aName = aBytes[idx:idx+alen].decode().rstrip('\x00')
            elif atag == b'DATA':
                aDataRaw = aBytes[idx:idx+alen]
                aData = cls.str_decode(aDataRaw)
                entries.append({"NAME": aName, "DATA": aData})
            idx += alen
        assert len(entries) == aSize, f"Mismatch length: {len(entries)} != {aSize}"
        return ADAT("ADAT", pad_count, entries)

    def as_dict(self) -> dict:
        """Generate dictionary suitable for creating YAML representation"""
        return {
            "tag": self.tag,
            "pad_count": self.pad_count,
            "entries": self.entries
        }

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        records += struct.pack(">4s L L L", b'SIZE', 8, len(self.entries), 0)
        for ent in self.entries:
            name = ent["NAME"].encode() + b'\0'
            name += b'\0' * ((8 - (len(name) % 8)) % 8)
            encData = self.str_encode(ent["DATA"])
            encData += b'\0' * ((8 - (len(encData) % 8)) % 8)
            records += struct.pack(">4s L", b'NAME', len(name)) + name
            records += struct.pack(">4s L", b'DATA', len(encData)) + encData
        return struct.pack(">4s L", b'FORM', len(records)) + records


class SPTH:
    """
    SPath class which stores x,y,z and heading,pitch,roll data for paths

    each of these datasets are stored as separate arrays, with each entry
    containing a time and value. the values used at runtime are then interpolated
    between the array. this means each dataset need not be of the same length.
    """

    # order of tags is important
    _spathTags = ("SCPP", "SCPH", "SCPX", "SCPY", "SCPR", "SCPZ", "SCP#")

    def __init__(self, tag=None, pad_count=0, entries=None):
        self.tag = tag if tag is not None else self.__class__.__name__
        self.pad_count = pad_count
        self.entries = entries if entries is not None else {}

    @classmethod
    def from_dict(cls, d: dict):
        """Construct SPTH from dictionary"""
        return cls(d["tag"], d["pad_count"], d["entries"])

    @classmethod
    def from_bytes(cls, form: bytes):
        """Construct SPTH from raw filesystem bytes"""
        ftag, flen, stag = struct.unpack(">4s L 4s", form[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        assert stag == b'SPTH', f"Expected 'SPTH', got ${stag}"
        sBytes = form[8:]
        idx = 4
        pad_count = 0
        entries = {}
        while idx < flen:
            tag, length = struct.unpack(">4s L", sBytes[idx:idx+8])
            idx += 8
            tag = tag.decode()
            assert tag == "PAD " or tag in cls._spathTags, f"Unexpected tag '${tag}'"
            if tag == "PAD ":
                pad_count += 1
            elif tag in cls._spathTags:
                spIdx = idx
                count, = struct.unpack(">L", sBytes[spIdx:spIdx+4])
                spIdx += 4
                sp = [{"time": e[0], "val": e[1]} for e in struct.iter_unpack(">ff", sBytes[spIdx:spIdx+8*count])]
                spIdx += 8*count
                entries[tag] = sp
            idx += length
        return cls(stag.decode(), pad_count, entries)

    # - tag: SPTH
    # - pad_count: 1
    # - entries:
    #     - {time: 0.0, val: 0.0}
    #     - {time: 2.0, val: 4.0}
    #     - ...
    def as_dict(self) -> dict:
        """Generate dictionary suitable for creating YAML representation"""
        return {
            "tag": self.tag,
            "pad_count": self.pad_count,
            "entries": self.entries
        }

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        for tag in self._spathTags:
            scpCount = len(self.entries[tag])
            scpLength = 8 + 8 * scpCount
            records += struct.pack(">4s L L", tag.encode(), scpLength, scpCount)
            records += b''.join([struct.pack(">ff", e['time'], e['val']) for e in self.entries[tag]])
            records += b'\0' * ((8 - (len(records) % 8)) % 8)
        spth = b'FORM' + struct.pack(">L", len(records)) + records
        return spth


class UV_COMM:
    """Boilerplate class for UV** that have one type of COMM entry"""

    def __init__(self, tag=None, pad_count=0, comm=None):
        self.tag = tag if tag is not None else self.__class__.__name__
        self.pad_count = pad_count
        self.comm = [] if comm is None else comm

    @classmethod
    def from_dict(cls, d: dict):
        """Construct from dictionary"""
        return cls(d["tag"], d["pad_count"], d["comm"])

    def as_dict(self) -> dict:
        """Generate dictionary suitable for creating YAML representation"""
        return {
            "tag": self.tag,
            "pad_count": self.pad_count,
            "comm": self.comm
        }


class UVEN(UV_COMM):
    """Environment"""

    @classmethod
    def from_bytes(cls, form: bytes):
        """Construct from raw filesystem bytes"""
        ftag, flen, utag = struct.unpack(">4s L 4s", form[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        utag = utag.decode()
        assert utag == cls.__name__, f"Expected '{cls.__name__}', got ${utag}"
        payload = form[8:]
        idx = 4
        pad_count = 0
        comm = []
        while idx < flen:
            tag, length = struct.unpack(">4s L", payload[idx:idx+8])
            idx += 8
            tag = tag.decode()
            assert tag in ("PAD ", "COMM"), f"Unexpected tag '${tag}'"
            if tag == "PAD ":
                pad_count += 1
            else:
                models = []
                commIdx = idx
                count, = struct.unpack(">B", payload[commIdx:commIdx+1])
                commIdx += 1
                if count > 0:
                    models = [list(m) for m in struct.iter_unpack(">HB", payload[commIdx:commIdx+3*count])]
                commIdx += 3*count
                data = list(struct.unpack(">4B 4B 4B 8x 2f B 17x 2B L B 3xL", payload[commIdx:commIdx+0x3C]))
                commIdx += 0x3C
                comm.append({"models": models, "data": data})
            idx += length
        return cls(utag, pad_count, comm)

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        for c in self.comm:
            comm = struct.pack(">B", len(c["models"]))
            comm += b''.join([struct.pack(">HB", m[0], m[1]) for m in c["models"]])
            comm += struct.pack(">4B 4B 4B 8x 2f B 17x 2B L B 3xL", *c["data"])
            comm += b'\0' * ((8 - (len(comm) % 8)) % 8)
            records += b'COMM' + struct.pack(">L", len(comm)) + comm
        return b'FORM' + struct.pack(">L", len(records)) + records


class UVLT(UV_COMM):
    """
    UVLT exists in the filesystem, but only contains 'PAD ' fields.
    The code will read 4 bytes from COMM if it existed, but it does not.
    """

    @classmethod
    def from_bytes(cls, form: bytes):
        """Construct from raw filesystem bytes"""
        ftag, flen, utag = struct.unpack(">4s L 4s", form[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        utag = utag.decode()
        assert utag == cls.__name__, f"Expected '{cls.__name__}', got ${utag}"
        payload = form[8:]
        idx = 4
        pad_count = 0
        comm = []
        while idx < flen:
            tag, length = struct.unpack(">4s L", payload[idx:idx+8])
            idx += 8
            tag = tag.decode()
            assert tag in ("PAD ", "COMM"), f"Unexpected tag '${tag}'"
            if tag == "PAD ":
                pad_count += 1
            else:
                ltIdx = idx
                lt = list(struct.unpack(">4B", payload[ltIdx:ltIdx+4]))
                ltIdx += 4
                comm.append(lt)
            idx += length
        return cls(utag, pad_count, comm)

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        for c in self.comm:
            comm = struct.pack(">4B", *c)
            comm += b'\0' * ((8 - (len(comm) % 8)) % 8)
            records += b'COMM' + struct.pack(">L", len(comm)) + comm
        return b'FORM' + struct.pack(">L", len(records)) + records


class UVLV(UV_COMM):
    """
    `UVLV` contains the counts and IDs used for the terrain, models, texture, animation for map data.
    """

    _levelFields = ("terra", "light", "environment", "model", "contour", "texture", "sequence", "animation", "font", "blit")

    @classmethod
    def from_bytes(cls, form: bytes):
        """Construct from raw filesystem bytes"""
        ftag, flen, utag = struct.unpack(">4s L 4s", form[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        utag = utag.decode()
        assert utag == cls.__name__, f"Expected '{cls.__name__}', got ${utag}"
        payload = form[8:]
        idx = 4
        pad_count = 0
        comm = []
        while idx < flen:
            tag, length = struct.unpack(">4s L", payload[idx:idx+8])
            idx += 8
            tag = tag.decode()
            assert tag in ("PAD ", "COMM"), f"Unexpected tag '${tag}'"
            if tag == "PAD ":
                pad_count += 1
            else:
                lv = {}
                lvIdx = idx
                for field in cls._levelFields:
                    count, = struct.unpack(">H", payload[lvIdx:lvIdx+2])
                    lvIdx += 2
                    lv[field] = [i for i, in struct.iter_unpack(">H", payload[lvIdx:lvIdx+2*count])]
                    lvIdx += 2*count
                comm.append(lv)
            idx += length
        return cls(utag, pad_count, comm)

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        for c in self.comm:
            comm = b''
            for field in self._levelFields:
                ids = c[field]
                comm += struct.pack(">H", len(ids))
                comm += b''.join([struct.pack(">H", i) for i in ids])
            comm += b'\0' * ((8 - (len(comm) % 8)) % 8)
            records += b'COMM' + struct.pack(">L", len(comm)) + comm
        return b'FORM' + struct.pack(">L", len(records)) + records


class UVSQ(UV_COMM):
    """
    `UVSQ` contains animation sequences for dynamic textures.
    """
    @classmethod
    def from_bytes(cls, form: bytes):
        """Construct from raw filesystem bytes"""
        ftag, flen, utag = struct.unpack(">4s L 4s", form[:0xC])
        assert ftag == b'FORM', f"Expected 'FORM', got ${ftag}"
        utag = utag.decode()
        assert utag == cls.__name__, f"Expected '{cls.__name__}', got ${utag}"
        payload = form[8:]
        idx = 4
        pad_count = 0
        comm = []
        while idx < flen:
            tag, length = struct.unpack(">4s L", payload[idx:idx+8])
            idx += 8
            tag = tag.decode()
            assert tag in ("PAD ", "COMM"), f"Unexpected tag '${tag}'"
            if tag == "PAD ":
                pad_count += 1
            else:
                sqIdx = idx
                frameCount, = struct.unpack(">B", payload[sqIdx:sqIdx+1])
                sqIdx += 1
                frameLen = 6 * frameCount
                frames = [{"textureId": tid, "frameTime": ft} for tid, ft in struct.iter_unpack(">Hf", payload[sqIdx:sqIdx+frameLen])]
                sqIdx += frameLen
                mode, reverse, framerate = struct.unpack(">B B f", payload[sqIdx:sqIdx+6])
                sq = {
                    "frames": frames,
                    "mode": mode,
                    "reverse": reverse,
                    "framerate": framerate
                }
                comm.append(sq)
            idx += length
        return cls(utag, pad_count, comm)

    def __bytes__(self) -> bytes:
        """Generate raw bytes suitable for regenerating filesystem data"""
        records = struct.pack(">4s", self.tag.encode())
        records += struct.pack(">4s L L", b'PAD ', 4, 0) * self.pad_count
        for c in self.comm:
            comm = struct.pack(">B", len(c["frames"]))
            comm += b''.join([struct.pack(">Hf", f["textureId"], f["frameTime"]) for f in c["frames"]])
            comm += struct.pack(">B B f", c["mode"], c["reverse"], c["framerate"])
            comm += b'\0' * ((8 - (len(comm) % 8)) % 8)
            records += b'COMM' + struct.pack(">L", len(comm)) + comm
        return b'FORM' + struct.pack(">L", len(records)) + records
