# Pilotwings 64 File System Data

The Pilotwings 64 ROM includes a custom file system that stores the game's
level data. This file enumerates the data types and their processing functions.
Functions and addresses are given in the RAM for the North American ROM.

## ROM Memory Map Overview

ROM Offset |  Length  | RAM Address           | Description
-----------|----------|-----------------------|-----------------
0x000000   | 0x000030 | -                     | ROM Header
0x000030   | 0x000FD0 | 0x1FC00000-0x1FC00FCF | IPL3 bootloader
0x001000   | 0x050E30 | 0x80200050-0x80250E7F | Kernel code/data
0x051E30   | 0x08C8F0 | 0x802CA900-0x803571EF | App code/data
0x0DE720   | 0x000E84 | -                     | TABL file system
0x0DF5B0   | 0x5395BC | -                     | Game file system

## File System Data Types

|  Tag   | Functions                    | Description
|--------|------------------------------|--------------------------------------------
| `.CTL` | func_80204438                | Sound Bank Parameters
| `.TBL` | func_80204438                | Sound Bank ADPCM Wavetable data
| `3VUE` |                              | 
| `ADAT` |                              |
| `APTS` | func_8030BDC8                | Audio switch points
| `BALS` | func_80345CE4                | 
| `BITM` | func_80219270                |
| `BNUS` | func_8030BDC8                | Bonus objects (stars)
| `BTGT` | func_80345CE4                | Ball target
| `CNTG` | func_80345CE4                |
| `COMM` | uvJanimLoad                  |
| `COMM` | uvLevelInit                  | Common
| `COMM` | func_80345CE4                |
| `DATA` | func_80341F10                |
| `ESND` | func_8030BDC8                | Environment sound
| `FALC` | func_80345CE4                | 
| `FORM` |                              |
| `FRMT` | func_80219270                |
| `GZIP` | func_80223F7C                | header for MIO0 compressed data
| `HOPD` | func_80345CE4                |
| `HPAD` | func_80345CE4                | Hover pad for rocket belt
| `IMAG` | func_80219270                |
| `INFO` | func_80345CE4                | Mission objective
| `JPTX` | func_80345CE4                | Some ASCII identifier
| `LEVL` | func_8030BDC8                |
| `LPAD` | func_8030BDC8, func_80345CE4 | Landing pads
| `LSTP` | func_80345CE4                |
| `LWIN` | func_80345CE4                |
| `NAME` | func_80341F10, func_80345CE4 | ASCII name identifier
| `OBSV` | func_80345CE4                | Unknown, parsed in code, but not in filesystem
| `PAD ` |                              |
| `PART` | uvJanimLoad                  |
| `PDAT` |                              |
| `PHDR` | func_80320A14                | Path header
| `PHTS` | func_80345CE4                | (also compares agains < PHTT 0x50485454)
| `PPOS` | func_80320A14                |
| `QUAT` | func_802D0ABC                |
| `RHDR` | func_80322BE0                |
| `RNGS` | func_80345CE4                |
| `RPKT` | func_80322BE0                |
| `SDFM` | func_80345CE4                | Unknown, parsed in code, but not in filesystem
| `SCP#` |                              |
| `SCPH` |                              |
| `SCPP` |                              |
| `SCPR` |                              |
| `SCPX` |                              |
| `SCPY` |                              |
| `SCPZ` |                              |
| `SIZE` | func_80341F10                |
| `SPTH` |                              |
| `STRG` | func_80219270                |
| `TABL` | func_802246a0                |
| `TARG` | func_80345CE4                |
| `THER` | func_80345CE4                |
| `TOYS` | func_8030BDC8                | Animated level objects (e.g. ferris wheel)
| `TPAD` | func_80345CE4                |
| `TPTS` | func_8030BDC8                | Terrain switch points
| `UPWL` |                              |
| `UPWT` |                              |
| `UVAN` | func_802246a0, func_80224a90 | Animation
| `UVBT` | func_802246a0, func_80224a90 | Blit
| `UVCT` | func_802246a0, func_80224a90 | Contour
| `UVEN` | func_802246a0, func_80224a90 | Environment
| `UVFT` | func_802246a0, func_80224a90 | Font
| `UVLT` | func_802246a0, func_80224a90 | Light?
| `UVLV` | func_802246a0, func_80224a90 | Level: container for lights, models, animation
| `UVMD` | func_802246a0, func_80224a90 | Model
| `UVRM` |                              |
| `UVRW` | func_802314d0                |
| `UVSQ` | func_802246a0, func_80224a90 | Sequence?
| `UVSX` | func_802246a0                | Sound Bank (Container for .CTL/.TBL)
| `UVSY` | func_802246a0                | System
| `UVTI` | func_802246a0, func_80224a90 | Texture image?
| `UVTP` | func_802246a0, func_80224a90 | Texture palette
| `UVTP` | uvMemLoadPal                 |
| `UVTR` | func_802246a0, func_80224a90 | Terra
| `UVTX` | func_802246a0, func_80224a90 | Texture
| `WOBJ` | func_8030BDC8                | Wind objects
| `XLAT` | func_802D0ABC                |

### LPAD / landing pad

Landing pads are the target landing pads used in the rocket belt and hang glider missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | heading
0x10   | ??   | TBD (always 0x0)
0x14   | ??   | TBD (always 0x0)
0x18   |      | **Total length**

### BNUS / bonus star

Bonus stars are the secret stars located in the birdman missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | ??   | TBD (always 0x80000000)
0x10   | ??   | TBD (always 0x0)
0x14   | ??   | TBD (always 0x0)
0x18   | ??   | 0x0 or 0x1
0x1C   | ??   | TBD
0x20?  |      | **Total length**

### BALS / balls

BALS are the objective balls to pop or push during a mission.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | ??   | TBD
0x20   | u8   | type
0x21   | ??   | TBD
0x30   | f32  | scale
0x34   | ??   | TBD
0x68   |      | **Total length**

### BTGT / ball target

BTGT is the cylindrical target for the two ball pushing rocket belt missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | u8   | TBD (always 0x01)
0x19   | ??   | TBD
0x20   |      | **Total length**

### CNTG / cannon targets

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | u8   | type
0x19   | ??   | TBD
0x20   |      | **Total length**

### HOPD / hopper destination

HOPD is the target area for the jumble hopper missions.

Offset | Type | Description
-------|------|------------
0x0    | ??   | TBD
0x4    | f32  | X position
0x8    | f32  | Y position
0xC    | f32  | Z position
0x10   | s32  | TBD (always 0x01)
0x14   | f32  | scale (either 40.0 or 30.0)
0x18   | f32  | height (always 50.0)
0x1C   | ??   | TBD
0x20   |      | **Total length**

### HPAD / hovering pad

HPAD are the hovering pads used in some rocket belt missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | ??   | TBD
0x24   | f32  | TBD
0x28   | ??   | TBD
0x40   |      | **Total length**

### LSTP / landing strip

LSTP are the landing strips used for the gyrocopter missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | upper-left X
0x4    | f32  | upper-left Y
0x8    | f32  | upper-left Z
0xC    | f32  | lower-right X
0x10   | f32  | lower-right Y
0x14   | f32  | lower-right Z
0x18   | ??   | TBD
0x28   |      | **Total length**

### OBSV

OBSV does not exist in the file system, but is parsed in the code. There are
four floats, first are a position vector, and the last is used to compare
against some distance to the fourth float in `func_802D408C`.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X
0x4    | f32  | Y
0x8    | f32  | Z
0xC    | f32  | Some radius or length
0x10   |      | **Total length**

### RNGS / rings

RNGS are the rings to fly through during missions.
After the last RNGS element, there sometimes 4 bytes more data. Total length = N * 0x84 + 4.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | ??   | TBD
0x1D   | u8   | TBD other
0x1E   | ??   | TBD
0x54   | u8   | size
0x55   | ??   | TBD
0x70   | u8   | axis
0x71   | ??   | TBD
0x72   | u8   | special
0x73   | ??   | TBD
0x84   |      | **Total length**

### TARG / targets

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | u8   | type
0x19   | u8   | TBD
0x1A   | ??   | TBD
0x20   |      | **Total length**

### THER / thermal

THER are the thermals in the hang glider missions.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | scale
0x10   | f32  | height
0x14   | s32  | TBD
0x18   | f32  | TBD
0x1C   | f32  | TBD
0x20   | f32  | TBD
0x24   | f32  | TBD
0x28   |      | **Total length**

### TPAD / takeoff pad

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | f32  | X angle
0x10   | f32  | Y angle
0x14   | f32  | Z angle
0x18   | ??   | TBD
0x28   | u8   | on ground
0x29   | ??   | TBD
0x2C   | f32  | TBD (typically 1.0)
0x30   |      | **Total length**

### TPTS / terrain switch points

Offset | Type | Description
-------|------|------------
0x34   |      | **Total length**

### WOBJ / wind objects

Wind objects are items placed in a level whose behavior interacts with the wind.
Some examples are windsocks and wind turbines.

Offset | Type | Description
-------|------|------------
0x0    | f32  | X position
0x4    | f32  | Y position
0x8    | f32  | Z position
0xC    | u8   | type (0 = windsock, 1 = wind turbine)
0xD    | -    | 3 bytes padding
0x10   |      | **Total length**

## Additional Resources:
 - [Pilotwings 64 noclip research](https://github.com/magcius/noclip.website/wiki/Pilotwings-64-Research-&-Development)
 - [noclip | PW64 parsing code](https://github.com/magcius/noclip.website/blob/main/src/Pilotwings64/Scenes.ts)
 - [TCRF | Pilotwings 64](https://tcrf.net/Pilotwings_64)
