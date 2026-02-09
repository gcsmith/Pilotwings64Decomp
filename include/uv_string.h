#ifndef UV_STRING_H
#define UV_STRING_H

#include <PR/ultratypes.h>

char* uvStrchr(const char* s, int c);
u32 uvStrlen(const char* s);
int uvStrcmp(const char* s1, const char* s2);
void uvSprintf(char* dest, const char* fmt, ...);
int uvAtoi(const char*);

#endif // UV_STRING_H
