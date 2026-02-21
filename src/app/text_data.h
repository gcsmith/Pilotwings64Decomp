#ifndef APP_TEXT_DATA_H
#define APP_TEXT_DATA_H

#include <PR/ultratypes.h>

// load TEXT and DATA blocks for id
void textLoadBlock(s32 id);

// searches for needle in NAME list
// returns correlated string from DATA list, or NULL if not found
s16* textGetDataByName(s16* needle);

// returns DATA string at index idx, or NULL if index too high
s16* textGetDataByIdx(s32 idx);

// formats integer `val` as PW64 string, padding to length
// only supports values [0-999]
s32 textFmtInt(s16* dst, s32 val, s32 length);

// formats int as PW64 string like textFormatInt, but additional offset in dst buffer
s32 textFmtIntAt(s16* dst, s32 val, s32 length, s32 dstOffset);

#endif // APP_TEXT_DATA_H
