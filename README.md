# Pilotwings64Decomp

An early, work-in-progress **matching decompilation** of Pilotwings 64. 

The purpose of this project is to produce a reconstruction of the high-level source code through reverse engineering.

> [!IMPORTANT]
> This repository does not contain any game assets, assembly code, or other copyrighted materials.
> You must provide your own legally-obtained copy of the game in order to extract the assets necessary to build this repository.

## Development

### Git
This repository uses Git submodules. Make sure to either clone the repository with the `--recurse-submodules` flag or to run `git submodule update --init --recursive` after the initial clone.

When pulling updates, you can update all submodules with `git submodule update --recursive`.

> Note: If you intend on developing inside of the Windows Subsystem for Linux (WSL), consider placing the repository on the WSL Linux partition. Builds are considerably slower when done on the Windows partition through WSL.

### Prerequisites

#### System packages

##### Linux / Windows Subsystem for Linux
The following packages should be all you need to compile this project:
- binutils-mips-linux-gnu
- gcc
- git
- python3
- python3-pip

#### Python3 packages / venv

```bash
python3 -m venv .venv
source ./.venv/bin/activate
python3 -m pip install -r requirements.txt
```

### Setup
1. Place an unmodified Pilot Wings 64 ROM into the root of the repository as `baserom.us.z64` (SHA1SUM: `ec771aedf54ee1b214c25404fb4ec51cfd43191a`).
2. Set up dependencies
    - `make dependencies`
3. Init project
    - `make init`

### Rebuilding
1. If any symbols or the splat config were changed, re-extract the ROM and rebuild the linker script:
    - `make extract`
2. Rebuild the ROM:
    - `make -j`