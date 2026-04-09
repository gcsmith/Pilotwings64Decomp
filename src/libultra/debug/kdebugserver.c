#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

typedef struct {
	unsigned type : 2;
    unsigned unk_2 : 4;
	unsigned length : 2;
	char buf[3];
} rdbPacketVD; // likely earlier version of rdbPacket

static u8 buffer[0x100];

static s32 kdebugState = 0;
static s32 numChars = 0;
static s32 kdebugRemaining = 0;

// could also be a struct with buffer at 0x20 offset
extern u8 D_802CA750[0x1B0];

#if BUILD_VERSION <= VERSION_D
// u32 to string
void func_802441A0(u32 arg0, u8* arg1) {
    arg1[0] = ((arg0 >> 24) & 0xFF);
    arg1[1] = ((arg0 >> 16) & 0xFF);
    arg1[2] = ((arg0 >> 8) & 0xFF);
    arg1[3] = (arg0 & 0xFF);
}
#endif

// string_to_u32
static u32 func_802441D0(u8* s) {
    u32 k;

    k = ((s[0] & 0xFF) << 0x18);
    k |= ((s[1] & 0xFF) << 0x10);
    k |= ((s[2] & 0xFF) << 0x8);
    k |= (s[3] & 0xFF);

    return k;
}

#if BUILD_VERSION <= VERSION_D
// similar to send_packet(), except for:
//   a. different `type` bitfield width
//   b. also waits on __osGetCause()
void func_80244228(u8* buf, s32 length) {
    rdbPacketVD packet;
    s32 i;

    packet.type = 0x2;
    packet.length = length;

    for (i = 0; i < length; i++) {
        packet.buf[i] = buf[i];
    }

    *(vu32*)RDB_BASE_REG = *(vu32*)&packet;

    while (!(__osGetCause() & CAUSE_IP6)) {
        ;
    }

    *(vu32*)RDB_READ_INTR_REG = 0;
}

// similar interface as send(), except:
//   a. doesn't have __osRdb_IP6_Empty
//   b. splits packet sending into full 3 bytes and remainder
void func_802442E8(u8* buf, s32 length) {
    s32 i;
    s32 lengthAlign3;
    s32 remainder;

    if (__osRdbWriteOK == 0) {
        while (!(__osGetCause() & CAUSE_IP6)) { }
        *(vs32* )RDB_READ_INTR_REG = 0;
        __osRdbWriteOK = 1;
    }
    remainder = length % 3;
    lengthAlign3 = length - remainder;

    for (i = 0; i < lengthAlign3; i += 3) {
        func_80244228(&buf[i], 3);
    }
    if (remainder > 0) {
        func_80244228(&buf[lengthAlign3], remainder);
    }
}

void kdebugserver_text_0220(void) {
    s32 addr;
    s32 length;

    addr = func_802441D0(&buffer[1]);
    length = func_802441D0(&buffer[5]);
    func_802442E8((u8*)addr, length);
}

void kdebugserver_text_026C(void) {
    func_802442E8(&D_802CA750[0x20], 0x190);
}

void kdebugserver(u32 rawPacket) {
    u32 i;
    rdbPacketVD packet;

    *(u32*)&packet = rawPacket;

    for (i = 0; i < packet.length; i++) {
        buffer[numChars++] = packet.buf[i];
    }
    kdebugRemaining -= packet.length;
    switch (kdebugState) {
    case 0:
        switch (packet.buf[0]) {
        case 1:
            kdebugState = 1;
            kdebugRemaining = 9 - packet.length;
            return;
        case 2:
            kdebugserver_text_026C();
            kdebugState = 0;
            numChars = 0;
            kdebugRemaining = 0;
            break;
        default:
            kdebugState = 0;
            numChars = 0;
            kdebugRemaining = 0;
            break;
        }
        break;
    case 1:
        if (kdebugRemaining <= 0) {
            if (*buffer == 1) {
                kdebugserver_text_0220();
                kdebugState = 0;
                numChars = 0;
                kdebugRemaining = 0;
            } else {
                kdebugState = 0;
                numChars = 0;
                kdebugRemaining = 0;
            }
            break;
        }
        break;
    default:
        kdebugState = 0;
        numChars = 0;
        kdebugRemaining = 0;
        break;
    }
}
#endif
