#ifndef UV_STRING_H
#define UV_STRING_H

#include <PR/ultratypes.h>

char* uvStrchr(const char* s, const char c);
u32 uvStrlen(const char* s);
int uvStrcmp(const char* s1, const char* s2);
void strFormatFloat(f32 number, s32 *bufPosPtr, char* strBuf);
void strFormatInt(s32 number, u16 base, s32 *bufPosPtr, char* strBuf, s32 padCount, s32 leftJustify, s32 hasZeroPadding);
char strDigitToChar(u16 digit);
void uvSprintf(char* dest, const char* fmt, ...);
int uvAtoi(const char* s);

#endif // UV_STRING_H
