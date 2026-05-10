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

You will need:

- Linux or WSL
- `git`
- `make`
- `gcc`
- `g++`
- `libpng` development headers
- `zlib` development headers
- an `arm-none-eabi` toolchain in `PATH`

On Ubuntu or WSL, install the base dependencies with:

```bash
sudo apt update
sudo apt install build-essential git make libpng-dev zlib1g-dev
```

You will also need an ARM embedded toolchain that provides `arm-none-eabi-gcc`, `arm-none-eabi-as`, `arm-none-eabi-ld`, and `arm-none-eabi-objcopy`.

## Setup

1. Clone the repository.

```bash
git clone <your-repo-url> ygodm8
cd ygodm8
```

2. Clone, build, and install `agbcc`.

This project expects `tools/agbcc/bin/agbcc` to exist for your current environment.

```bash
cd ..
git clone https://github.com/pret/agbcc.git
cd agbcc
./build.sh
./install.sh ../ygodm8
cd ../ygodm8
```

If you already have an `agbcc` checkout, you can reuse it instead of cloning a fresh copy.

## Building

Build the ROM with:

```bash
make
```

This compiles the local helper tools first, then builds `ygodm8.gba`.

To remove build output and rebuild from scratch:

```bash
make clean
make
```

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

## Notes

- Build artifacts or tools compiled outside WSL may not work correctly inside WSL.
- If you switch environments, rebuild `agbcc` from within that environment.
- Manual `agbcc` installation is expected for older decompilation-style repositories like this one.
