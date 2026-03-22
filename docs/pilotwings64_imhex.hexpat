#pragma description Pilotwings 64 ImHex Pattern | N64 ROM header and PW64 filesystem
#pragma author queueRAM

#pragma endian big

import std.io;
import std.mem;
import std.string;

// --------- N64 ROM header ------------

enum CategoryCode : u8 {
    GamePak = 'N',
    Disk_64DD = 'D',
    Expandable_Game_Pak = 'C',
    Expandable_Game_64DD = 'E',
    Aleck64_Game_Pak = 'Z',
};

enum RegionCode : u8 {
    All = 'A',
    Brazil = 'B',
    China = 'C',
    Germany = 'D',
    North_America = 'E',
    France = 'F',
    Gateway_64_NTSC = 'G',
    Netherlands = 'H',
    Italy = 'I',
    Japan = 'J',
    Korea = 'K',
    Gateway_64_PAL = 'L',
    Canada = 'N',
    Europe = 'P',
    Spain = 'S',
    Australia = 'U',
    Scandinavia = 'W',
    Europe = 'X',
    Europe = 'Y',
    Europe = 'Z',
};

struct GameCode {
    CategoryCode categoryCode;
    char gameCode[2];
    RegionCode regionCode;
};

struct LibultraVersion {
    padding[2];
    u8 majorMinor;
    char revision;
}  [[format("libultra_u32")]];;

fn libultra_u32(auto v) {
    u8 major = v.majorMinor / 10;
    u8 minor = v.majorMinor % 10;
    return std::format("{}.{}{}", major, minor, v.revision);
};

struct N64Header {
    u32 PI_BSD_DOM1;
    u32 clockRate;
    u32 *bootAddress : u32;
    LibultraVersion libultraVersion;
    u64 checkCode;
    padding[8];
    char gameTitle[0x14];
    padding[7];
    GameCode gameCode;
    u8 romVersion;
};


// --------- Pilotwings 64 filesystem ------------

// --- common types
using f32 = be float;

struct VecTimeVal {
    f32 time;
    f32 value;
} [[static, format("format_VecTimeVal")]]; // size = 0x8

fn format_VecTimeVal(VecTimeVal v) {
    return std::format("[ {}, {}, {} ]", v.time, v.value);
};

struct Vec3F {
    f32 x, y, z;
} [[static, format("format_Vec3F")]]; // size = 0xC

fn format_Vec3F(Vec3F v) {
    return std::format("[ {}, {}, {} ]", v.x, v.y, v.z);
};

struct Vec4F {
    f32 x, y, z, w;
} [[static]]; // size = 0x10

struct Mtx4F {
    f32 m[16];
} [[static]]; // size = 0x40

// --- UV kernel types
struct UVSY {
    f32 unk0;
    u16 uvVersion;
    u16 UVMD;
    u16 UVCT;
    u16 UVTX;
    u16 UVEN;
    u16 UVLT;
    u16 UVTR;
    u16 UVSQ;
    u16 UVLV;
    u16 UVAN;
    u16 UVFT;
    u16 UVBT;
    u16 unk1C;
    u16 UVSX;
    u16 UVTP;
    u16 unk22;
    padding[4];
} [[static]]; // size = 0x28 (only 0x24 allocated in code)


struct UVEN_Models {
    u16 modelId;
    u8 flag;
} [[static]]; // size = 0x3

struct UVEN_Data {
    u8 screenR;
    u8 screenG;
    u8 screenB;
    u8 screenA;
    u8 fogR;
    u8 fogG;
    u8 fogB;
    u8 fogA;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 padC[8];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
    u8 pad1D[17];
    u8 unk2E;
    u8 pad2F;
    u32 ptr30;
    u8 count;
    padding[3];
    u32 ptr38;
} [[static]]; // size = 0x3C

struct UVEN {
    u8 count;
    UVEN_Models models[count];
    UVEN_Data data;
};


struct UVTR_Tile {
    u8 tileType;
    if (tileType != 0) {
        Mtx4F mat;
        u8 unk44;
        u16 contIdx;
    }
}; // size = (tileType == 0) ? 0x01 : 0x44

struct UVTR {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    UVTR_Tile tiles[unk18 * unk19];
}; // size = 0x28 + variable tiles


struct UVLV {
    u16 terraCount;
    u16 terraIds[terraCount];
    u16 lightCount;
    u16 lightIds[lightCount];
    u16 environmentCount;
    u16 environmentIds[environmentCount];
    u16 modelCount;
    u16 modelIds[modelCount];
    u16 contourCount;
    u16 countourIds[contourCount];
    u16 textureCount;
    u16 textureIds[textureCount];
    u16 sequenceCount;
    u16 sequenceIds[sequenceCount];
    u16 animationCount;
    u16 animationIds[animationCount];
    u16 fontCount;
    u16 fontIds[fontCount];
    u16 blitCount;
    u16 blitIds[blitCount];
};


struct UVSQ_Unk4 {
    u16 unk0;
    f32 unk4;
} [[static]]; // size = 0x6

struct UVSQ {
    u8 count;
    UVSQ_Unk4 unk4[count];
    u8 unk8;
    u8 unk9;
    f32 unkC;
};


struct UVTP_Unk {
    u16 unk4;
    u16 unk8;
} [[static]]; // size = 0x4

struct UVTP {
    u16 count;
    UVTP_Unk unk[count];
};


struct TBD_ {
    u8 comm[parent.length];
};


struct VUE3_COMM {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 modelId;
    s16 unk14;
    padding[parent.length - 0x16];
}; // size = 0x16 (should be 0x20?)

struct VUE3_QUAT_Unk8 {
    Vec4F unk0;
    s32 unk10;
    u8 pad14[0x4];
} [[static]]; // size = 0x18

struct VUE3_QUAT {
    s32 count;
    s32 unk4;
    VUE3_QUAT_Unk8 data[count];
};

struct VUE3_XLAT_Unk8 {
    Vec3F unk0;
    s32 unkC;
} [[static]]; // size = 0x10

struct VUE3_XLAT {
    s32 count;
    s32 unk4;
    VUE3_XLAT_Unk8 data[count];
};

// 3VUE
struct VUE3 {
    char tag[4];
    u32 length;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("COMM"): VUE3_COMM comm;
        ("QUAT"): VUE3_QUAT quat;
        ("XLAT"): VUE3_XLAT xlat;
    }
};


// format PW64 u16 strings as ASCII representation
fn pw64ToAscii(ref auto val) {
    str result;
    for (u32 i = 0, i < sizeof(val) / 2, i += 1) {
        u16 v = val[i];
        if (v >= 0x60 && v <= 0xBF) { // [0x60-0xBF]: bold versions of [0x00-0x5F]
            v -= 0x60;
        }
        match (v) {
            (0x00 ... 0x09): result += char('0' + v);
            (0x0A ... 0x23): result += char('A' + v - 0xA);
            (0x24 ... 0x3D): result += char('a' + v - 0x24);
            (0x3E): result += "-";
            (0x3F): result += "#";
            (0x40): result += "<";
            (0x41): result += ">";
            (0x42): result += " ";
            (0x43): result += "\"";
            (0x44): result += "(";
            (0x45): result += ")";
            (0x46): result += "*";
            (0x47): result += "&";
            (0x48): result += ",";
            (0x49): result += ".";
            (0x4A): result += "/";
            (0x4B): result += "!";
            (0x4C): result += "?";
            (0x4D): result += "'";
            (0x4E): result += "#";
            (0x4F): result += ":";
            (0x50 ... 0x59): result += std::format("{}", v - 0x50);
            (0xD4): result += "%";
            (0xFD): result += " "; // actually "\t" but that renders oddly in ImHex
            (0xFE): result += "\n";
            (0xFF): result += "\0";
            (_): result += ".";
        }
    }
    return result;
};

struct ADAT {
    char tag[4];
    u32 length;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("SIZE"): u8 size[length];
        ("NAME"): char name[length];
        ("DATA"): u16 data[length / 2] [[format("pw64ToAscii")]];
        (_): u8 data[length]; // catch all for things like "SIZE"
    }
};


struct PDAT_PHDR {
    s32 unk0;
    s32 duration;
} [[static]]; // size = 0x8

struct PDAT_PPOS {
    Vec3F pos;
    Vec3F rot;
} [[static]]; // size = 0x18

struct PDAT {
    char tag[4];
    u32 length;
    const u64 Start = $;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("PHDR"): PDAT_PHDR phdr;
        ("PPOS"): PDAT_PPOS pos[while($ - Start < length)];
        (_): u8 data[length];
    }
};


struct SPTH_SCP {
    s32 count;
    VecTimeVal vals[count];
}; // size = 0x4 + (0x8 * count)

struct SPTH {
    char tag[4];
    u32 length;
    const u64 Start = $;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("SCPH"): SPTH_SCP scph;
        ("SCPP"): SPTH_SCP scpp;
        ("SCPR"): SPTH_SCP scpp;
        ("SCPX"): SPTH_SCP scpx;
        ("SCPY"): SPTH_SCP scpy;
        ("SCPZ"): SPTH_SCP scpz;
        ("SCP#"): SPTH_SCP scp_;
        (_): u8 data[length];
    }
    padding[while (($ - Start) < length)]; // length is always to 8-bytes, not offsets
};


struct LevelLEVL {
    u8 countESND;
    u8 countWOBJ;
    u8 countLPAD;
    u8 countTOYS;
    u8 countTPTS;
    u8 countAPTS;
    u8 countBNUS;
    padding[1];
};

struct LevelAPTS {
    Vec3F unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} [[static]]; // size = 0x20

struct LevelBNUS {
    Vec3F pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s32 unk18;
} [[static]]; // size = 0x1C

struct LevelESND {
    Mtx4F unk0;
    Vec3F unk40;
    Vec3F unk4C;
    s8 unk58;
    u8 pad59[3];
    f32 unk5C;
    f32 unk60;
    s32 unk64;
    f32 unk68;
    f32 unk6C;
    s8 unk70;
    u8 pad71[3];
    s32 unk74;
} [[static]]; // size = 0x78

// potential landing pad defined for Map (Level)
struct LevelLPAD {
    Vec3F pos;
    f32 unkC;
    s32 unk10;
    u8 unk14;
    padding[3];
} [[static]]; // size = 0x18

struct LevelTOYS {
    Vec3F pos;
    u8 unkC[4];
} [[static]]; // size = 0x10

struct LevelTPTS {
    u8 unk0;
    u8 unk1[3];
    Vec3F unk4;
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    s32 unk20;
    f32 unk24;
    Vec3F unk28;
} [[static]]; // size = 0x34 (padded to 0x38)

enum WOBJType : u8 {
    WindsockJointed = 0x00,
    WindTurbine     = 0x01,
    WindsockSimple  = 0x02,
};

struct LevelWOBJ {
    Vec3F pos;
    WOBJType type;
    padding[3];
} [[static]]; // size = 0x10

// PW64 Level (map) data
struct UPWL {
    char tag[4];
    u32 length;
    const u64 Start = $;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("LEVL"): LevelLEVL levl;
        ("APTS"): LevelAPTS apts[length / sizeof(LevelAPTS)];
        ("BNUS"): LevelBNUS bnus[length / sizeof(LevelBNUS)];
        ("ESND"): LevelESND esnd[length / sizeof(LevelESND)];
        ("LPAD"): LevelLPAD lpad[length / sizeof(LevelLPAD)];
        ("TOYS"): LevelTOYS toys[length / sizeof(LevelTOYS)];
        ("TPTS"): LevelTPTS tpts[length / sizeof(LevelTPTS)];
        ("WOBJ"): LevelWOBJ wobj[length / sizeof(LevelWOBJ)];
    }
    padding[while (($ - Start) < length)]; // length is always to 8-bytes, not offsets
};

// --- UV user types
struct Unk803599D0 {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s32 pad44;
    s32 pad48;
    s32 pad4C;
    s32 pad50;
} [[static]]; // size = 0x54

struct Unk80345C80 {
    Unk803599D0 unk0;
    Unk803599D0 unk54;
    Unk803599D0 unkA8;
    Unk803599D0 unkFC;
    Unk803599D0 unk150;
    u8 pad1A4[0x3B4-0x1A4];
    s32 unk3B4;
    s32 unk3B8;
    f32 unk3BC;
    f32 unk3C0;
    f32 unk3C4;
    f32 unk3C8;
} [[static]]; // size = 0x3CC

struct UPWT_COMM {
    u8 classNum;
    u8 vehNum;
    u8 testNum;
    u8 unk3;
    u8 unk4;
    u8 unk5[0x3];
    u8 unk8[4];
    u8 unkC[4];
    s32 unk10;
    u8 unk14[0x18];
    s32 unk2C;
    u8 unk30[0x14];
    f32 unk44;
    Unk80345C80 unk48;
    u8 unk414[8];
    u8 countTHER;
    u8 countLWIN;
    u8 countTPAD;
    u8 countLPAD;
    u8 countLSTP;
    u8 countRNGS;
    u8 countBALS;
    u8 countTARG;
    u8 countHPAD;
    u8 countBTGT;
    u8 countPHTS;
    u8 countFALC;
    u8 countSDFM;
    u8 countCNTG;
    u8 countHOPD;
    u8 countOBSV;
} [[static]]; // size = 0x42C (padded to 0x430 in FS)

struct TaskBALS {
    Vec3F pos;
    u8 padC[0x18 - 0xC];
    s32 unk18;
    f32 unk1C;
    u8 type;
    u8 unk21;
    u8 pad22[2];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 scale;
    s32 unk34;
    s32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[4];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    s32 unk54;
    s32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
} [[static]]; // size = 0x68

struct TaskBTGT {
    Vec3F pos;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
    padding[2];
} [[static]]; // size = 0x1C (padded to 0x20 in FS)

struct TaskCNTG {
    Vec3F pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    padding[3];
} [[static]]; // size = 0x1C (padded to 0x20 in FS)

struct TaskFALC {
    Vec3F unk0;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 pad14[4];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    f32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    f32 unkA8;
} [[static]]; // size = 0xAC

struct TaskHOPD {
    u8 pad0[4];
    Vec3F pos;
    s32 unk10;
    f32 scale;
    f32 height;
    u8 pad1C[4];
} [[static]]; // size = 0x20

enum HPADType : u8 {
    Large = 0x00,
    Small = 0x01,
};

struct TaskHPAD {
    Vec3F pos [[comment("position vector")]];
    Vec3F rot [[comment("rotation vector (degrees)")]];
    s32 unk18;
    HPADType type;
    u8 points;
    u8 pad1E[2];
    f32 fuelAdded;
    u8 nextHpadCount [[comment("number of HPADs to activate")]];
    u8 pad25[3];
    s32 nextHpads[5] [[comment("array of HPADs to activate")]];
    u8 active [[comment("active at start")]];
    padding[3];
} [[static]] ; // size = 0x40

struct TaskLPAD {
    Vec3F pos;
    Vec3F angle;
    u8 pad18[4];
    Vec3F unk1C;
    u8 unk28;
    u8 pad29[3];
    u8 unk2C;
    padding[3];
} [[static]]; // size = 0x30

struct TaskLSTP {
    Vec3F pos;
    Vec3F unkC;
    u8 pad10[0x4];
    u8 unk1C;
    padding[3];
    f32 unk20;
} [[static]]; // size = 0x24 (padded to 0x28 in FS)

struct TaskLWIN {
    Vec3F unk0;
    Vec3F unkC;
    Vec3F unk18;
    Vec3F unk24;
    Vec3F unk30;
    s32 unk3C;
    Vec3F unk40;
    f32 unk4C;
    u8 unk50;
    u8 unk51;
    padding[2];
} [[static]]; // size = 0x54

// OBSV is not actually present in FS, but is decoded in code
struct TaskOBSV {
    f32 x;
    f32 y;
    f32 z;
    f32 unkC;
} [[static]]; // size = 0x10

struct TaskPHTS {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} [[static]]; // size = 0x14

struct TaskRNGS {
    Vec3F pos [[comment("position vector")]];
    Vec3F rot [[comment("rotation vector (degrees)")]];
    s32 unk18;
    padding[1];
    u8 childCount;
    padding[2];
    s32 childRings[5];
    u8 timedChildRingCount;
    padding[3];
    s32 timedChildRings[5];
    u8 points;
    u8 untimed;
    padding[2];
    f32 timeRingDuration;
    u8 size;
    u8 isActive;
    padding[2];
    f32 rotationRate0;
    f32 translation;
    char rotationAxis0;
    padding[3];
    f32 rotationRateTimedOut1;
    f32 rotationRateTiming1;
    f32 rotationRate1;
    char rotationAxis1;
    u8 ringType;
    u8 ringSubType;
    u8 unk73;
    char name[0x10];
} [[static]]; // size = 0x84

// SDFM is not present in FS, but is copied in code so only size is known
struct TaskSDFM {
    u8 unk0[0x4C];
} [[static]]; // size = 0x4C

struct TaskTARG {
    Vec3F pos;
    Vec3F rot;
    u8 targetType;
    u8 unk19;
    s32 pad1C;
} [[static]]; // size = 0x20

struct TaskTHER {
    Vec3F pos;
    f32 scale;
    f32 height;
    s32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} [[static]]; // size = 0x28

struct TaskTPAD {
    Vec3F pos;
    Vec3F angle;
    u8 pad18[4];
    Vec3F unk1C;
    u8 unk28;
    u8 pad29[3];
    f32 unk2C;
} [[static]]; // size = 0x30

// PW64 Task objectives data
struct UPWT {
    char tag[4];
    u32 length;
    const u64 Start = $;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("JPTX" | "NAME" | "INFO"): char data[length];
        ("COMM"): UPWT_COMM comm;
        ("BALS"): TaskBALS bals[length / sizeof(TaskBALS)];
        ("BTGT"): TaskBTGT btgt[length / sizeof(TaskBTGT)];
        ("CNTG"): TaskCNTG cntg[length / sizeof(TaskCNTG)];
        ("FALC"): TaskFALC falc[length / sizeof(TaskFALC)];
        ("HOPD"): TaskHOPD hopd[length / sizeof(TaskHOPD)];
        ("HPAD"): TaskHPAD hpad[length / sizeof(TaskHPAD)];
        ("LPAD"): TaskLPAD lpad[length / sizeof(TaskLPAD)];
        ("LSTP"): TaskLSTP lstp[length / sizeof(TaskLSTP)];
        ("LWIN"): TaskLWIN lwin[length / sizeof(TaskLWIN)];
        ("OBSV"): TaskOBSV obsv[length / sizeof(TaskOBSV)];
        ("PHTS"): TaskPHTS phts[length / sizeof(TaskPHTS)];
        ("RNGS"): TaskRNGS rngs[length / sizeof(TaskRNGS)];
        ("SDFM"): TaskSDFM sdfm[length / sizeof(TaskSDFM)];
        ("TARG"): TaskTARG targ[length / sizeof(TaskTARG)];
        ("THER"): TaskTHER ther[length / sizeof(TaskTHER)];
        ("TPAD"): TaskTPAD tpad[length / sizeof(TaskTPAD)];
        (_): u8 data[length];
    }
    padding[while (($ - Start) < length)]; // length is always to 8-bytes, not offsets
};


// templated handler for UV FORM data
struct UV<T, auto Align> {
    char tag[4];
    u32 length;
    match (tag) {
        ("PAD "): u8 pad[length] [[hidden]];
        ("COMM"): T comm;
        ("GZIP"): {
            char comm[4];
            u32 dLength;
            u8 compData[length - 8]; // length includes COMM and dLength
        }
        (_): u8 data[length]; // catch all for things like "PART" in UNAN or "LEVL" in UPWL
    }
    if (Align) {
        padding[while($ % 8 != 0)];
    }
};


struct FORM {
    char form[4];
    u32 length;
    const u64 TagStart = $;
    char tag[4];
    match (tag) {
        // UV tags
        ("UVSY"): UV<UVSY, true> entries[while(($ - TagStart) < length)];
        ("UVEN"): UV<UVEN, true> entries[while(($ - TagStart) < length)];
        ("UVTR"): UV<UVTR, true> entries[while(($ - TagStart) < length)];
        ("UVLV"): UV<UVLV, true> entries[while(($ - TagStart) < length)];
        ("UVSQ"): UV<UVSQ, true> entries[while(($ - TagStart) < length)];
        ("UVTP"): UV<UVTP, true> entries[while(($ - TagStart) < length)];
        ("UVMD"): UV<TBD_, false> entries[while(($ - TagStart) < length)]; // pure GZIP
        ("UVCT"): UV<TBD_, false> entries[while(($ - TagStart) < length)]; // pure GZIP
        ("UVTX"): UV<TBD_, false> entries[while(($ - TagStart) < length)]; // pure GZIP
        ("UVBT"): UV<TBD_, false> entries[while(($ - TagStart) < length)]; // pure GZIP
        ("UVAN"): UV<TBD_, false> entries[while(($ - TagStart) < length)];
        ("UVFT"): UV<u8, false> entries[while(($ - TagStart) < length)];
        ("UPWL"): UPWL entries[while(($ - TagStart) < length)];
        ("SPTH"): SPTH entries[while(($ - TagStart) < length)];
        ("UPWT"): UPWT entries[while(($ - TagStart) < length)];
        ("ADAT"): ADAT entries[while(($ - TagStart) < length)];
        ("3VUE"): VUE3 entries[while(($ - TagStart) < length)];
        ("PDAT"): PDAT entries[while(($ - TagStart) < length)];
        ("UVSX"): UV<TBD_, false> entries[while(($ - TagStart) < length)]; // TODO: types for .CTL/.TBL
    }
} [[name(std::format("{}", tag))]];


// --------- Header
N64Header N64Header @ 0x00;

// --------- Filesystem
FORM uvsy @ 0xDF5B0;
FORM uven @ 0xDF5F8;
// ignore UVLT @ 0xDFD70 because it is empty
FORM uvtr @ 0xDFD88;
FORM uvlv @ 0xE2028;
FORM uvsq @ 0xE4FA8;
FORM uvtp @ 0xE5030;
FORM uvmd[363] @ 0xE5138;
FORM uvct[101] @ 0x1BB0AC;
FORM uvtx[463] @ 0x240100;
FORM uvan[115] @ 0x3085DC;
FORM uvft[9] @ 0x32C3F8;
FORM upwl[4] @ 0x33020C;
FORM spth0 @ 0x342B7C;
FORM upwt[61] @ 0x342E2C;
FORM adat0 @ 0x35C08C;
FORM spth1[5] @ 0x36E214;
FORM vue3[12] @ 0x36E754;
FORM pdat[25] @ 0x37F434;
FORM spth2[2] @ 0x44C774;
FORM uvbt[102] @ 0x44D494;
FORM uvsx @ 0x4B577C;