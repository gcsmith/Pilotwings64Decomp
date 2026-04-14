#ifndef PILOTWINGS64_UV_SPRITE
#define PILOTWINGS64_UV_SPRITE

#include <PR/sp.h>
#include <uv_util.h>
#include <uv_graphics.h>

enum SpriteBlitId {
    BLIT_ID_04                          = 0x04,
    BLIT_ID_05                          = 0x05,
    BLIT_ID_06                          = 0x06,
    BLIT_ID_07                          = 0x07,
    BLIT_ID_08                          = 0x08,
    BLIT_ID_09                          = 0x09,
    BLIT_ID_0A                          = 0x0A,
    BLIT_ID_0B                          = 0x0B,
    BLIT_ID_0C                          = 0x0C,
    BLIT_TEST_MENU_TOP_SCORE            = 0x0D, // "Top Score" box title
    BLIT_TEST_MENU_BUTTON_START         = 0x0E, // "Start" button
    BLIT_TEST_MENU_BUTTON_SCORING       = 0x0F, // "Scoring" button
    BLIT_TEST_MENU_BUTTON_VIEW_MAP      = 0x10, // "View map" button
    BLIT_TEST_MENU_BUTTON_CONTROL       = 0x11, // "Control" button
    BLIT_TEST_MENU_BUTTON_HINT          = 0x12, // "Hint" button
    BLIT_TEST_MENU_BUTTON_SAMPLE_PHOTO  = 0x13, // "Sample photo" button
    BLIT_TEST_MENU_BUTTON_RETURN        = 0x14, // "Return" button
    BLIT_TEST_MENU_TEST_TITLE           = 0x15, // "TEST" box title
    BLIT_ID_16                          = 0x16,
    BLIT_ID_17                          = 0x17,
    BLIT_ID_18                          = 0x18,
    BLIT_ID_19                          = 0x19,
    BLIT_ID_1A                          = 0x1A,
    BLIT_ID_1B                          = 0x1B,
    BLIT_ID_1E                          = 0x1E,
    BLIT_ID_1F                          = 0x1F,
    BLIT_ID_20                          = 0x20,
    BLIT_ID_21                          = 0x21,
    BLIT_ID_22                          = 0x22,
    BLIT_ID_23                          = 0x23,
    BLIT_ID_24                          = 0x24,
    BLIT_ID_25                          = 0x25,
    BLIT_ID_26                          = 0x26,
    BLIT_ID_27                          = 0x27,
    BLIT_ID_28                          = 0x28,
    BLIT_ID_29                          = 0x29,
    BLIT_ID_2A                          = 0x2A,
    BLIT_ID_2B                          = 0x2B,
    BLIT_ID_2C                          = 0x2C,
    BLIT_ID_2D                          = 0x2D,
    BLIT_WAYPOINT_CURRENT_POSITION      = 0x2E, // "Current position"
    BLIT_WAYPOINT_LANDING_POINT         = 0x2F, // "Landing point"
    BLIT_WAYPOINT_RUNWAY                = 0x30, // "Runway"
    BLIT_WAYPOINT_TARGET                = 0x31, // "Target"
    BLIT_WAYPOINT_MECHA_HAWK            = 0x32, // "Mecha Hawk"
    BLIT_WAYPOINT_GOAL                  = 0x33, // "Goal"
    BLIT_WAYPOINT_WHALE                 = 0x34, // "Whale"
    BLIT_WAYPOINT_SPACE_SHUTTLE         = 0x35, // "Space shuttle"
    BLIT_WAYPOINT_PASSENGER_BOAT        = 0x36, // "Passenger boat"
    BLIT_WAYPOINT_FOUNTAIN              = 0x37, // "Fountain"
    BLIT_WAYPOINT_FLAME                 = 0x38, // "Flame"
    BLIT_WAYPOINT_MISSI_THE_MONSTER     = 0x39, // "Missi the Monster"
    BLIT_WAYPOINT_NEXT_JP               = 0x3A, // Japanese "next goal"
    BLIT_N64_CONTROLLER_INFOGRAPHIC     = 0x3B, // N64 controller infographic
    BLIT_TEST_MENU_BUTTON_VIEW_DEMO     = 0x3C, // "View demo" button
    BLIT_ID_3D                          = 0x3D,
    BLIT_ID_3E                          = 0x3E,
    BLIT_ID_3F                          = 0x3F,
    BLIT_ID_40                          = 0x40,
    BLIT_ID_42                          = 0x42,
    BLIT_ID_43                          = 0x43,
    BLIT_ID_48                          = 0x48,
    BLIT_ID_49                          = 0x49,
    BLIT_ID_4A                          = 0x4A,
    BLIT_ID_4B                          = 0x4B,
    BLIT_WAYPOINT_NEXT                  = 0x4C, // "Next" waypoint for next ring / hover pad
    BLIT_CONT_INFO_FLARE_LANDING        = 0x4D, // "Flare (use for air brake or landing)"
    BLIT_CONT_INFO_Z_BUTTON             = 0x4E, // "( [Z] )" button callout
    BLIT_CONT_INFO_SNAP_PHOTO           = 0x4F, // "Snap photo"
    BLIT_CONT_INFO_CONTROL_VEHICLE      = 0x50, // "Control the vehicle"
    BLIT_CONT_INFO_DEC_THROTTLE         = 0x51, // "Decrease throttle setting"
    BLIT_CONT_INFO_INC_THROTTLE         = 0x52, // "Increase throttle setting"
    BLIT_CONT_INFO_FIRE_MISSILES        = 0x53, // "Fire missiles"
    BLIT_CONT_INFO_WEAK_JET             = 0x54, // "Weak jet"
    BLIT_CONT_INFO_STRONG_JET           = 0x55, // "Strong jet"
    BLIT_CONT_INFO_AIR_BRAKE            = 0x56, // "Air brake / Hover"
    BLIT_CONT_INFO_FIRE                 = 0x57, // "Fire"
    BLIT_CONT_INFO_ADJUST_FIRE          = 0x58, // "Adjust fire angle & Move cannon left / right"
    BLIT_CONT_INFO_FLARE                = 0x59, // "Flare (Use for air brake)"
    BLIT_CONT_INFO_OPEN_CHUTE           = 0x5A, // "Open chute"
    BLIT_CONT_INFO_TILT_BACKWARD        = 0x5B, // "Tilt backward"
    BLIT_CONT_INFO_TILT_FORWARD         = 0x5C, // "Tilt forward"
    BLIT_CONT_INFO_TURN_LEFT_RIGHT      = 0x5D, // "Turn left / right"
    BLIT_CONT_INFO_LEFT_RIGHT_ARROWS    = 0x5E, // "<- ->"
    BLIT_CONT_INFO_UP_ARROW             = 0x5F, // "↑"
    BLIT_CONT_INFO_DOWN_ARROW           = 0x60, // "↓"
    BLIT_CONT_INFO_CHANGE_JUMP_ALTITUDE = 0x61, // "Change the altitude of jump"
    BLIT_CONT_INFO_ADJUST_LEFT_RIGHT    = 0x62, // "Adjust left and right directions"
    BLIT_CONT_INFO_ADJUST_JUMP_ANGLES   = 0x63, // "Adjust angles for jumping
    BLIT_CONT_INFO_FLAP_WINGS           = 0x64, // "Flap the wings"
    BLIT_CONT_INFO_BRAKE_HOVER          = 0x65, // "Brake / Hover"
};

#define SPRT_PROPID_END             0
#define SPRT_PROPID_DIM             1  // type:s32,s32
#define SPRT_PROPID_POS             2  // type:s32,s32
#define SPRT_PROPID_ENABLED         3  // type:s32
#define SPRT_PROPID_TEX_ID          5  // type:s32
#define SPRT_PROPID_COLOR           7  // type:s32,s32,s32,s32
#define SPRT_PROPID_BITMAP          8  // type:s32
#define SPRT_PROPID_BLIT            9  // type:s32
#define SPRT_PROPID_FAST_COPY       10 // type:s32
#define SPRT_PROPID_TRANSPARENT     11 // type:s32

#define SPRT_PROP_END               SPRT_PROPID_END
#define SPRT_PROP_DIM(w, h)         SPRT_PROPID_DIM, (w), (h)
#define SPRT_PROP_POS(x, y)         SPRT_PROPID_POS, (x), (y)
#define SPRT_PROP_ENABLED(x)        SPRT_PROPID_ENABLED, (x)
#define SPRT_PROP_TEX_ID(x)         SPRT_PROPID_TEX_ID, (x)
#define SPRT_PROP_COLOR(r, g, b, a) SPRT_PROPID_COLOR, (r), (g), (b), (a)
#define SPRT_PROP_BITMAP(x)         SPRT_PROPID_BITMAP, (x)
#define SPRT_PROP_BLIT(x)           SPRT_PROPID_BLIT, (x)
#define SPRT_PROP_FAST_COPY(x)      SPRT_PROPID_FAST_COPY, (x)
#define SPRT_PROP_TRANSPARENT(x)    SPRT_PROPID_TRANSPARENT, (x)

typedef struct {
/* 00 */ u8 enabled;
/* 01 */ u8 skipped; // skips drawing in uvSprtDrawAll(), but never used?
/* 02 */ s16 width;
/* 04 */ s16 height;
/* 06 */ s16 xpos;
/* 08 */ s16 ypos;
/* 0A */ u16 textureId;
/* 0C */ u8 red;
/* 0D */ u8 green;
/* 0E */ u8 blue;
/* 0F */ u8 alpha;
/* 10 */ Bitmap* bitmap;
/* 14 */ Sprite sprite;
/* 58 */ Gfx* dlist[2];
} uvSprite_t; // size 0x60

void uvSprt_80230130(void);
void uvSprt_802301A4(void);
void _uvTxtDraw(s32 textureId);
void uvSprtFromBitmap(uvSprite_t* sprite, ParsedUVTX* uvtx);
void uvSprt_80230750(uvSprite_t* sprite, ParsedUVTX* uvtx);
s32  uvSprtFindFree(void);
void uvSprtInit(void);
void uvSprtDisplayList(uvSprite_t* sprite);
void uvSprtDrawAll(void);
void uvSprtDraw(s32 spriteId);
void uvSprtSetBlit(uvSprite_t* sprite, s32 blitId);
s16  uvSprtGetWidth(s32 spriteId);
s16  uvSprtGetHeight(s32 spriteId);
void uvSprtProps(s32 spriteId, ...);
void uvSprtUpdateUnk(ParsedUVTX* uvtx);
void uvSprtResetUnk(void);

#endif // PILOTWINGS64_UV_SPRITE

