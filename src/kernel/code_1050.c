#include <uv_audio.h>
#include <uv_matrix.h>
#include <libc/stdarg.h>

UnkStruct_80200144_t D_80250E80[1];

void func_802000DC(u16);

void func_802000A0(void) {
    u16 i;

    for (i = 0; i < 1; i++) {
        func_802000DC(i);
    }
}

void func_802000DC(u16 arg0) {
    Mtx4F ident;
    UnkStruct_80200144_t* temp_a0;

    temp_a0 = &D_80250E80[arg0];

    uvMat4SetIdentity(&ident);
    uvMat4Copy(&temp_a0->mat, &ident);
    temp_a0->unk4C = 2;
    temp_a0->unk40 = 1.0f;
    temp_a0->unk44 = 1.0f;
}

void func_80200144(u16 arg0, Mtx4F* arg1) {
    uvMat4Copy(&D_80250E80[arg0].mat, arg1);
}

void func_80200180(u16 arg0, ...) {
    UnkStruct_80200144_t* temp_a2;
    u32 propertyType;
    va_list args;

    temp_a2 = &D_80250E80[arg0];

    // passing an object that undergoes default argument promotion to 'va_start'
    // has undefined behavior (e.g. u8, u16, f32)
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"
#endif
    va_start(args, arg0);
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

    while (TRUE) {
        propertyType = va_arg(args, s32);
        switch (propertyType) {
        case 0:
            return;
        case 1:
            temp_a2->unk40 = va_arg(args, f64);
            break;
        case 2:
            temp_a2->unk44 = va_arg(args, f64);
            break;
        case 4:
            temp_a2->unk48 = va_arg(args, f64);
            break;
        case 8:
            temp_a2->unk4C = va_arg(args, s32);
            break;
        default:
            _uvDebugPrintf("Unknown property type %d\n", propertyType);
            return;
        }
    }
}

void func_80200308(u16 arg0) {
    uvEmitterFlush(arg0);
    uvaSeqSetVol(D_80250E80[arg0].unk44);
}
