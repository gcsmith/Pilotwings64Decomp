#ifndef PILOTWINGS64_UV_DOBJ_H
#define PILOTWINGS64_UV_DOBJ_H

#include <uv_common.h>
#include <uv_graphics.h>
#include <uv_matrix.h>
#include <uv_sched.h>

enum Models {
    MODEL_HOLIDAY_ISLAND_LOW_POLY                           = 0x000, // 0xe5138
    MODEL_WHITE_SAIL_BOAT_WITH_RED_LOGO                     = 0x001,
    MODEL_BLUE_CUBOID                                       = 0x002,
    MODEL_YELLOW_SPEED_BOAT                                 = 0x003,
    MODEL_THEMEPARK_BROWN_GREEN_BUILDING                    = 0x004, // Brown+Green Building near carnival
    MODEL_RESORT_TIKI_HUT_1                                 = 0x005, // Tiki Hut / Hay roof building near beach
    MODEL_THEMEPARK_CIRCUS_TENT                             = 0x006, // Yellow/Blue Circus Tent
    MODEL_THEMEPARK_LONG_BUILDING                           = 0x007, // Long building near ferris wheel
    MODEL_THEMEPARK_SMALL_BUILDING                          = 0x008, // Small building
    MODEL_THEMEPARK_MERRY_GO_ROUND                          = 0x009,
    MODEL_CASTLE                                            = 0x00A, // Castle on peak of map
    MODEL_THEMEPARK_ENTRY_BUILDING                          = 0x00B, // Three Entry flag building
    MODEL_THEMEPARK_FERRIS_WHEEL                            = 0x00C,
    MODEL_VILLAGE_WATER_WHEEL                               = 0x00D,
    MODEL_VILLAGE_BRIDGE_BRICK                              = 0x00E,
    MODEL_BRIDGE_BRICK_LONG_WHITE                           = 0x00F,
    MODEL_VILLAGE_LARGE_OLD_BUILDING                        = 0x010, // Old building in small town
    MODEL_VILLAGE_BUILDING_1                                = 0x011,
    MODEL_VILLAGE_BUILDING_2                                = 0x012, // And another building
    MODEL_RESORT_BUILDING_NEAR_AIRPORT                      = 0x013, // Big white building near airport
    MODEL_VILLAGE_BUILDING_WITH_CHIMNEY                     = 0x014,
    MODEL_HOLIDAY_LIGHTHOUSE                                = 0x015,
    MODEL_CASTLE_YARD                                       = 0x016,
    MODEL_AIRPORT_ATC_BUILDING                              = 0x017, // Aiport ATC building
    MODEL_PALM_TREE                                         = 0x018,
    MODEL_FIVE_PALM_TREES                                   = 0x019,
    MODEL_RED_BLUE_SAILBOAT                                 = 0x01A,
    MODEL_YELLOW_WHITE_PLANE                                = 0x01B,
    MODEL_BEACH_UMBRELLAS_AND_TOWELS                        = 0x01C,
    MODEL_BARN                                              = 0x01D, // Barn-looking building
    MODEL_SMALL_FARM_SHACK                                  = 0x01E, // Small white building/shack
    MODEL_YELLOW_N64_FLAG                                   = 0x01F,
    MODEL_RESORT_TIKI_HUT_2                                 = 0x020, // Tiki hut
    MODEL_CARPARK_STREET_LAMP                               = 0x021,
    MODEL_TREE                                              = 0x022,
    MODEL_TREE_SMALL                                        = 0x023, // Smaller tree
    MODEL_TREE_TALL                                         = 0x024, // Tall tree
    MODEL_THEMEPARK_ENTRANCE_ARCH                           = 0x025, // Entrance arch building with N64 logo flags
    MODEL_DOUBLE_WATER_FOUNTAIN                             = 0x026,
    MODEL_BIG_WHITE_RED_PLANE                               = 0x027,
    MODEL_CRESCENT_ISLAND_LOW_POLY                          = 0x028, // 0xe5138 Also full poly in game? LOD?
    MODEL_RED_WHITE_BLUE_YACHT                              = 0x029, // Red/White/Blue yacht/boat
    MODEL_WHITE_YELLOW_SAILBOAT                             = 0x02A,
    MODEL_ROCK_ARCH                                         = 0x02B,
    MODEL_ROCK_POST                                         = 0x02C,
    MODEL_ROCK_PILLAR_TALL                                  = 0x02D,
    MODEL_ROCK_SMALL                                        = 0x02E,
    MODEL_ROCK_BIG                                          = 0x02F,
    MODEL_ROCK_SMALL_2                                      = 0x030,
    MODEL_ROCK_PILLAR_MEDIUM                                = 0x031,
    MODEL_FARMHOUSE_4X_OVERGROWN                            = 0x032, // Group of 4x farm buildings, one with overgrowing walls
    MODEL_FARMHOUSE_2X_OVERGROWN_AND_SILO                   = 0x033, // Group of 2x farm buildings, one with overgrowing walls + a silo
    MODEL_SILO_3                                            = 0x034, // Another Silo...
    MODEL_FARM_STORAGE_1                                    = 0x035,
    MODEL_CR_RESORT_BUILDING_1                              = 0x036, // 1 side painted with psychadelic circle image
    MODEL_CR_RESORT_BUILDING_2                              = 0x037, // Also contains multi-tier pool
    MODEL_CR_RESORT_BUILDING_3                              = 0x038, // U-Shaped building with pool in the middle
    MODEL_CR_RESORT_BUILDING_4                              = 0x039, // 1 side painted with sky & wind-surfer image
    MODEL_CR_RESORT_BUILDING_5                              = 0x03A, // 3x buildings surrounding a small pool with steps down to the beach
    MODEL_CR_RESORT_BUILDING_6                              = 0x03B, // Tiered building with pool at the base
    MODEL_CR_LIGHTHOUSE                                     = 0x03C, // Small Lighthouse (Crescent Island)
    MODEL_CR_WOODEN_HUT_1                                   = 0x03D, // Small wooden villiage rectangular hut (Crescent Island)
    MODEL_CR_WOODEN_HUT_2                                   = 0x03E, // Small wooden flat-roofed villiage hut (Crescent Island)
    MODEL_03F                                               = 0x03F, // Bridge?? FLAT with Ramp one side? Not sure if this is used
    MODEL_WIND_SOCK_YELLOW_BLUE                             = 0x040,
    MODEL_PLANTER_BOX                                       = 0x041,
    MODEL_HANGGLIDER_YGW                                    = 0x042, // Yellow-Green-White Hang-glider prop
    MODEL_HANGGLIDER_BLUE                                   = 0x043, // Blue Hang-glider prop wiht N64 logo
    MODEL_TRUCK_BLUE                                        = 0x044, // Blue Truck (Ute)
    MODEL_ROCKFACE_SMALL                                    = 0x045, // Small One-sided rockface? Not sure where this is used
    MODEL_ROCKFACE_LARGE                                    = 0x046, // Large One-sided rockface? Not sure where this is used
    MODEL_CR_AIRPORT_HANGER                                 = 0x047, // Airport hanger (Crescent Island)
    MODEL_CR_SEASIDE_TOWN_CENTRE                            = 0x048, // Stone building, lots of steps
    MODEL_CR_SEASIDE_TOWN_BUILDING_1                        = 0x049, // Brown roofed villa, two tiered, small tower on one side
    MODEL_CR_SEASIDE_TOWN_BUILDING_2                        = 0x04A, // Villa? Orange roof + sections of brown roof, some awnings
    MODEL_CR_SEASIDE_TOWN_FOUNTAIN                          = 0x04B, // Fountain with stone spire ontop
    MODEL_WOODEN_CHURCH                                     = 0x04C, // Wooden Church building
    MODEL_CAVE_PILLARS_LARGE                                = 0x04D, // cave pillars (larger centre pillar)
    MODEL_CAVE_PILLARS                                      = 0x04E, // Cave pillars
    MODEL_CAVE_PILLAR_SINGLE                                = 0x04F, // Cave pillar
    MODEL_CAVE_LIGHT_FITTING                                = 0x050, // Cave light fitting
    MODEL_LITTLE_STATES_LOW_POLY                            = 0x051, // 0x1114fc
    MODEL_BIG_CRUISE_SHIP                                   = 0x052,
    MODEL_WIND_TURBINE                                      = 0x053,
    MODEL_PUMP_JACK                                         = 0x054,
    MODEL_STONE_WARIO_HEAD                                  = 0x055,
    MODEL_SPACE_SHUTTLE                                     = 0x056,
    MODEL_BIG_RED_SQUARE                                    = 0x057, // not sure if this is used?
    MODEL_NESSIES_HEAD                                      = 0x058,
    MODEL_BOAT_BLUE_WHITE_N64_FLAG                          = 0x059, // Blue and white boat with N64 logo flag
    MODEL_05A                                               = 0x05A, // Building with 4 columns out front (smithsonian museum maybe?)
    MODEL_BOAT_PADDLE_STEAMER                               = 0x05B,
    MODEL_TREE_LS_1                                         = 0x05C, // Green leaves, brown trunk
    MODEL_TREE_LS_2                                         = 0x05D, // Green leaves, brown trunk (different shape)
    MODEL_TREE_LS_3                                         = 0x05E, // Yellow leaves, brown trunk
    MODEL_TREE_LS_4                                         = 0x05F, // Bright green leaves, brown trunk
    MODEL_TREE_LS_5                                         = 0x060, // Yellow leaves, brown trunk - appears identical to 0x05E
    MODEL_061                                               = 0x061, // Large office building with a diagonal cutout
    MODEL_062                                               = 0x062, // Large office building 
    MODEL_063                                               = 0x063, // Another large office building
    MODEL_NYC_EMPIRE_STATE_BUILDING                         = 0x064,
    MODEL_NYC_BUILDING_UN_HEADQUARTERS                      = 0x065,
    MODEL_NYC_STATUE_OF_LIBERTY                             = 0x066, // 0x12c238
    MODEL_CHICAGO_4X_OFFICE_TOWERS_1                        = 0x067, // Office buildings 4x inc. twin towers?
    MODEL_CHICAGO_4X_OFFICE_TOWERS_2                        = 0x068, // Office buildings 4x Two tall longer buildings, one short, one medium
    MODEL_CHICAGO_4X_OFFICE_TOWERS_3                        = 0x069, // Office buidings one long, one diamond shaped, two taller
    MODEL_CHICAGO_5X_OFFICE_TOWERS_1                        = 0x06A, // 5x office buildings
    MODEL_NYC_4X_OFFICE_TOWERS_1                            = 0x06B, // 4x office buildings, 2x include grassed areas
    MODEL_NYC_3X_OFFICE_TOWERS_1                            = 0x06C, // More office buildings
    MODEL_NYC_4X_OFFICE_TOWERS_2                            = 0x06D, // more office buildings
    MODEL_NYC_4X_OFFICE_TOWERS_3                            = 0x06E, // Group of office buildings
    MODEL_NYC_SINGLE_OFFICE_TOWER_1                         = 0x06F, // Single office building
    MODEL_NYC_WORLD_TRADE_CENTER                            = 0x070, // Two extremely tall office buildings
    MODEL_SILO_1                                            = 0x071, // Small flat-top silo
    MODEL_SILO_2                                            = 0x072, // Wider flat-top silo
    MODEL_BARN_LONG_1                                       = 0x073, // Long Barn (Chicken Barn?) (complex roof)
    MODEL_WATER_TOWER                                       = 0x074, // Red&White Water tower ontop of scaffolding
    MODEL_FL_WIDE_BUILDING                                  = 0x075, // Large modern building, 4x pointed roof sections, mostly flat
    MODEL_AIRPORT_HANGER_DOUBLE                             = 0x076, // Double Airplane Hanger-looking building
    MODEL_KSC_LARGE_AIRPLANE_HANGAR                         = 0x077, // 0x1004 Possibly used elsewhere
    MODEL_KSC_CONTROL_TOWERS                                = 0x078, // Airport control-tower (or maybe Prison towers??)
    MODEL_KSC_GUARD_TOWER                                   = 0x079, // Security Entrance Gate, also used at Nuclear Plant
    MODEL_BARN_LONG_2                                       = 0x07A, // Another Long barn, simple roof
    MODEL_BARN_MEDIUM                                       = 0x07B, // Slightly smaller long barn, simple roof
    MODEL_STL_GATEWAY_ARCH                                  = 0x07C, // Gateway Archway
    MODEL_FARMHOUSE_3X_STONE                                = 0x07D, // Group of 3x stone farmhouses, tiled slat roof
    MODEL_FARMHOUSE_4X_STONE_AND_SILO                       = 0x07E, // Group of 4x stone farmhouse & buildings & tall silo
    MODEL_RED_BARN_AND_SILO                                 = 0x07F, // Red Barn with silo, ramp going to upstairs
    MODEL_WASHINGTON_LINCOLN_MEMORIAL                       = 0x080, // State building of some kind (lots of columns)
    MODEL_WASHINGTON_WHITEHOUSE                             = 0x081,
    MODEL_WASHINGTON_MONUMENT                               = 0x082,
    MODEL_SPACE_SHUTTLE_LAUNCH_TOWER                        = 0x083, // Space shuttle launch tower
    MODEL_GAS_STATION                                       = 0x084, // ?
    MODEL_WASHINGTON_CAPITOL_BUILDING                       = 0x085, // 0x13ab4c
    MODEL_WASHINGTON_FEDERAL_TRIANGLE                       = 0x086,
    MODEL_WASHINGTON_RECTANGULAR_BUILDING                   = 0x087,
    MODEL_NUCLEAR_POWER_PLANT                               = 0x088,
    MODEL_089                                               = 0x089, //Bridge support?
    MODEL_LA_TOWER_1                                        = 0x08A, //TODO: 08A-091 are buildings, possible generic, maybe some iconic?
    MODEL_LA_2X_TOWERS                                      = 0x08B,
    MODEL_08C                                               = 0x08C,
    MODEL_08D                                               = 0x08D,
    MODEL_08E                                               = 0x08E,
    MODEL_08F                                               = 0x08F, 
    MODEL_BUILDING_PINK_1                                   = 0x090, // Pink-ish office building
    MODEL_BUILDING_PINK_2                                   = 0x091, // Pink-ish U-Shaped building, multiple storey with ground-level walkway
    MODEL_SEATTLE_SPACE_NEEDLE                              = 0x092, // Space needle
    MODEL_OBSERVATORY                                       = 0x093, // Observatory with dome roof and telescope sticking out of the top
    MODEL_TRUCK_DELIVERY_BLUE                               = 0x094, // Blue Truck
    MODEL_LS_BRIDGE_SUPPORT_SMALL                           = 0x095, // Small Bridge pylon/support
    MODEL_LS_BRIDGE_SUPPORT_TALL                            = 0x096, // Taller Bridge pylon/support
    MODEL_ROW_OF_5X_TREES                                   = 0x097, // Row of 5x Trees
    MODEL_MOBILE_PHONE_TOWER                                = 0x098, // Radio/Mobile tower
    MODEL_STONE_MARIO_HEAD                                  = 0x099,
    MODEL_OFFSHORE_OIL_RIG                                  = 0x09A, // Offshore Oil Rig
    MODEL_09B                                               = 0x09B,
    MODEL_09C                                               = 0x09C,
    MODEL_09D                                               = 0x09D,
    MODEL_09E                                               = 0x09E,
    MODEL_09F                                               = 0x09F,
    MODEL_0A0                                               = 0x0A0,
    MODEL_0A1                                               = 0x0A1,
    MODEL_0A2                                               = 0x0A2,
    MODEL_0A3                                               = 0x0A3,
    MODEL_0A4                                               = 0x0A4,
    MODEL_EVER_FROST_ISLAND_LOW_POLY                        = 0x0A5, // 0x149084
    MODEL_OIL_SPRAY                                         = 0x0A6, // Oil fountain spray
    MODEL_SKI_LIFT_CHAIR                                    = 0x0A7,
    MODEL_ICEBERG_1                                         = 0x0A8, // Iceberg
    MODEL_ICEBERG_2                                         = 0x0A9, // Another iceberg (with floating ripples)
    MODEL_ICEBERG_FRACTURED                                 = 0x0AA, // Four icebergs (fragmented pieces)
    MODEL_TREE_SNOW_BILLBOARD                               = 0x0AB, // Billboarded Tree (kinda like a christmas tree)
    MODEL_0AC                                               = 0x0AC, // White roofed long building
    MODEL_STONE_CHURCH                                      = 0x0AD, // Large stone church? Dark roof, snow ontop, 3 towers
    MODEL_0AE                                               = 0x0AE, // Round tower with overhanging roof, meling snow around the lip
    MODEL_0AF                                               = 0x0AF, // Small house with snow on roof, red brick chimney
    MODEL_0B0                                               = 0x0B0, // Long building with tall steep roof that touches the ground on either side
    MODEL_0B1                                               = 0x0B1, // Long building (lodge?) with two red chimnets and lots of doors & windows
    MODEL_0B2                                               = 0x0B2, // Tall lodge, yellow walls, two storey with balcony
    MODEL_0B3                                               = 0x0B3, // Very large lodge, 5 pointed roof sections, 3 chimneys, multiple balconies
    MODEL_0B4                                               = 0x0B4, // Stone walled compound, small garage & entry building?
    MODEL_AIRPORT_ATC_BUILDING_SNOWY                        = 0x0B5, // Air traffic control tower (Snowy roof)
    MODEL_AIRPORT_HANGER_SNOWY                              = 0x0B6, // Airplane Hanger (snowy roof)
    MODEL_0B7                                               = 0x0B7, // Long Grey Building
    MODEL_0B8                                               = 0x0B8, // Red/White metal tower with lighthouse light on top, concrete/stone base
    MODEL_0B9                                               = 0x0B9, // Concrete Dome building with american flag on top
    MODEL_0BA                                               = 0x0BA, // Smaller tower with railing (Billboard)
    MODEL_0BB                                               = 0x0BB, // Large Tower with mesh on top (Billboard)
    MODEL_0BC                                               = 0x0BC, // Large chimney (refinery?)
    MODEL_0BD                                               = 0x0BD, // Large shipping container crane?
    MODEL_REFINERY_TANK_SPHERE                              = 0x0BE, // Sphere storage tank with railing and staircase to the top
    MODEL_REFINERY_BUILDING_WITH_PIPES                      = 0x0BF, // 0x16182c | Refinery building_xx?
    MODEL_PIPELINE_1                                        = 0x0C0, // Large ground-based pipeline
    MODEL_SKI_LIFT_START                                    = 0x0C1, // Ski-lift Start point building?
    MODEL_SKI_LIFT_END                                      = 0x0C2, // Ski lift end-point building
    MODEL_SKI_LIFT_POLE                                     = 0x0C3, // Ski lift pole
    MODEL_IGLOO                                             = 0x0C4, // Igloo with black chimney
    MODEL_0C5                                               = 0x0C5, // Small building, yellow walls, snowy roof
    MODEL_WHITE_FLAG_N64LOGO                                = 0x0C6, // white flag with N64 Logo
    MODEL_MAP_THERMAL_CYLINDER                              = 0x0C7, // Map marker thermal cylinder
    MODEL_MAP_WIND_INDICATOR_ARROW                          = 0x0C8, // Map marker (wind direction indicator)
    MODEL_MAP_TARGET_INDICATOR_ARROW                        = 0x0C9, // Map marker (Target indicator)
    MODEL_MAP_RING_TARGET_YELLOW_CUBE                       = 0x0CA, // Map marker (ring target)
    MODEL_MAP_LANDING_PAD_RED_CUBE                          = 0x0CB, // Map marker (landing pad)
    MODEL_MAP_RING_TARGET_BLUE_CUBE                         = 0x0CC, // Map marker (blue ring target)
    MODEL_PILOTWINGS_3D_LOGO                                = 0x0CD, // 0x166184
    MODEL_MAP_STARTING_DIRECTION_ARROW                      = 0x0CE, // Map marker (Starting location/direction)
    MODEL_CANNON_ON_TALL_RED_PEDESTAL                       = 0x0CF,
    MODEL_CANNONB_TARGET_1                                  = 0x0D0, // Target - normal sized, way smaller than 0x106-8 - Map marker?
    MODEL_RED_WHITE_GOAL                                    = 0x0D1, // Red Goal (Ball or Jumble Hopper (less transparent))
    MODEL_GREEN_BLUE_GOAL_0                                 = 0x0D2, // Green Goal (Ball or Jumble Hopper?)
    MODEL_MECCA_HAWK                                        = 0x0D3,
    MODEL_LANDING_PAD_NOTARGET                              = 0x0D4, // Has no target, just square outline
    MODEL_WIND_WAVE_1                                       = 0x0D5, // Wind effect (large wave with scrolling texture
    MODEL_WIND_WAVE_2                                       = 0x0D6, // Smaller wind effect small wave with fast scrolling texture
    MODEL_GREY_WHALE                                        = 0x0D7,
    MODEL_BROWN_BOX                                         = 0x0D8, // Unknown brown rectangular box with missing bottom side
    MODEL_RING_YELLOW_1                                     = 0x0D9, // Rings appear to all have timer modes, presumably hidden when not a timed ring? (can't find any non-timed rings in the list)
    MODEL_RING_RED_1                                        = 0x0DA,
    MODEL_RING_BLUE_1                                       = 0x0DB,
    MODEL_RING_WHITE_1                                      = 0x0DC,
    MODEL_RING_YELLOW_2                                     = 0x0DD,
    MODEL_RING_RED_2                                        = 0x0DE,
    MODEL_RING_BLUE_2                                       = 0x0DF,
    MODEL_RING_WHITE_2                                      = 0x0E0,
    MODEL_RING_YELLOW_3                                     = 0x0E1,
    MODEL_RING_RED_3                                        = 0x0E2,
    MODEL_RING_BLUE_3                                       = 0x0E3,
    MODEL_RING_WHITE_3                                      = 0x0E4,
    MODEL_RING_YELLOW_4                                     = 0x0E5,
    MODEL_RING_RED_4                                        = 0x0E6,
    MODEL_RING_BLUE_4                                       = 0x0E7,
    MODEL_RING_WHITE_4                                      = 0x0E8,
    MODEL_RING_YELLOW_5                                     = 0x0E9,
    MODEL_RING_RED_5                                        = 0x0EA,
    MODEL_RING_BLUE_5                                       = 0x0EB,
    MODEL_RING_WHITE_5                                      = 0x0EC,
    MODEL_RING_LOCKED_YELLOW                                = 0x0ED,
    MODEL_RING_LOCKED_RED                                   = 0x0EE,
    MODEL_RING_LOCKED_BLUE                                  = 0x0EF,
    MODEL_RING_LOCKED_GREY                                  = 0x0F0,
    MODEL_RING_WITH_GOAL_TEXT                               = 0x0F1,
    MODEL_BONUS_STAR                                        = 0x0F2,
    MODEL_GREEN_BLUE_GOAL_1                                 = 0x0F3, // Green/blue goal used in Rocket Belt (more translucent)
    MODEL_BALL_ORANGE                                       = 0x0F4,
    MODEL_BALL_GREEN                                        = 0x0F5,
    MODEL_BALL_BLUE                                         = 0x0F6,
    MODEL_MISSILE_TARGET_BILLBOARD                          = 0x0F7,
    MODEL_MISSILE_TARGET_DISC                               = 0x0F8,
    MODEL_MISSILE_TARGET_BALL                               = 0x0F9,
    MODEL_RB_HOVERPAD_LOCKED                                = 0x0FA, // HPAD
    MODEL_RB_HOVERPAD_STANDARD                              = 0x0FB, // HPAD
    MODEL_RB_HOVERPAD_LARGE                                 = 0x0FC, // HPAD
    MODEL_GIANT_TRANSPARENT_MECCA_HAWK                      = 0x0FD,
    MODEL_GIANT_RED_THING                                   = 0x0FE, // ??
    MODEL_BIG_ROCK_BOULDER                                  = 0x0FF,
    MODEL_ICEBERG_GIANT                                     = 0x100, // ??
    MODEL_HG_THERMAL_CYLINDER                               = 0x101, //Hang Glider Thermal Cylinder shape
    MODEL_LANDING_PAD_1                                     = 0x102, // LPAD
    MODEL_LANDING_PAD_2                                     = 0x103, // LPAD
    MODEL_LANDING_PAD_3                                     = 0x104, // LPAD
    MODEL_CANNON_ON_PILLAR                                  = 0x105,
    MODEL_CANNONB_TARGET_2                                  = 0x106, // CNTG - Huge?
    MODEL_CANNONB_TARGET_3                                  = 0x107, // CNTG - Huge?
    MODEL_CANNONB_TARGET_4                                  = 0x108, // CNTG - Huge?
    MODEL_JH_DESTINATION                                    = 0x109, // Jumble Hopper Goal Target? (more transparent than _0D1)
    MODEL_HG_LARK_LOWPOLY                                   = 0x10A, // Low Poly (LOD?Intro?)
    MODEL_HG_GOOSE_LOWPOLY                                  = 0x10B, // Low Poly (LOD?Intro?)
    MODEL_HG_HAWK_LOWPOLY                                   = 0x10C,
    MODEL_HG_KIWI_LOWPOLY                                   = 0x10D,
    MODEL_HG_IBIS_LOWPOLY                                   = 0x10E,
    MODEL_HG_ROBIN_LOWPOLY                                  = 0x10F,
    MODEL_HG_LARK                                           = 0x110, //Lark Hang glider model
    MODEL_HG_SHADOW                                         = 0x111, //Hang glider shadow model
    MODEL_HG_SHADOW_COLUMN                                  = 0x112, // Hang glider shadow column model
    MODEL_HG_LARK_CRASHED                                   = 0x113, //Lark Hang glider model (crashed)
    MODEL_HG_GOOSE                                          = 0x114, //Goose Hang glider model
    MODEL_HG_GOOSE_CRASHED                                  = 0x115, //Goose Hang glider model (crashed)
    MODEL_HG_HAWK                                           = 0x116, //Hawk Hang glider model
    MODEL_HG_HAWK_CRASHED                                   = 0x117, //Hawk Hang glider model (crashed)
    MODEL_HG_KIWI                                           = 0x118, //Kiwi Hang glider model
    MODEL_HG_KIWI_CRASHED                                   = 0x119, //Kiwi Hang glider model (crashed)
    MODEL_HG_IBIS                                           = 0x11A, //Ibis Hang glider model
    MODEL_HG_IBIS_CRASHED                                   = 0x11B, //Ibis Hang glider model (crashed)
    MODEL_HG_ROBIN                                          = 0x11C, //Robin Hang glider model
    MODEL_HG_ROBIN_CRASHED                                  = 0x11D, //Robin Hang glider model (crashed)
    MODEL_RB_LARK                                           = 0x11E, // Lark Rocket Pack Model
    MODEL_RB_SHADOW                                         = 0x11F, // Round Shadow?
    MODEL_RB_SHADOW_COLUMN                                  = 0x120, // Shadow Column
    MODEL_MULTI_COLORED_CUBE                                = 0x121, // not sure if this is used?
    MODEL_RB_GOOSE                                          = 0x122, //Goose Rocket Pack Model
    MODEL_RB_HAWK                                           = 0x123, //Hawk Rocket Pack Model
    MODEL_RB_KIWI                                           = 0x124, // Kiwi Rocket Pack Model
    MODEL_RB_IBIS                                           = 0x125, // Ibis Rocket Pack Model
    MODEL_RB_ROBIN                                          = 0x126, // Robin Rocket Pack Model
    MODEL_GYRO_LARK                                         = 0x127, // Lark Gyro Model
    MODEL_GYRO_SHADOW                                       = 0x128, //Gyro Shadow Model
    MODEL_GYRO_SHADOW_COLUMN                                = 0x129, //Gyro Shadow Column Model
    MODEL_GYRO_LARK_CRASHED                                 = 0x12A, //Lark Gyro Model (crashed)
    MODEL_GYRO_GOOSE                                        = 0x12B, // Goose Gyro Model
    MODEL_GYRO_GOOSE_CRASHED                                = 0x12C, //Goose Gyro Model (crashed)
    MODEL_GYRO_HAWK                                         = 0x12D, // Hawk Gyro Model
    MODEL_GYRO_HAWK_CRASHED                                 = 0x12E, //Hawk Gyro Model (crashed)
    MODEL_GYRO_KIWI                                         = 0x12F, // Kiwi Gyro Model
    MODEL_GYRO_KIWI_CRASHED                                 = 0x130, //Kiwi Gyro Model (crashed)
    MODEL_GYRO_IBIS                                         = 0x131, // Ibis Gyro Model
    MODEL_GYRO_IBIS_CRASHED                                 = 0x132, //Ibis Gyro Model (crashed)
    MODEL_GYRO_ROBIN                                        = 0x133, // Robin Gyro Model
    MODEL_GYRO_ROBIN_CRASHED                                = 0x134, //Robin Gyro Model (crashed)
    MODEL_CANNONB_LARK_LAUNCHED                             = 0x135,
    MODEL_CANNONB_GOOSE_LAUNCHED                            = 0x136,
    MODEL_CANNONB_HAWK_LAUNCHED                             = 0x137,
    MODEL_CANNONB_KIWI_LAUNCHED                             = 0x138,
    MODEL_CANNONB_IBIS_LAUNCHED                             = 0x139,
    MODEL_CANNONB_ROBIN_LAUNCHED                            = 0x13A,
    MODEL_BIRDMAN_LARK                                      = 0x13B,
    MODEL_BIRDMAN_SHADOW                                    = 0x13C,
    MODEL_BIRDMAN_SHADOW_COLUMN                             = 0x13D,
    MODEL_BIRDMAN_GOOSE                                     = 0x13E,
    MODEL_BIRDMAN_HAWK                                      = 0x13F,
    MODEL_BIRDMAN_KIWI                                      = 0x140,
    MODEL_BIRDMAN_IBIS                                      = 0x141,
    MODEL_BIRDMAN_ROBIN                                     = 0x142,
    MODEL_SKYDIVING_LARK                                    = 0x143,
    MODEL_PARACHUTE_LARK                                    = 0x144,
    MODEL_SKYDIVING_KIWI                                    = 0x145, // Skydiving Kiwi model
    MODEL_SKYDIVING_IBIS                                    = 0x146, // Skydiving Ibis model
    MODEL_SKYDIVING_ROBIN                                   = 0x147,
    MODEL_SKYDIVING_SHADOW                                  = 0x148, // Skydiving "shadow" of player
    MODEL_SKYDIVING_GOOSE                                   = 0x149,
    MODEL_PARACHUTE_GOOSE                                   = 0x14A,
    MODEL_SKYDIVING_HAWK                                    = 0x14B, // Skydiving Hawk model
    MODEL_PARACHUTE_HAWK                                    = 0x14C,
    MODEL_PARACHUTE_KIWI                                    = 0x14D, // Parachute pink girl model
    MODEL_PARACHUTE_IBIS                                    = 0x14E, // Parachute Isis model
    MODEL_PARACHUTE_ROBIN                                   = 0x14F, // Paracute Robin model
    MODEL_JUMBLEH_LARK                                      = 0x150, // Jumble Hopper Lark
    MODEL_JUMBLEH_SHADOW                                    = 0x151, // Round shadow
    MODEL_JUMBLEH_GOOSE                                     = 0x152,
    MODEL_JUMBLEH_HAWK                                      = 0x153,
    MODEL_JUMBLEH_KIWI                                      = 0x154, // Jumble Hopper Kiwi
    MODEL_JUMBLEH_IBIS                                      = 0x155, // Jumble Hopper Ibis
    MODEL_JUMBLEH_ROBIN                                     = 0x156, // Jumble Hopper Robin
    MODEL_PILOTWINGS_LOGO_FEATHER                           = 0x157, // Pilotwings Swoosh/feather thing
    MODEL_PILOTWINGS_LOGO_SIX                               = 0x158, // 3D "6" in intro PW64 logo
    MODEL_PILOTWINGS_LOGO_FOUR                              = 0x159, // 3D "4" in intro PW64 logo
    MODEL_PILOT_LARK                                        = 0x15A, // Character Select model
    MODEL_PILOT_GOOSE                                       = 0x15B, // Character Select model
    MODEL_PILOT_HAWK                                        = 0x15C, // Character Select model
    MODEL_PILOT_KIWI                                        = 0x15D, // Character Select model
    MODEL_PILOT_IBIS                                        = 0x15E, // Character Select model
    MODEL_PILOT_ROBIN                                       = 0x15F, // Character Select model
    MODEL_SKYBOX_INTRO_LOW_POLY_SKY_CLOUD                   = 0x160, // Low-poly Sky+Cloud Dome "skybox" for Intro / Level Select
    MODEL_SKYBOX_SUNNY                                      = 0x161,
    MODEL_SKYBOX_SUNNY_2                                    = 0x162, // Cloudy Sunny Skybox Part 2?
    MODEL_SKYBOX_DARK_CLOUDS                                = 0x163,
    MODEL_SKYBOX_EVENING                                    = 0x164,
    MODEL_SKYBOX_STARRY_NIGHT                               = 0x165,
    MODEL_OCEAN_CUTOUT_CRESCENT_ISLAND                      = 0x166, // Ocean "cut-out" with outline of Crescent Island
    MODEL_SKYBOX_DARK_GLOOMY_CLOUDS                         = 0x167,
    MODEL_OCEAN_CUTOUT_LITTLE_STATES                        = 0x168, // Ocean "cut-out" with outline of Little States
    MODEL_OCEAN_CUTOUT_EVER_FROST_ISLAND                    = 0x169, // Ocean "cut-out" with outline of Ever-Frost Island
    MODEL_SKYBOX_INTRO_GIANT_CIRCULAR_SKY_OCEAN             = 0x16A, // Giant circular sky+ocean skybox with high-resh skybox/clouds AND empty ocean (used in Intro)

    MODEL_WORLD                                             = 0xFFFF // used to indicate a model that's not bound to a level? (Possibly used to make a model dissappear without freeing it?)
};

#define MODEL_IS_TREE(id) (((id) == MODEL_PALM_TREE) || \
                           ((id) == MODEL_TREE_LS_1) || \
                           ((id) == MODEL_TREE_LS_2) || \
                           ((id) == MODEL_TREE_LS_3) || \
                           ((id) == MODEL_TREE_LS_4) || \
                           ((id) == MODEL_TREE_LS_5) || \
                           ((id) == MODEL_TREE) || \
                           ((id) == MODEL_TREE_SMALL) || \
                           ((id) == MODEL_TREE_TALL))

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
    u8 unk190[25];
    u8 pad1A9[0x1AC - 0x1A9];
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
s32  uvDobjAllocIdx(void);
void uvDobjInit(void);
void _uvDobjsDraw(UnkStruct_80204D94* arg0, s32 arg1);
void uvDobj_8021771C(UnkStruct_80204D94*);
u8   uvDobjGetLODIndex(ParsedUVMD* uvmd, f32 dist);
s32  uvDobj_80217B34(s32**);
void uvDobj_80217B4C(Unk80263780*, ParsedUVMD*, u8);
void uvDobj_80217E24(Unk80263780*, ParsedUVMD*, u8, f32, f32);
void uvDobj_802180DC(s32, Unk80371120*);

#endif // PILOTWINGS64_UV_DOBJ_H

