#include "asm.h"

.section .text, "ax"

LEAF(aspMainTextStart)
.incbin "rsp/aspMain.textbin.bin"
END(aspMainTextStart)
EXPORT(aspMainTextEnd)

.section .rodata, "a"

SYM_START(aspMainDataStart)
.incbin "rsp/aspMain.databin.bin"
SYM_END(aspMainDataStart)
EXPORT(aspMainDataEnd)
