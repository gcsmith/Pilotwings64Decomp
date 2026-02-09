#include "common.h"
#include <libc/stdarg.h>
#include <PR/ultratypes.h>
#include <uv_string.h>

// forward declarations
void strFormatFloat(f32, s32*, char*, s32);
void strFormatInt(s32, s32 base, s32*, char*, s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/uvStrchr.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/uvStrlen.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/uvStrcmp.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/strFormatInt.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/strFormatFloat.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/strDigitToChar.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/strCharToDigit.s")

void uvSprintf(char* dest, const char* fmt, ...) {
    s32 srcBufPos;
    s32 j;
    s32 destBufPos;
    char padStrBuf[0x5C];
    char* argStr;
    s32 arg;
    s32 padCount;
    int hasPadding;
    int leftJustify;
    u8 c;
    int parseSpecifier;
    va_list args;

    c = fmt[0];
    va_start(args, fmt);
    parseSpecifier = FALSE;
    srcBufPos = 0;
    destBufPos = 0;
    while (c != 0) {
        if (!parseSpecifier) {
            if (c == '%') {
                padCount = -1;
                leftJustify = FALSE;
                hasPadding = FALSE;
                parseSpecifier = TRUE;
            } else {
                dest[destBufPos] = c;
                destBufPos++;
            }
        } else {
            if (c == '-') {
                srcBufPos++;
                c = fmt[srcBufPos];
                leftJustify = TRUE;
            }
            if (c == '\0') {
                break;
            }
            if (c == '0') {
                srcBufPos++;
                c = fmt[srcBufPos];
                hasPadding = TRUE;
            }
            if (c == '\0') {
                break;
            }
            if ((c >= '1') && (c <= '9')) {
                j = 0;
                while ((c >= '0') && (c <= '9')) {
                    padStrBuf[j] = c;
                    srcBufPos++;
                    j++;
                    c = fmt[srcBufPos];
                }
                padStrBuf[j] = '\0';
                padCount = uvAtoi(padStrBuf);
            }
            if (c == '\0') {
                break;
            }
            if (c == '.') {
                srcBufPos++;
                j = 0;
                c = fmt[srcBufPos];
                while ((c >= '0') && (c <= '9')) {
                    padStrBuf[j] = c;
                    srcBufPos++;
                    j++;
                    c = fmt[srcBufPos];
                }
                padStrBuf[j] = '\0';
            }
            if (c == '\0') {
                break;
            }
            if (c == 'x') {
                arg = va_arg(args, s32);
                strFormatInt(arg, 16, &destBufPos, dest, padCount, leftJustify, hasPadding);
                parseSpecifier = FALSE;
            } else if (c == 'd') {
                arg = va_arg(args, s32);
                strFormatInt(arg, 10, &destBufPos, dest, padCount, leftJustify, hasPadding);
                parseSpecifier = FALSE;
            } else if (c == 'b') {
                arg = va_arg(args, s32);
                strFormatInt(arg, 2, &destBufPos, dest, padCount, leftJustify, hasPadding);
                parseSpecifier = FALSE;
            } else if (c == 'f') {
                strFormatFloat(va_arg(args, f64), &destBufPos, dest, c);
                parseSpecifier = FALSE;
            } else if (c == 's') {
                argStr = arg = va_arg(args, char*);
                parseSpecifier = FALSE;
                while (*argStr != 0) {
                    dest[destBufPos] = *argStr++;
                    destBufPos++;
                }
            }
        }
        srcBufPos++;
        c = fmt[srcBufPos];
    }
    dest[destBufPos] = 0;
    va_end(args);
}

#pragma GLOBAL_ASM("asm/nonmatchings/kernel/string/uvAtoi.s")
