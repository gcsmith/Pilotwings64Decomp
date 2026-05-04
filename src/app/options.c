#include "common.h"
#include <uv_font.h>
#include <uv_geometry.h>
#include <uv_graphics.h>
#include <uv_memory.h>
#include <uv_sprite.h>
#include <uv_texture.h>
#include "kernel/code_1050.h"
#include "code_B3A70.h"
#include "credits.h"
#include "demo.h"
#include "menu.h"
#include "menu_utils.h"
#include "options.h"
#include "save.h"
#include "snap.h"
#include "snd.h"
#include "text_data.h"

STATIC_DATA f32 sVolume[] = { 0.0f, 0.2f, 0.4f, 0.6f, 1.0f };
STATIC_DATA s32 sStereoMono = 0;
STATIC_DATA s32 sSoundTrack = 0;
STATIC_DATA s32 sVolumeMusic = 4;
STATIC_DATA s32 sVolumeSfx = 4;
STATIC_DATA s32 D_8034F8F4 = 0; // unused, only ever set to 0

STATIC_DATA s16 sOptionsPanel;
STATIC_DATA s32 sStickHeld;
STATIC_DATA u8 sGameComplete; // flag to determine if game is complete
STATIC_DATA u8 sSaveFileIdx;
STATIC_DATA s32 sOptionMenuItems[5]; // menu items, at least 5

// forward declarations
void optionsInit(void);
void optionsDeinit(void);
s32 optionsMenuHandler(void); // FIXME change to Update() for consistency?
void optionsDrawPanel(void);
void optionsDrawBorder(void);
void optionsInitMain(void);
void optionsInitAlbum(void);
void optionsInitSound(void);
s32 optionsHandlerMain(void);
s32 optionsHandlerAlbum(void);
s32 optionsHandlerSound(void);
void options_80316B80(void);
void optionsSetSetting(s32, s32);
void optionsSetTrack(s32, s32);
s32 optionsItemWrap(s32 val, s32 first, s32 last);
void optionsPanel0(void);
void optionsPanel1(void);
void optionsPanel2(void);

s32 optionsTopRender(void) {
    s32 menuSel;

    sOptionsPanel = 3;
    optionsInit();
    while ((menuSel = optionsMenuHandler()) == -1) {
        uvGfxBegin();
        optionsDrawBorder();
        optionsDrawPanel();
        uvGfxEnd();
    }
    optionsDeinit();
    return menuSel;
}

void optionsInit(void) {
    D_80362690->unkC[D_80362690->unk9C].unk8A = 0;
    saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);
    sGameComplete = credits_8030CC48();

    D_80362690->unkC[D_80362690->unk9C].unk8A = 1;
    saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);

    if (sGameComplete < credits_8030CC48()) {
        sGameComplete = credits_8030CC48();
    } else {
        D_80362690->unkC[D_80362690->unk9C].unk8A = 0;
        saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);
    }
    if (sOptionsPanel == 3) {
        options_80316B80();
        sOptionsPanel = 0;
    }
    switch (sOptionsPanel) {
    case 0:
        optionsInitMain();
        break;
    case 1:
        optionsInitAlbum();
        break;
    case 2:
        optionsInitSound();
        break;
    }
    sStickHeld = 0;
}

void optionsInitMain(void) {
    s32 menuY;
    s32 count;

    saveFileLoad(D_80362690->unkC[D_80362690->unk9C].unk8A);
    if (sGameComplete != 0) {
        sOptionMenuItems[0] = TEXT_PHOTO_ALBUM;
        sOptionMenuItems[1] = TEXT_SOUND_OPTIONS;
        sOptionMenuItems[2] = TEXT_CONGURA;
        sOptionMenuItems[3] = TEXT_QUIT;
        count = 4;
        menuY = 80;
    } else {
        sOptionMenuItems[0] = TEXT_PHOTO_ALBUM;
        sOptionMenuItems[1] = TEXT_SOUND_OPTIONS;
        sOptionMenuItems[2] = TEXT_QUIT;
        count = 3;
        menuY = 100;
    }
    menuCreateItems(80, menuY, 6, 1.0f, 1.0f, sOptionMenuItems, count);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xFF, 0xFF, 0xFF);
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xFF, 0xFF, 0x00);
}

void optionsInitAlbum(void) {
    sOptionMenuItems[0] = TEXT_FILE_1;
    sOptionMenuItems[1] = TEXT_FILE_2;
    sOptionMenuItems[2] = TEXT_QUIT;
    menuCreateItems(80, 100, 6, 1.0f, 1.0f, sOptionMenuItems, 3);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xFF, 0xFF, 0xFF);
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xFF, 0xFF, 0x00);
    D_8034F8F4 = 0;
}

void optionsInitSound(void) {
    sOptionMenuItems[0] = TEXT_MODE_STEREO;
    sOptionMenuItems[1] = TEXT_STRACK;
    sOptionMenuItems[2] = TEXT_BGM_V1;
    sOptionMenuItems[3] = TEXT_SFX_V1;
    sOptionMenuItems[4] = TEXT_QUIT;
    menuCreateItems(40, 70, 6, 1.0f, 1.0f, sOptionMenuItems, 5);
    menuUtilSetColors(MENU_COLOR_ITEM, 0xFF, 0xFF, 0xFF);
    menuUtilSetColors(MENU_COLOR_SELECTED, 0xFF, 0xFF, 0);
    optionsSetSetting(0, sStereoMono);
    optionsSetTrack(1, sSoundTrack);
    optionsSetSetting(2, sVolumeMusic);
    optionsSetSetting(3, sVolumeSfx);
    menuUtilSetSoundFlags(MENU_SOUND_CHANGE | MENU_SOUND_BACK);
}

void optionsDeinit(void) {
    menuDeinit();
}

s32 optionsMenuHandler(void) {
    switch (sOptionsPanel) {
    case 0:
        return optionsHandlerMain();
    case 1:
        return optionsHandlerAlbum();
    case 2:
        return optionsHandlerSound();
    default:
        _uvDebugPrintf("option_update : unknown panel!\n");
        return 0;
    }
}

s32 optionsHandlerMain(void) {
    s32 temp_v0;
    u32 temp_t7;

    temp_v0 = menuCheckInputs();
    temp_t7 = temp_v0 + 1;
    if (sGameComplete) {
        switch (temp_t7) {
        case 1:
            sOptionsPanel = 1;
            func_8032D51C(0);
            optionsInit();
            return -1;
        case 2:
            sOptionsPanel = 2;
            func_8032D51C(0);
            optionsInit();
            return -1;
        case 3:
            func_8033FB14();
            func_8033F964(1);
            func_8032D51C(0);
            creditsMainRender();
            options_80316B80();
            optionsInitMain();
            return -1;
        case 0:
        case 4:
            func_8032D51C(0);
            return 0;
        default:
            return -1;
        }
    } else {
        switch (temp_v0) {
        case 0:
            sOptionsPanel = 1;
            func_8032D51C(0);
            optionsInit();
            return -1;
        case 1:
            sOptionsPanel = 2;
            func_8032D51C(0);
            optionsInit();
            return -1;
        case -1:
        case 2:
            func_8032D51C(0);
            return 0;
        default:
            return -1;
        }
    }
}

s32 optionsHandlerAlbum(void) {
    s32 temp_v0;

    temp_v0 = menuCheckInputs();
    switch (temp_v0) {
    case 0:
        sSaveFileIdx = 0;
        saveFileLoad(sSaveFileIdx);
        if (func_8033E3A8(0) != 0) {
            saveFileWrite(sSaveFileIdx);
        }
        options_80316B80();
        optionsInitAlbum();
        return -1;
    case 1:
        sSaveFileIdx = 1;
        saveFileLoad(sSaveFileIdx);
        if (func_8033E3A8(0) != 0) {
            saveFileWrite(sSaveFileIdx);
        }
        options_80316B80();
        optionsInitAlbum();
        menu_8030B69C(1);
        return -1;
    case 2:
        func_8032D51C(0);
        return 0;
    case -1:
        sOptionsPanel = 0;
        func_8032D51C(0);
        optionsInit();
        return -1;
    default:
        return -1;
    }
}

s32 optionsHandlerSound(void) {
    s32 sp24;
    s32 menuItem;
    s32 optInc;
    f32 stickX;

    sp24 = menuCheckInputs();
    menuItem = menu_8030B668();
    if (sp24 == -1) {
        if (menuItem != 1) {
            sOptionsPanel = 0;
            func_8032D51C(0);
            optionsInit();
            return -1;
        } else {
            D_8034F8F4 = 0;
            func_8033F964(1);
        }
    }
    optInc = 0;
    stickX = demoGetInputs(0, INPUT_AXIS_X);
    if (ABS_NOEQ(stickX) < 0.75f) {
        sStickHeld = FALSE;
    } else if (!sStickHeld) {
        if (stickX > 0.75f) {
            optInc = 1;
            sStickHeld = TRUE;
        }
        if (stickX < -0.75f) {
            optInc = -1;
            sStickHeld = TRUE;
        }
    }

    switch (menuItem) {
    case 0:
        sStereoMono += optInc;
        sStereoMono = optionsItemWrap(sStereoMono, 0, 1);
        if (sStereoMono == 0) {
            func_80200180(0, 8, 2, 0);
        } else {
            func_80200180(0, 8, 1, 0);
        }
        if (optInc != 0) {
            sndPlaySfx(0x54);
        }
        optionsSetSetting(0, sStereoMono);
        return -1;
    case 1:
        sSoundTrack += optInc;
        sSoundTrack = optionsItemWrap(sSoundTrack, 0, 30);
        if (sp24 == menuItem) {
            sndSetMusic(sSoundTrack);
            func_8033F964(0);
            func_8033FCD0(0xFF);
        }
        if (optInc != 0) {
            sndPlaySfx(0x54);
        }
        optionsSetTrack(1, sSoundTrack);
        return -1;
    case 2:
        sVolumeMusic += optInc;
        if (sVolumeMusic < 0) {
            sVolumeMusic = 0;
        } else if (sVolumeMusic >= 5) {
            sVolumeMusic = 4;
        }
        optionsSetSetting(2, sVolumeMusic);
        func_8033FA88(sVolume[sVolumeMusic]);
        func_8033FD94(0xFF, sVolume[sVolumeSfx], sVolume[sVolumeMusic]);
        return -1;
    case 3:
        sVolumeSfx += optInc;
        if (optInc != 0) {
            sndPlaySfx(SFX_UI_CONFIRM);
        }
        if (sVolumeSfx < 0) {
            sVolumeSfx = 0;
        } else if (sVolumeSfx >= 5) {
            sVolumeSfx = 4;
        }
        optionsSetSetting(3, sVolumeSfx);
        func_8033FAD4(sVolume[sVolumeSfx]);
        func_8033FD94(0xFF, sVolume[sVolumeSfx], sVolume[sVolumeMusic]);
        return -1;
    case 4:
        if (sp24 == menuItem) {
            sndPlaySfx(SFX_UI_CONFIRM);
            func_8032D51C(0);
            return 0;
        }
        return -1;
    default:
        return -1;
    }
}

void optionsDrawPanel(void) {
    switch (sOptionsPanel) {
    case 0:
        optionsPanel0();
        break;
    case 1:
        optionsPanel1();
        break;
    case 2:
        optionsPanel2();
        break;
    }
}

void optionsPanel0(void) {
    menuRender();
    uvFontGenDlist();
}

void optionsPanel1(void) {
    menuRender();
    uvFontGenDlist();
}

void optionsPanel2(void) {
    menuRender();
    uvFontGenDlist();
}

void optionsDrawBorder(void) {
    uvSprtDraw(0);
    uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
    uvVtxRect(0, SUBSCREEN_Y0, SCREEN_WIDTH - 1, 0);
    uvVtxRect(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SUBSCREEN_Y1);
    uvVtxRect(0, SUBSCREEN_Y1, SUBSCREEN_X0, SUBSCREEN_Y0);
    uvVtxRect(SUBSCREEN_X1, SUBSCREEN_Y1, SCREEN_WIDTH - 1, SUBSCREEN_Y0);
}

void options_80316B80(void) {
    uvLevelInit();
    uvLevelAppend(0x70);
    uvLevelAppend(0x2E);
    // clang-format off
    uvSprtProps(0,
        SPRT_PROP_ENABLED(TRUE),
        SPRT_PROP_POS(0, 240),
        SPRT_PROP_BLIT(BLIT_ID_43),
        SPRT_PROP_END
    );
    // clang-format on
    textLoadBlock(0x42);
}

void optionsSetSetting(s32 menuIdx, s32 setting) {
    s32 menuTextId;

    switch (menuIdx) {
    case 0:
        switch (setting) {
        case 0:
            menuTextId = TEXT_MODE_STEREO;
            break;
        case 1:
            menuTextId = TEXT_MODE_MONO;
            break;
        }
        break;
    case 2:
        switch (setting) {
        case 0:
            menuTextId = TEXT_BGM_V1;
            break;
        case 1:
            menuTextId = TEXT_BGM_V2;
            break;
        case 2:
            menuTextId = TEXT_BGM_V3;
            break;
        case 3:
            menuTextId = TEXT_BGM_V4;
            break;
        case 4:
            menuTextId = TEXT_BGM_V5;
            break;
        }
        break;
    case 3:
        switch (setting) {
        case 0:
            menuTextId = TEXT_SFX_V1;
            break;
        case 1:
            menuTextId = TEXT_SFX_V2;
            break;
        case 2:
            menuTextId = TEXT_SFX_V3;
            break;
        case 3:
            menuTextId = TEXT_SFX_V4;
            break;
        case 4:
            menuTextId = TEXT_SFX_V5;
            break;
        }
        break;
    }
    sOptionMenuItems[menuIdx] = menuTextId;
    menuSetItem(menuIdx, textGetDataByIdx(menuTextId));
}

void optionsSetTrack(s32 menuItem, s32 trackIdx) {
    s16* trackStr;

    if (menuItem == 1) {
        trackStr = textGetDataByIdx(TEXT_STRACK);
        textFmtIntAt(trackStr, trackIdx + 1, 2, 13);
        menuSetItem(1, trackStr);
    }
}

s32 optionsItemWrap(s32 val, s32 first, s32 last) {
    if (val < first) {
        val = last;
    } else if (val > last) {
        val = first;
    }
    return val;
}
