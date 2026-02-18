[![Build](https://github.com/gcsmith/Pilotwings64Decomp/actions/workflows/ci.yml/badge.svg)](https://github.com/gcsmith/Pilotwings64Decomp/actions/workflows/ci.yml)
[![Code](https://decomp.dev/gcsmith/Pilotwings64Decomp/us.svg?mode=shield&measure=code&label=Code%20Bytes)](https://decomp.dev/gcsmith/Pilotwings64Decomp)
[![Data](https://decomp.dev/gcsmith/Pilotwings64Decomp/us.svg?mode=shield&measure=data&label=Data%20Bytes)](https://decomp.dev/gcsmith/Pilotwings64Decomp)
[![Functions](https://decomp.dev/gcsmith/Pilotwings64Decomp/us.svg?mode=shield&measure=matched_functions&label=Functions)](https://decomp.dev/gcsmith/Pilotwings64Decomp)
[![Discord](https://img.shields.io/discord/1465499203831730191?color=%237289DA&logo=discord&logoColor=%23FFFFFF)](https://discord.gg/bkrYXSjrKE)

# Pilotwings64Decomp

This repo contains a work-in-progress **matching decompilation** of Pilotwings 64, currently supporting the following releases: North America (U).

The purpose of this project is to produce a reconstruction of the high-level source code through reverse engineering.

> [!IMPORTANT]
> This repository does not contain any game assets, assembly code, or other copyrighted materials.
> You must provide your own legally-obtained copy of the game in order to extract the assets necessary to build this repository.

## Quick Start
See the [Development](#development) section below for full details on different systems. For Debian/Ubuntu, the following steps can be taken to quickly get going:
```bash
$ sudo apt install binutils-mips-linux-gnu gcc git make python3 python3-pip
$ git clone --recurse-submodules https://github.com/gcsmith/Pilotwings64Decomp.git
$ cd Pilotwings64Decomp
$ python3 -m venv .venv
$ source ./.venv/bin/activate
$ python3 -m pip install -r requirements.txt
$ cp <path-to-ROM> ./baserom.us.z64
$ make dependencies
$ make init
```

## Development

### Git
This repository uses Git submodules. Make sure to either clone the repository with the `--recurse-submodules` flag or to run `git submodule update --init --recursive` after the initial clone.

When pulling updates, you can update all submodules with `git submodule update --recursive`.

> Note: If you intend on developing inside of the Windows Subsystem for Linux (WSL), consider placing the repository on the WSL Linux partition. Builds are considerably slower when done on the Windows partition through WSL.

### Prerequisites

#### System packages

##### Debian/Ubuntu Linux (also under WSL)
The following packages should be all you need to compile this project:
- binutils-mips-linux-gnu (or similar, e.g. mips64-elf-binutils)
- gcc
- git
- make
- python3
- python3-pip

#### macOS
Under macOS, ensure the Xcode command line tools are installed and the following homebrew packages:
- make
- tehzz/n64-dev/mips64-elf-binutils

#### Python3 packages / venv
This project has python3 dependencies defined in the repo's requirements.txt. These can be managed through a python virtual environment and pip or through uv.

Example setup with python3 venv/pip
```bash
$ python3 -m venv .venv
$ source ./.venv/bin/activate
$ python3 -m pip install -r requirements.txt
```

Example setup with uv:
```bash
$ uv venv
$ uv pip install -r requirements.txt
```

### Setup
1. Place an unmodified Pilotwings 64 ROM into the root of the repository as `baserom.us.z64` (SHA1SUM: `ec771aedf54ee1b214c25404fb4ec51cfd43191a`).
2. Set up dependencies
    - `make dependencies`
3. Init project
    - `make init`

### Rebuilding
1. If any symbols or the splat config were changed, re-extract the ROM and rebuild the linker script:
    - `make extract`
2. Rebuild the ROM:
    - `make -j`

## Contributing
Pull requests are welcome. You can help with decompilation, renaming, documentation, and tooling. PRs are subject to code formatting checks, so there is an additional dependency of `clang-format` (provided by clang). Run `make format` to format your changes prior to starting the PR.
