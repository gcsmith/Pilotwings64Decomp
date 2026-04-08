#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 osEepromProbe(OSMesgQueue* mq) {
    s32 ret;
    OSContStatus sdata;

    ret = 0;
    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if ((ret == 0) && (sdata.type & CONT_EEPROM)) {
        ret = 1;
    } else {
        ret = 0;
    }
    __osSiRelAccess();
    return ret;
}

