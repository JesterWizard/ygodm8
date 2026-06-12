# ygodm8

`ygodm8` is a GBA decompilation-style codebase that builds with the legacy `agbcc` toolchain.

It is intended for inspecting, modifying, and rebuilding the game from a C and assembly decompiled source. That makes it useful for reverse engineering, bug fixes, feature work, and ROM hacking.

## Toolchain Overview

This project uses:

- `agbcc` for the legacy matching C build
- `arm-none-eabi` tools for assembling and linking
- `gbagfx` for graphics conversion
- `preproc` for source and script preprocessing

The local helper tools are built from this repository during `make`. `agbcc` must be installed separately into `tools/agbcc`.

## Requirements

You can build on **Linux**, **WSL**, or **Windows without WSL** (via MSYS2). All three use the same `make` commands once set up.

Every platform needs:

- `git`, `make`, `gcc`, `g++`, Python 3
- `libpng` and `zlib` development headers
- an `arm-none-eabi` toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-as`, `arm-none-eabi-ld`, `arm-none-eabi-objcopy`)
- a copy of `baserom.gba` in the repo root (for patching and tests)

Pick one setup path below, then follow [Setup](#setup).

### Linux or WSL

On Ubuntu or WSL:

```bash
sudo apt update
sudo apt install build-essential git make libpng-dev zlib1g-dev python3
sudo apt install binutils-arm-none-eabi   # or another arm-none-eabi toolchain
```

### Windows (without WSL)

Use **devkitPro**. It gives you MSYS2 (a small Linux-like shell) and the ARM toolchain in one installer. You do not need WSL.

1. Download and run the [devkitPro installer](https://github.com/devkitPro/installer/releases).
   - In **Choose Components**, leave only **GBA Development** checked.
   - Keep the default install location (`C:\devkitpro`).

2. Open the devkitPro MSYS2 shell:
   - Start Menu → **devkitPro MSYS2**, or run `C:\devkitpro\msys2\msys2_shell.bat`.

3. Install the remaining build tools (paste into the MSYS2 window):

```bash
pacman -Sy msys2-keyring
pacman -S make gcc git zlib-devel libpng-devel python
```

4. Go to where you want the project (example: Desktop):

```bash
cd /c/Users/YourName/Desktop
```

Replace `YourName` with your Windows username. MSYS2 paths use `/c/` instead of `C:\`.

## Setup

1. Clone the repository.

```bash
git clone <your-repo-url> ygodm8
cd ygodm8
```

2. Clone, build, and install `agbcc`.

This project expects `tools/agbcc/bin/agbcc` to exist for your current environment. Run these commands in the **same shell** you will use for `make` (WSL, Linux, or MSYS2 — not PowerShell).

```bash
cd ..
git clone https://github.com/pret/agbcc.git
cd agbcc
./build.sh
./install.sh ../ygodm8
cd ../ygodm8
```

If you already have an `agbcc` checkout, you can reuse it instead of cloning a fresh copy.

3. Add `baserom.gba` to the `ygodm8` folder (same directory as the Makefile).

## Building

Build the ROM with:

```bash
make
```

This compiles the local helper tools first, then builds `ygodm8.gba` and `ygodm8.ups`.

The UPS patch is generated from `baserom.gba` to `ygodm8.gba`.

To skip UPS patch generation for a build:

```bash
make BUILD_UPS=0
```

To remove build output and rebuild from scratch:

```bash
make clean
make
```

To run the project test suite (host tests, validators, full ROM build, memory report):

```bash
make test
```

For a faster loop without linking the ROM:

```bash
make test-host
```

See [documentation/tdd-framework.md](documentation/tdd-framework.md) for what the framework is, why it exists, and the manual smoke checklist.

To verify the built ROM against the expected hash:

```bash
make compare
```

Expected SHA-1:

```text
dad3aa7dd470c9b475236fed2ea867b04ab1b089  ygodm8.gba
```

## Troubleshooting

### `tools/agbcc/bin/agbcc: not found`

This usually means `agbcc` is missing, stale, or was built in a different environment. Rebuild and reinstall it from the same environment you are using for this repo:

```bash
cd ../agbcc
./build.sh
./install.sh ../ygodm8
cd ../ygodm8
make clean
make
```

### `SHRT_MAX` undeclared

If you hit an error like:

```text
'SHRT_MAX' undeclared
```

add this include near the top of the source file using `SHRT_MAX`:

```c
#include <limits.h>
```

`agbcc` can be stricter than modern compilers about indirect includes.

### `arm-none-eabi-gcc: command not found`

Install an ARM embedded GCC toolchain and make sure the `arm-none-eabi` binaries are available in your shell `PATH`.

On Windows, open the **devkitPro MSYS2** shell (not PowerShell or CMD). devkitARM should already be on `PATH` there.

### Windows: `libpng-devel` not found

If `pacman -S libpng-devel` fails, install the other packages first, then ask for help or follow the libpng build steps in [pret/pokeemerald INSTALL.md](https://github.com/pret/pokeemerald/blob/master/INSTALL.md) under **Windows (msys2)**.

### Switched between WSL and Windows (or Linux)

Build tools are not interchangeable across environments. From the new shell:

```bash
cd ../agbcc
git clean -fX
./build.sh
./install.sh ../ygodm8
cd ../ygodm8
make clean
make
```

## Notes

- Always build from one environment: Linux, WSL, or MSYS2. Do not mix artifacts between them.
- PowerShell and CMD cannot run this build directly; use WSL or devkitPro MSYS2 on Windows.
- Manual `agbcc` installation is expected for older decompilation-style repositories like this one.
- See [CUSTOM_CONTENT.md](CUSTOM_CONTENT.md) for the custom folders and files in this repo.
