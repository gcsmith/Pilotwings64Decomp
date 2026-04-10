#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

static u8 kdebugBuffer[0x100];
OSThread __osThreadSave;

static s32 kdebugState = 0;
static s32 numChars = 0;
static s32 kdebugRemaining = 0;

UNUSED STATIC_FUNC void kdebug_u32_to_string(u32 u, u8* s) {
    s[0] = ((u >> 24) & 0xFF);
    s[1] = ((u >> 16) & 0xFF);
    s[2] = ((u >> 8) & 0xFF);
    s[3] = (u & 0xFF);
}

STATIC_FUNC u32 kdebug_string_to_u32(u8* s) {
    u32 k;

    k = ((s[0] & 0xFF) << 0x18);
    k |= ((s[1] & 0xFF) << 0x10);
    k |= ((s[2] & 0xFF) << 0x8);
    k |= (s[3] & 0xFF);

    return k;
}

// similar to send_packet(), except for:
//   a. different `type` bitfield width
//   b. also waits on __osGetCause()
STATIC_FUNC void kdebug_send_packet(u8* buf, s32 length) {
    rdbPacket packet;
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
STATIC_FUNC void kdebug_send(u8* buf, s32 length) {
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
        kdebug_send_packet(&buf[i], 3);
    }
    if (remainder > 0) {
        kdebug_send_packet(&buf[lengthAlign3], remainder);
    }
}

STATIC_FUNC void kdebug_send_buffer(void) {
    s32 addr;
    s32 length;

    addr = kdebug_string_to_u32(&kdebugBuffer[1]);
    length = kdebug_string_to_u32(&kdebugBuffer[5]);
    kdebug_send((u8*)addr, length);
}

STATIC_FUNC void kdebug_send_thread(void) {
    kdebug_send((u8*)&__osThreadSave.context, sizeof(__osThreadSave.context));
}

void kdebugserver(u32 rawPacket) {
    u32 i;
    rdbPacket packet;

    *(u32*)&packet = rawPacket;

    for (i = 0; i < packet.length; i++) {
        kdebugBuffer[numChars++] = packet.buf[i];
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
            kdebug_send_thread();
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
            if (kdebugBuffer[0] == 1) {
                kdebug_send_buffer();
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
