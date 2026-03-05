#include "common.h"
#include <libc/stdarg.h>
#include <PR/ultratypes.h>
#include <uv_string.h>

char* uvStrchr(const char* s, const char c) {
    while (*s != '\0' && c != *s) {
        s++;
    }
    if (*s != 0) {
        return (char*)s;
    }
    return NULL;
}

u32 uvStrlen(const char* s) {
    s32 len;

    len = 0;
    while (*s++ != 0) {
        len++;
    }
    return len;
}

int uvStrcmp(const char* s1, const char* s2) {
    s32 len1;
    s32 len2;
    s32 i;

    len1 = uvStrlen(s1);
    len2 = uvStrlen(s2);

    if (len1 < len2) {
        return -1;
    }
    if (len2 < len1) {
        return 1;
    }

    for (i = 0; i < len1; i++) {
        if (*s1 < *s2) {
            return -1;
        }
        if (*s1 > *s2) {
            return 1;
        }

        s1++;
        s2++;
    }

    return 0;
}

void strFormatInt(s32 number, u16 base, s32* bufPosPtr, char* strBuf, s32 padCount, s32 leftJustify, s32 hasZeroPadding) {
    u16 digit;
    u16 numDigits;
    s32 outputLength;
    s32 bufPos;
    u16 isNegative;
    s32 i;
    s32 digitsRemaining;
    s32 inputLengthRemaining;
    s32 outputLengthRemaining;

    bufPos = *bufPosPtr;
    if (number < 0) {
        isNegative = TRUE;
        number = -number;
    } else {
        isNegative = FALSE;
    }
    numDigits = 0;
    i = 1;
    if (number != 0) {
        while (number >= i) {
            numDigits++;
            i *= base;
        }
    } else {
        numDigits = 1;
    }

    if (padCount > 0) {
        outputLength = padCount;
    } else {
        outputLength = numDigits + isNegative;
    }
    bufPos += outputLength;
    bufPos--;
    outputLengthRemaining = outputLength;
    digitsRemaining = numDigits;
    inputLengthRemaining = numDigits + isNegative;
    if (leftJustify) {
        for (i = 0; i < outputLength; i++) {
            if (inputLengthRemaining < outputLengthRemaining) {
                strBuf[bufPos--] = ' ';
                outputLengthRemaining--;
            } else if (digitsRemaining > 0) {
                digit = number % base;
                strBuf[bufPos--] = strDigitToChar(digit);
                number = (number - digit) / base;
                digitsRemaining--;
                outputLengthRemaining--;
                inputLengthRemaining--;
            } else if (inputLengthRemaining == 1) {
                strBuf[bufPos--] = ' ';
            }
        }
    } else {
        for (i = 0; i < outputLength; i++) {
            if (digitsRemaining > 0) {
                digit = number % base;
                strBuf[bufPos--] = strDigitToChar(digit);
                number = (number - digit) / base;
            } else {
                if (hasZeroPadding) {
                    if ((i == outputLength - 1) && isNegative) {
                        strBuf[bufPos--] = '-';
                    } else {
                        strBuf[bufPos--] = '0';
                    }
                } else {
                    if ((digitsRemaining == 0) && isNegative) {
                        strBuf[bufPos--] = '-';
                    } else {
                        strBuf[bufPos--] = ' ';
                    }
                }
            }
            digitsRemaining--;
        }
    }
    bufPos += outputLength;
    bufPos++;
    *bufPosPtr = bufPos;
}

void strFormatFloat(f32 number, s32* bufPosPtr, char* strBuf) {
    f32 decimalPart;
    u16 digit;
    s32 i;
    s32 integerPart;
    u16 isNegative;
    u16 numDigits;
    s32 bufPos;

    bufPos = *bufPosPtr;
    if (number < 0.0f) {
        isNegative = TRUE;
        number = -number;
    } else {
        isNegative = FALSE;
    }
    integerPart = (s32)number;
    numDigits = 0;
    i = 1;
    if (integerPart != 0) {
        while (integerPart >= i) {
            numDigits++;
            i *= 10;
        }
    } else {
        numDigits = 1;
    }
    bufPos += numDigits + isNegative;
    strBuf[bufPos++] = '.';
    decimalPart = number - integerPart;

    for (i = 0; i < 2; i++) {
        decimalPart *= 10.0f;
        digit = (s32)decimalPart;
        decimalPart -= digit;
        strBuf[bufPos++] = strDigitToChar(digit);
    }
    bufPos -= 4;

    for (i = 0; i < numDigits; i++) {
        digit = integerPart % 10;
        strBuf[bufPos--] = strDigitToChar(digit);
        integerPart = (integerPart - digit) / 10;
    }
    if (isNegative) {
        strBuf[bufPos--] = '-';
    }
    bufPos += numDigits + isNegative + 4;
    *bufPosPtr = bufPos;
}

char strDigitToChar(u16 digit) {
    if (digit < 10) {
        return '0' + digit;
    }
    return ' ';
}

s32 strCharToDigit(char digitChar) {
    if ((digitChar >= '0') && (digitChar <= '9')) {
        return digitChar - '0';
    }
    return 0;
}

void uvSprintf(char* dest, const char* fmt, ...) {
    s32 srcBufPos;
    s32 j;
    s32 destBufPos;
    char padStrBuf[0x5C];
    char* argStr;
    s32 arg;
    s32 padCount;
    int hasZeroPadding;
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
                hasZeroPadding = FALSE;
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
                hasZeroPadding = TRUE;
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
                strFormatInt(arg, 16, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'd') {
                arg = va_arg(args, s32);
                strFormatInt(arg, 10, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'b') {
                arg = va_arg(args, s32);
                strFormatInt(arg, 2, &destBufPos, dest, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (c == 'f') {
                strFormatFloat(va_arg(args, f64), &destBufPos, dest);
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

int uvAtoi(const char* s) {
    s32 len;
    s32 i;
    s32 number;

    len = uvStrlen(s);
    number = 0;

    for (i = 0; i < len; i++) {
        number *= 10;
        number += strCharToDigit(s[i]);
    }
    return number;
}
