#ifndef UV_DOBJ_H
#define UV_DOBJ_H

#include <PR/ultratypes.h>
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_sched.h>

enum Models {
    MODEL_HOLIDAY_ISLAND_FULL_MAP                                    = 0x000, // Holiday Island Full Map (0xe5138)
    MODEL_WHITE_SAIL_BOAT                                            = 0x001, // White Sail Boat with Red logo
    MODEL_BLUE_CUBOID                                                = 0x002, // Blue Cuboid
    MODEL_YELLOW_SPEED_BOAT                                          = 0x003, // Yellow Speed Boat
    MODEL_BUILDINGS_NEAR_CARNIVAL                                    = 0x004, // Brown+Green Building near carnival
    MODEL_BUILDINGS_NEAR_BEACH                                       = 0x005, // Tiki Hut / Hay roof building near beach
    MODEL_CIRCUS_TENTS                                               = 0x006, // Yellow/Blue Circus Tent
    MODEL_BUILDING_WITH_FERRIS_WHEEL                                 = 0x007, // Long building near ferris wheel
    MODEL_SMALL_BUILDING_SIDE                                        = 0x008, // Small side of building
    MODEL_MERRY_GO_ROUND                                             = 0x009, // Merry-go-round
    MODEL_CASTLE                                                     = 0x00A, // Castle on peak of map
    MODEL_ENTRY_FLAG_BUILDING                                        = 0x00B, // Three Entry flag building
    MODEL_FERRIS_WHEEL                                               = 0x00C, // Ferris wheel
    MODEL_WATER_WHEEL                                                = 0x00D, // Water wheel
    MODEL_BRIDGE_BRICK                                               = 0x00E, // Bridge brick
    MODEL_BRIDGE_BRICK_LONG_WHITE                                    = 0x00F, // Bridge brick, long white
    MODEL_OLD_BUILDING_IN_TOWN                                       = 0x010, // Old building in small town
    MODEL_BUILDING_11                                                = 0x011, // Another building
    MODEL_BUILDING_12                                                = 0x012, // And another building
    MODEL_BUILDING_NEAR_AIRPORT                                      = 0x013, // Big white building near airport
    MODEL_HOUSE_WITH_SMOKE_STACK                                     = 0x014, // Small house with smoke stack
    MODEL_LIGHTHOUSE                                                 = 0x015, // Lighthouse building
    MODEL_CASTLE_YARD                                                = 0x016, // Castle "yard"
    MODEL_AIRPORT_ATC                                                = 0x017, // Aiport ATC building
    MODEL_PALM_TREE                                                  = 0x018, // Palm tree
    MODEL_FIVE_PALM_TREES                                            = 0x019, // 5 palm trees
    MODEL_RED_SAILBOAT                                               = 0x01A, // Red sailboat
    MODEL_YELLOW_WHITE_PLANE                                         = 0x01B, // Yellow white plane
    MODEL_BEACH_UMBRELLAS_AND_TOWELS                                 = 0x01C, // Beach umbrealls and towels
    MODEL_BARN                                                       = 0x01D, // Barn-looking building
    MODEL_SMALL_WHITE_SHACK                                          = 0x01E, // Small white building/shack
    MODEL_YELLOW_N64_FLAG                                            = 0x01F, // Yellow N64 flag
    MODEL_TIKI_HUT                                                   = 0x020, // Tiki hut
    MODEL_STREET_LAMP_POST                                           = 0x021, // Street lamp post
    MODEL_TREE                                                       = 0x022, // Tree
    MODEL_SMALLER_TREE                                               = 0x023, // Smaller tree
    MODEL_TALL_TREE                                                  = 0x024, // Tall tree
    MODEL_ENTRANCE_ARCH_BUILDING                                     = 0x025, // Entrance arch building with N64 logo flags
    MODEL_DOUBLE_WATER_FOUNTAIN                                      = 0x026, // Double water fountain
    MODEL_BIG_WHITE_RED_PLANE                                        = 0x027, // Big white/red plane
    MODEL_LOW_POLY_INTRO_CRESCENT_ISLAND                             = 0x028, // Low poly intro crescent island (0xff040) -> also "full poly" when in game? LOD?
    MODEL_YACHT_BOATS                                                = 0x029, // Red/White/Blue yacht/boat
    MODEL_WHITE_YELLOW_SAILBOAT                                      = 0x02A, // White/Yellow sailboat
    MODEL_ROCK_ARCH                                                  = 0x02B, // Rock arch
    MODEL_ROCK_POST                                                  = 0x02C, // Another rock post
    MODEL_TALL_ROCK                                                  = 0x02D, // Tall rock
    MODEL_SMALL_ROCK                                                 = 0x02E, // Small rock
    MODEL_BIG_ROCK                                                   = 0x02F, // Big rock
    MODEL_SMALL_ROCK2                                                = 0x030, // Small rock

    MODEL_40                                                         = 0x040,
    MODEL_PLANTER_BOX                                                = 0x041, // Planter box thing?

    MODEL_AIRCRAFT_HANGAR                                            = 0x048, // Aircraft hangar

    MODEL_LITTLE_STATES_FULL_MAP                                     = 0x051, // Little States Full map (0x1114fc)
    MODEL_BIG_CRUISE_SHIP                                            = 0x052, // Big Cruise Ship
    MODEL_WIND_TURBINE                                               = 0x053, // Wind Turbine

    MODEL_SPACE_SHUTTLE                                              = 0x056, // Space Shuttle
    MODEL_BIG_RED_SQUARE                                             = 0x057, // Big red square?
    MODEL_NESSIES_HEAD                                               = 0x058, // Nessie's head

    MODEL_VERY_TALL_BUILDING                                         = 0x064, // Very tall building
    MODEL_BUILDING_WITH_7_FLAGS_IN_FRONT                             = 0x065, // Building with 7 flags in front
    MODEL_STATUE_OF_LIBERTY                                          = 0x066, // Statue of Liberty (0x12c238)

    MODEL_LARGE_AIRPLANE_HANGER                                      = 0x077, // Large Airplane Hanger (0x1004)

    MODEL_RED_BARN_AND_SILO                                          = 0x07F, // Red barn and silo

    MODEL_ANOTHER_BUILDING_NEAR_WHITEHOUSE                           = 0x081, // another building near whitehouse
    MODEL_WASHINGTON_MONUMENT                                        = 0x082, // Washington Monument
    MODEL_SPACE_SHUTTLE_LAUNCH_DOCK                                  = 0x083, // Space Shuttle launch dock
    MODEL_GAS_STATION                                                = 0x084, // Gas Station (?)
    MODEL_US_WHITE_HOUSE                                             = 0x085, // US White House (0x13ab4c)
    MODEL_ANOTHER_IRREGULARLY_SHAPED_DC_BUILDING                     = 0x086, // Another irregularly shaped DC building

    MODEL_EVER_FROST_ISLAND_FULL_MAP                                 = 0x0A5, // Ever-Frost Island Full map (0x149084)

    MODEL_BUILDING_WITH_PIPES                                        = 0x0BF, // Building with pipes (0x16182c)

    MODEL_HG_WIND_SOCK                                               = 0x0C7, // HG "Wind Sock"
    MODEL_YELLOW_3D_ARROW_POINTING                                   = 0x0C8, // Yellow 3d Arrow pointing
    MODEL_RED_3D_ARROW_POINTING_DOWN                                 = 0x0C9, // Red 3D Arrow pointing down.
    MODEL_YELLOW_CUBE                                                = 0x0CA, // Yellow Cube
    MODEL_RED_CUBE                                                   = 0x0CB, // Red Cube
    MODEL_BLUE_CUBE                                                  = 0x0CC, // Blue Cube
    MODEL_PILOTWINGS_3D_LOGO                                         = 0x0CD, // "Pilotwings" 3D Logo (0x166184)
    MODEL_GREEN_3D_ARROW_THING                                       = 0x0CE, // Green 3D Arrow thing
    MODEL_CANON_ON_A_TALL_RED_PEDESTAL                               = 0x0CF, // Canon on a tall red pedestal

    MODEL_GREEN_BALL_OR_JUMBLE_HOPPER_GOAL                           = 0x0D1, // Green Ball or Jumble Hopper goal

    MODEL_MECCA_HAWK                                                 = 0x0D3, // Mecca Hawk
    MODEL_LANDING_PAD_EMPTY_NO_TARGET                                = 0x0D4, // Yellow-stripe-bordered landing pad (empty, no target)
    MODEL_D5                                                         = 0x0D5,
    MODEL_D6                                                         = 0x0D6,
    MODEL_D7                                                         = 0x0D7,
    MODEL_D8                                                         = 0x0D8,
    MODEL_FIRST_RING_YELLOW                                          = 0x0D9, // First ring (Yellow)

    MODEL_YELLOW_RING                                                = 0x0E1, // Yellow Ring
    MODEL_RED_RING                                                   = 0x0E2, // Red Ring

    MODEL_BONUS_STAR                                                 = 0x0F2, // Bonus star

    MODEL_ORANGE_BALL                                                = 0x0F4, // Orange ball

    MODEL_F7                                                         = 0x0F7,
    MODEL_F8                                                         = 0x0F8,
    MODEL_F9                                                         = 0x0F9,

    MODEL_GIANT_TRANSPARENT_MECCA_HAWK                               = 0x0FD, // Giant transparent Mecca Hawk
    MODEL_GIANT_RED_THING                                            = 0x0FE, // Giant red... thing?
    MODEL_BIG_ROCK_BOULDER                                           = 0x0FF, // Big Rock/Boulder
    MODEL_GIANT_ICEBERG                                              = 0x100, // Giant Iceberg?
    MODEL_HG_THERMAL_CYLINDER                                        = 0x101, // HG thermal cylinder
    MODEL_RP_HG_LANDING_PAD                                          = 0x102, // RP/HG landing pad
    MODEL_LANDING_PAD_WITH_RED_TARGET                                = 0x103, // Landing Pad with Red Target

    MODEL_105                                                        = 0x105,

    MODEL_LOW_RES_GOOSE_HG                                           = 0x10B, // Low Res Goose HG Model

    MODEL_BREAKS_NO_CLIP                                             = 0x112, // ???? Breaks NoClip

    MODEL_LARK_RP                                                    = 0x11E, // Lark RP Model
    MODEL_ROUND_SHADOW                                               = 0x11F, // Round Shadow?
    MODEL_SHADOW_COLUMN_RP                                           = 0x120, // Shadow (Column? RP?)
    MODEL_MULTI_COLORED_CUBE                                         = 0x121, // Multi-colored cube

    MODEL_LARK_GYRO                                                  = 0x127, // Lark Gyro Model

    MODEL_GOOSE_GYRO                                                 = 0x12B, // Goose Gyro Model
    MODEL_HAWK_GYRO                                                  = 0x12D, // Hawk Gyro Model

    MODEL_KIWI_GYRO                                                  = 0x12F, // Kiwi Gyro Model

    MODEL_IBIS_GYRO                                                  = 0x131, // Ibis Gyro Model

    MODEL_ROBYN_GYRO                                                 = 0x133, // Robyn Gyro Model

    MODEL_135                                                        = 0x135,
    MODEL_136                                                        = 0x136,
    MODEL_137                                                        = 0x137,
    MODEL_138                                                        = 0x138,
    MODEL_139                                                        = 0x139,
    MODEL_13A                                                        = 0x13A,

    MODEL_BIRDMAN_ROBIN                                              = 0x142, // Birdman Robin model
    MODEL_SKYDIVING_LARK                                             = 0x143, // Skydiving Lark Model
    MODEL_PARACHUTE_LARK                                             = 0x144, // Parachute Lark model
    MODEL_SKYDIVING_PINK_GIRL                                        = 0x145, // Skydiving pink girl model
    MODEL_SKYDIVING_ISIS                                             = 0x146, // Skydiving Isis model
    MODEL_SKYDIVING_ROBIN                                            = 0x147, // Skydiving Robin model
    MODEL_SKYDIVING_SHADOW_OF_PLAYER                                 = 0x148, // Skydiving "shadow" of player
    MODEL_SKYDIVING_GOOSE                                            = 0x149, // Skydiving Goose model
    MODEL_PARACHUTE_GOOSE                                            = 0x14A, // Parachute Goose model
    MODEL_SKYDIVING_HAWK_                                            = 0x14B, // Skydiving Hawk  model
    MODEL_PARACHUTE_HAWK                                             = 0x14C, // Parachute Hawk Model
    MODEL_PARACHUTE_PINK_GIRL                                        = 0x14D, // Parachute pink girl model
    MODEL_PARACHUTE_ISIS                                             = 0x14E, // Parachute Isis model
    MODEL_PARACUTE_ROBIN                                             = 0x14F, // Paracute Robin model
    MODEL_JUMBLE_HOPPER_LARK                                         = 0x150, // Jumble Hopper Lark
    MODEL_ROUND_SHADOW2                                              = 0x151, // Round shadow

    MODEL_JUMBLE_HOPPER_KIWI                                         = 0x154, // Jumble Hopper Kiwi
    MODEL_JUMBLE_HOPPER_IBIS                                         = 0x155, // Jumble Hopper Ibis
    MODEL_JUMBLE_HOPPER_ROBYN                                        = 0x156, // Jumble Hopper Robyn
    MODEL_PILOTWINGS_SWOOSH_FEATHER_THING                            = 0x157, // Pilotwings Swoosh/feather thing
    MODEL_3D_6_IN_INTRO_PW64_LOGO                                    = 0x158, // 3D "6" in intro PW64 logo
    MODEL_3D_4_IN_INTRO_PW64_LOGO                                    = 0x159, // 3D "4" in intro PW64 logo
    MODEL_LARK_BODY_CHARACTER_SELECT                                 = 0x15A, // Lark body model (character select)
    MODEL_GOOSE_BODY                                                 = 0x15B, // Goose body model
    MODEL_HAWK_BODY                                                  = 0x15C, // Hawk body model
    MODEL_KIWI_BODY                                                  = 0x15D, // Kiwi body model
    MODEL_IBIS_BODY                                                  = 0x15E, // Ibis body model
    MODEL_ROBIN_BODY                                                 = 0x15F, // Robin body model
    MODEL_SKY_CLOUD_DOME_SKYBOX_FOR_INTRO_LEVEL_SELECT               = 0x160, // Low-poly Sky+Cloud Dome "skybox" for Intro / Level Select
    MODEL_SUNNY_SKYBOX                                               = 0x161, // "Sunny" Skybox
    MODEL_CLOUDY_SKYBOX_SUNNY_PART_2                                 = 0x162, // "Cloudy" Skybox (Sunny Part 2?)
    MODEL_DARK_CLOUDS_SKYBOX                                         = 0x163, // "Dark clouds" Skybox
    MODEL_EVENING_SKYBOX                                             = 0x164, // "Evening" Skybox
    MODEL_STARRY_NIGHT_SKYBOX                                        = 0x165, // "Starry Night" Skybox
    MODEL_OCEAN_CUT_OUT_WITH_OUTLINE_OF_CRESCENT_ISLAND              = 0x166, // Ocean "cut-out" with outline of Crescent Island(?)
    MODEL_DARK_GLOOMY_CLOUDS_SKYBOX                                  = 0x167, // "Dark gloomy clouds" skybox
    MODEL_OCEAN_CUT_OUT_WITH_OUTLINE_OF_LITTLE_STATES                = 0x168, // Ocean "cut-out" with outline of Little States
    MODEL_OCEAN_CUT_OUT_WITH_OUTLINE_OF_EVER_FROST_ISLAND            = 0x169, // Ocean "cut-out" with outline of Ever-Frost Island
    MODEL_CIRCULAR_SKY_OCEAN_SKYBOX_WITH_CLOUDS_EMPTY_OCEAN_IN_INTRO = 0x16A, // Giant circular sky+ocean skybox with high-resh skybox/clouds AND empty ocean (used in Intro)

    MODEL_WORLD                                                      = 0xFFFF // used to indicate a model that's not bound to a level?
};

typedef struct {
    u16 modelId;
    u16 unk2[1]; // unknown size, might take up everything till unk34
    u8 pad4[0x34-0x4];
    u8 unk34;
    f32 unk38;
    s32 unk3C;
} Unk80263780; // size = 0x40

typedef struct Unk80371120 {
    Unk8022B0A0 unk0[1];
    u8 pad10[0x180];
    u8 unk190[1];
    u8 pad191[0x1B];
    s32 unk1AC;
} Unk80371120; // size = 0x1B0

extern Unk80263780 D_80263780[100];
extern Mtx4F D_80265080[300];
extern u8 D_80269B80[300];
extern u16 D_80269CB0[100];
extern u16 D_80269F08;
extern u16 D_80269F0A;

void uvDobjModel(s32 objId, s32 modelId);
void uvDobjProps(s32 objId, ...);
void uvDobjPosm(s32 objId, s32 part, Mtx4F* src);
void uvDobjGetPosm(s32 objId, s32, Mtx4F* dst);
void uvDobjState(s32, s32);
void uvDobjSetState(s32 objId, s32 flags);
void uvDobjClearState(s32 objId, s32 flags);
s32 uvDobjAllocIdx(void);
void uvDobjInit(void);
void _uvDobjsDraw(UnkStruct_80204D94* arg0, s32 arg1);
void uvDobj_8021771C(UnkStruct_80204D94*);
u8 uvDobj_80217AB4(ParsedUVMD*, f32);
s32 uvDobj_80217B34(s32**);
void uvDobj_80217B4C(Unk80263780*, ParsedUVMD*, u8);
void uvDobj_80217E24(Unk80263780*, ParsedUVMD*, u8, f32, f32);
void uvDobj_802180DC(s32, Unk80371120*);

#endif // UV_DOBJ_H
