#include "common.h"
#include <PR/ultratypes.h>
#include <uv_graphics.h>
#include <uv_level.h>
#include <uv_memory.h>
#include <uv_util.h>

typedef struct {
    s32 unk0;
} Unk8034F410;

typedef struct {
    u8 unk0[7];
    u8 pad7;
    u8 pad8[0x70];
} Unk8030BDC8;

s32 func_80223E80(s32 addr);
void func_80223F30(s32 arg0);
s32 func_802314D0(s32, s32, s32);
void func_802D1A74(void);
void func_802D1CE8(void);
void func_802D206C(void);
void func_802E1444(u16);
void func_802E27A8(void*);
void func_802E79F0(void);
void func_802E7C28(void);
void func_802EB0D4(void);
void func_802EB270(void);
void func_802F15C8(void);
void func_802F182C(void);
void func_802F1AE8(void);
void func_802F1D3C(void);
void func_802F1FF0(void);
void func_8030BA98(u8, u8);
void func_803151AC(void);
void func_8031531C(void);
void func_80315734(void);
void func_8031596C(void);
void func_80315D68(void);
void func_80315E3C(void);
void func_80320534(void);
void func_8032079C(void);
void func_80335BE4(void);
void func_80335E44(void);
void func_803363E0(void);
void func_8033651C(void);
void func_80341F10(s32);
void func_80348280(LevelTOYS*);
void func_803483AC(void);
void func_8034BEDC(void);
void func_8034C0BC(void);
void func_8034C964(void);
void func_8034CB80(void);
void uvLevelInit(void);
void env_loadtpal(s32);
void uvMemLoadDS(s32);

extern s32 D_8034F400;
extern s32 D_8034F404;
extern LevelObjects* D_8034F408;
extern s32 D_8034F40C;
extern Unk8034F410 D_8034F410[];

// likely arrays of structs for level data
extern s32 gLevelWOBJ;
extern s32 gLevelLPAD;
extern LevelTPTS gLevelTPTS;
extern LevelTOYS gLevelTOYS;
extern s32 gLevelAPTS;
extern s32 gLevelBNUS;
extern LevelObjects gLevelObjects;

void func_8030B6C0(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    s32 i;

    D_8034F40C = arg0;
    uvLevelInit();
    func_80341F10(0x42);
    env_loadtpal(D_80362690->unk0[0].unk8);
    uvMemLoadDS(arg0);
    switch (arg0) {
    case 1:
        D_8034F408 = func_8030BDC8(0);
        break;
    case 3:
        D_8034F408 = func_8030BDC8(1);
        break;
    case 5:
        D_8034F408 = func_8030BDC8(2);
        break;
    case 10:
        D_8034F408 = func_8030BDC8(3);
        break;
    }
    uvMemLoadDS(0x1A);
    if (arg3 != 0) {
        for (i = 0; i < (s32)gLevelObjects.countTOYS; i++) {
            func_80348280(&gLevelObjects.dataTOYS[i]);
        }
        D_8034F400 = 1;
    } else {
        D_8034F400 = 0;
    }
    if ((arg2 == 0) || (arg2 == 6)) {
        uvMemLoadDS(0x1B);
    }
    func_8030BA98(arg1, arg2);
    uvMemLoadDS(0xC);
    uvMemLoadDS(0xD);
    uvMemLoadDS(0x2E);
    func_802E1444(D_80362690->unk0[0].unk8);
    if (arg3 != 0) {
        func_8030B868();
    }
}

void func_8030B868(void) {
    if (D_8034F404 == 0) {
        if (1) { // fakematch
            D_8034F404 = 1;
        }
        switch (D_8034F40C) {
        case 1:
            func_802F1AE8();
            func_802D1CE8();
            break;
        case 3:
            func_8034BEDC();
            func_802EB0D4();
            func_802D1A74();
            func_802F15C8();
            break;
        case 5:
            func_80335BE4();
            func_802E79F0();
            func_803151AC();
            func_802F182C();
            func_80320534();
            break;
        case 10:
            func_80315D68();
            func_80315734();
            func_803363E0();
            func_802F1D3C();
            func_8034C964();
            break;
        }
    }
}

void func_8030B964(void) {
    if (D_8034F404 != 0) {
        if (1) { // fakematch
            D_8034F404 = 0;
        }
        switch (D_8034F40C) {
        case 1:
            func_802F1FF0();
            func_802D206C();
            break;
        case 3:
            func_8034C0BC();
            func_802EB270();
            func_802D206C();
            func_802F1FF0();
            break;
        case 5:
            func_80335E44();
            func_802E7C28();
            func_8031531C();
            func_802F1FF0();
            func_8032079C();
            break;
        case 10:
            func_80315E3C();
            func_8031596C();
            func_8033651C();
            func_802F1FF0();
            func_8034CB80();
            break;
        }
    }
}

void func_8030BA60(void) {
    if (D_8034F400 != 0) {
        func_803483AC();
        func_8030B964();
    }
}

void func_8030BA98(u8 pilot, u8 vehicle) {
    s32 var_a2;

    var_a2 = -1;
    // clang-format off: compress switch statements
    switch (pilot) {
    case 0:
        switch (vehicle) {
        case 0: var_a2 = 0x1C; break;
        case 1: var_a2 = 0x22; break;
        case 2: var_a2 = 0x28; break;
        case 3: var_a2 = 0x2F; break;
        case 4: var_a2 = 0x3B; break;
        case 6: var_a2 = 0x35; break;
        case 5: var_a2 = 0x41; break;
        }
        break;
    case 1:
        switch (vehicle) {
        case 0: var_a2 = 0x1D; break;
        case 1: var_a2 = 0x23; break;
        case 2: var_a2 = 0x29; break;
        case 3: var_a2 = 0x30; break;
        case 4: var_a2 = 0x3C; break;
        case 6: var_a2 = 0x36; break;
        case 5: var_a2 = 0x42; break;
        }
        break;
    case 2:
        switch (vehicle) {
        case 0: var_a2 = 0x1E; break;
        case 1: var_a2 = 0x24; break;
        case 2: var_a2 = 0x2A; break;
        case 3: var_a2 = 0x31; break;
        case 4: var_a2 = 0x3D; break;
        case 6: var_a2 = 0x37; break;
        case 5: var_a2 = 0x43; break;
        }
        break;
    case 3:
        switch (vehicle) {
        case 0: var_a2 = 0x1F; break;
        case 1: var_a2 = 0x25; break;
        case 2: var_a2 = 0x2B; break;
        case 3: var_a2 = 0x32; break;
        case 4: var_a2 = 0x3E; break;
        case 6: var_a2 = 0x38; break;
        case 5: var_a2 = 0x44; break;
        }
        break;
    case 4:
        switch (vehicle) {
        case 0: var_a2 = 0x20; break;
        case 1: var_a2 = 0x26; break;
        case 2: var_a2 = 0x2C; break;
        case 3: var_a2 = 0x33; break;
        case 4: var_a2 = 0x3F; break;
        case 6: var_a2 = 0x39; break;
        case 5: var_a2 = 0x45; break;
        }
        break;
    case 5:
        switch (vehicle) {
        case 0: var_a2 = 0x21; break;
        case 1: var_a2 = 0x27; break;
        case 2: var_a2 = 0x2D; break;
        case 3: var_a2 = 0x34; break;
        case 4: var_a2 = 0x40; break;
        case 6: var_a2 = 0x3A; break;
        case 5: var_a2 = 0x46; break;
        }
        break;
    }
    // clang-format on
    if (var_a2 == -1) {
        _uvDebugPrintf("level : can't compute level append - pilsel:%d vehsel:%d\n", pilot, vehicle);
    } else {
        uvMemLoadDS(var_a2);
    }
}

void func_8030BD20(void) {
}

u8 levelGetWOBJ(void** data) {
    *data = D_8034F408->dataWOBJ;
    return D_8034F408->countWOBJ;
}

u8 levelGetTPTS(LevelTPTS** data) {
    *data = D_8034F408->dataTPTS;
    return D_8034F408->countTPTS;
}

u8 levelGetAPTS(void** data) {
    *data = D_8034F408->dataAPTS;
    return D_8034F408->countAPTS;
}

u8 levelGetLPAD(void** data) {
    *data = D_8034F408->dataLPAD;
    return D_8034F408->countLPAD;
}

u8 levelGetBNUS(void** data) {
    *data = D_8034F408->dataBNUS;
    return D_8034F408->countBNUS;
}

LevelObjects* func_8030BDC8(u8 arg0) {
    s32 i;
    s32 idx;  // spC0
    u32 size; // spBC
    u32 tag;
    u8* srcPtr; // spB4
    Unk8030BDC8 sp3C;
    Unk8030BDC8* ptr;
    LevelObjects* temp;
    u8 tmp8;

    idx = func_80223E80(func_802314D0(D_8034F410[arg0].unk0, 2, arg0));
    temp = &gLevelObjects;
    uvMemSet((void*)temp, 0, sizeof(LevelObjects));
    gLevelObjects.dataWOBJ = &gLevelWOBJ;
    gLevelObjects.dataLPAD = &gLevelLPAD;
    gLevelObjects.dataTOYS = &gLevelTOYS;
    gLevelObjects.dataTPTS = &gLevelTPTS;
    gLevelObjects.dataAPTS = &gLevelAPTS;
    gLevelObjects.dataBNUS = &gLevelBNUS;

    while ((tag = func_80223F7C(idx, &size, (void**)&srcPtr, 1)) != 0) {
        switch (tag) {
        case 'ESND': // 0x45534E44
            for (i = 0; i < temp->unk0; i++) {
                _uvMediaCopy(&sp3C, srcPtr, sizeof(sp3C));
                srcPtr += sizeof(sp3C);
                func_802E27A8(&sp3C);
            }
            break;
        case 'WOBJ': // 0x574F424A
            _uvMediaCopy(temp->dataWOBJ, srcPtr, size);
            break;
        case 'LPAD': // 0x4C504144
            _uvMediaCopy(temp->dataLPAD, srcPtr, size);
            break;
        case 'TOYS': // 0x544F5953
            _uvMediaCopy(temp->dataTOYS, srcPtr, size);
            break;
        case 'TPTS': // 0x54505453
            _uvMediaCopy(temp->dataTPTS, srcPtr, size);
            break;
        case 'APTS': // 0x41505453
            _uvMediaCopy(temp->dataAPTS, srcPtr, size);
            break;
        case 'BNUS': // 0x424E5553
            _uvMediaCopy(temp->dataBNUS, srcPtr, size);
            break;
        case 'LEVL': // 0x4C45564C
            ptr = (Unk8030BDC8*)srcPtr;
            temp->unk0 = ptr->unk0[0];
            if (temp->unk0 >= 255) {
                _uvAssertMsg("dst_level -> level . nenvsnds < NENV_SNDS", "level.c", 0x27F);
            }

            temp->countWOBJ = ptr->unk0[1];
            if (temp->countWOBJ >= 16) {
                _uvAssertMsg("dst_level -> level . nwobjs < LEVEL_NWOBJS", "level.c", 0x282);
            }
            if (temp->countWOBJ >= 17) {
                _uvDebugPrintf("level : too many wind objects defined in level [%d]\n", temp->countWOBJ);
                temp->countWOBJ = 0;
            }

            temp->countLPAD = ptr->unk0[2];
            if (temp->countLPAD >= 15) {
                _uvDebugPrintf("level : too many potential landing pads defined in level [%d]\n", temp->countLPAD);
                temp->countLPAD = 0;
            }

            temp->countTOYS = ptr->unk0[3];
            if (temp->countTOYS >= 17) {
                _uvDebugPrintf("level : too many toys in level [%d]\n", temp->countTOYS);
                temp->countTOYS = 0;
            }

            temp->countTPTS = ptr->unk0[4];
            if (temp->countTPTS >= 17) {
                _uvDebugPrintf("level : too many terra switch points in level [%d]\n", temp->countTPTS);
                temp->countTPTS = 0;
            }

            temp->countAPTS = ptr->unk0[5];
            if (temp->countAPTS >= 21) {
                _uvDebugPrintf("level : too many audio switch points in level [%d]\n", temp->countAPTS);
                temp->countAPTS = 0;
            }

            temp->countBNUS = ptr->unk0[6];
            if (temp->countBNUS >= 3) {
                _uvDebugPrintf("level : too many bonus objects level [%d]\n", temp->countBNUS);
                temp->countBNUS = 0;
            }
            break;
        }
    }
    func_80223F30(idx);
    return &gLevelObjects;
}
