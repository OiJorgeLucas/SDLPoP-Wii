# SDLPoP Wii

Nintendo Wii port of [SDLPoP](https://github.com/NagyD/SDLPoP), the open-source port of *Prince of Persia* based on the disassembly of the DOS version.

**SDLPoP Wii 1.0** is developed by **OiJorgeLucas**.

The goal of this port is to preserve the original SDLPoP experience while making it feel at home on Nintendo Wii, with native controller layouts, Wii-specific video handling, portable application paths, loading optimizations, Homebrew Channel integration, and support for the major features of SDLPoP.

## Features

* Wii Remote support.
* Wii Remote + Nunchuk support.
* Classic Controller support.
* USB keyboard support.
* Controller hotplug support.
* Controller-based text entry.
* Quicksave and quickload.
* SDLPoP mods and custom levelsets.
* Replay playback and replay recording.
* Replay filtering by the currently active levelset.
* Wii-specific 4:3 and 16:9 presentation handling.
* Wii-specific resource and directory caching.
* Optimized loading for both DAT and extracted resources.
* Portable paths based on the directory containing `boot.dol`.
* Multiple independent installations with separate configurations.
* Clean return to the Homebrew Channel.

## Installation

Extract the release ZIP to the root of your SD card or USB device.

The standard installation is:

```text
apps/
└── sdlpop/
    ├── boot.dol
    ├── icon.png
    ├── meta.xml
    ├── SDLPoP.ini
    ├── gamecontrollerdb.txt
    ├── COPYING
    ├── data/
    ├── mods/
    │   └── mods.txt
    └── doc/
        └── THIRD_PARTY_NOTICES.md
```

Then launch **SDLPoP Wii** from the Homebrew Channel.

The Wii build uses the directory containing `boot.dol` as its application root. The folder does not need to be named `sdlpop`.

For example, these can coexist as completely independent installations:

```text
apps/sdlpop/
apps/princess/
apps/another-config/
```

Each installation can have its own `SDLPoP.ini`, saves, replays, mods and selected levelset.

The internal SDLPoP resource layout remains unchanged. Keep `data/`, `mods/` and other game resources in their normal locations inside the application directory.

## Controls

SDLPoP Wii provides three dedicated Wii controller layouts.

Some Prince of Persia actions are contextual. For example, movement and action inputs may also be used for climbing, sword fighting or other situations when appropriate.

### Classic Controller — SNES-style layout

Designed as the traditional 16-bit-style control option.

| Button | Gameplay | Menus |
| --- | --- | --- |
| D-Pad / Left Stick | Movement | Navigate |
| B | Forward Jump | Back |
| A | Special Actions (shuffle, grab, etc.) | Confirm |
| X | Grab | — |
| Y | Show remaining time | — |
| L / R | Crouch | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

### Wii Remote — NES/Master System-style layout

Hold the Wii Remote horizontally.

| Button | Gameplay | Menus |
| --- | --- | --- |
| D-Pad | Movement | Navigate |
| 2 | Forward Jump | Confirm |
| 1 | Special Actions (shuffle, grab, etc.) | Back |
| A | Show remaining time | — |
| B | Crouch | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

### Wii Remote + Nunchuk — Wii-style layout

A Wii-specific layout built around analog movement and the Wii Remote face buttons.

| Button | Gameplay | Menus |
| --- | --- | --- |
| Nunchuk Stick / D-Pad | Movement | Navigate |
| A | Forward Jump | Confirm |
| B | Special Actions (shuffle, grab, etc.) | Back |
| Z | Crouch | — |
| C | Show remaining time | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

### Replay and recording shortcuts

The `-` button acts as the replay shortcut modifier and must be held first.

**Wii Remote**

* `-` + D-Pad Right: view or cycle through replays.
* `-` + D-Pad Left: start or stop replay recording.

**Classic Controller**

* `-` + D-Pad Right: view or cycle through replays.
* `-` + D-Pad Left: start or stop replay recording.

**Wii Remote + Nunchuk**

* `-` + `1`: view or cycle through replays.
* `-` + `2`: start or stop replay recording.

### USB keyboard

USB keyboards are supported and retain the original SDLPoP keyboard controls.

## Quicksave and Quickload

SDLPoP's exact-state quicksave and quickload features are supported on Wii.

They can be used through the in-game menu, and the normal SDLPoP keyboard shortcuts remain available when using a USB keyboard.

The Wii port includes a same-level quickload optimization that can reuse already loaded level resources when possible.

## Mods

SDLPoP Wii supports SDLPoP mod folders and custom levelsets.

Place a mod inside:

```text
mods/<ModName>/
```

Then edit `SDLPoP.ini`:

```ini
levelset = ModName
```

Only files that differ from the base game need to be present in the mod directory.

A short mod installation guide is included in:

```text
mods/mods.txt
```

Mod resources continue to use the standard SDLPoP directory structure.

## Replays and Recording

Replay playback and replay recording are fully supported.

Replays are stored as `.P1R` files using SDLPoP's existing replay system.

On Wii, replay selection is filtered to the currently active levelset. This keeps replay browsing separate between the original game and different mods.

For example:

```text
original levelset → original replays
Princess levelset → Princess replays
another mod       → that mod's replays
```

Replay loading also benefits from Wii-specific resource caching.

## Game Data and Loading

SDLPoP Wii supports both DAT files and extracted resources.

DAT resources generally provide the fastest loading path. Extracted resources are also fully supported.

The Wii port adds several loading optimizations for the console's filesystem characteristics, including:

* cached directory lookups;
* cached original environment resources;
* cached raw extracted Kid resources used when rebuilding sprites;
* hidden preload work during the opening sequence when the original game is using extracted or mixed resources.

DAT-based original installations and mods continue to use their normal loading paths.

Do not remove DAT files that are already part of the standard SDLPoP distribution.

## Video and Aspect Ratio

The Wii build always runs fullscreen.

SDLPoP renders internally on its 320×200 logical canvas. Wii-specific aspect-ratio handling is applied only during final presentation.

On a Wii configured for **16:9**, enabling **Correct aspect ratio** compensates for widescreen stretching and presents the game at its intended proportions.

On a Wii configured for **4:3**, the normal full-width presentation is retained.

## Portable Application Paths

Unlike desktop builds that may search multiple system locations, the Wii port resolves its files from the directory containing the running `boot.dol`.

This makes the application portable and allows multiple independent SDLPoP installations on the same SD card or USB device.

Save files and other writable files are also kept relative to that application directory.

## Startup Input Note

On some Wii setups, Wii Remote and USB keyboard input may take a brief moment to become available after launch.

If the first input on the splash screen is not detected, wait a moment and press again.

This does not affect normal gameplay controls.

## Building

The Wii port is built with **devkitPPC** and the Wii libraries provided by **devkitPro**.

The project uses `Makefile.wii`.

### Docker build

The development workflow used for the Wii port can be reproduced with the official devkitPro container:

```bash
cd ~/projetos/SDLPoP

docker run --rm \
  -v "$PWD":/src \
  -w /src \
  devkitpro/devkitppc:latest \
  bash -lc '
    export DEVKITPRO=/opt/devkitpro
    export DEVKITPPC=/opt/devkitpro/devkitPPC
    export PATH=$DEVKITPPC/bin:/opt/devkitpro/tools/bin:$PATH
    export WIIPORTLIBS=$DEVKITPRO/portlibs/wii
    export PPCPORTLIBS=$DEVKITPRO/portlibs/ppc
    export PKG_CONFIG_PATH=$WIIPORTLIBS/lib/pkgconfig:$PPCPORTLIBS/lib/pkgconfig

    make -f Makefile.wii clean
    make -f Makefile.wii -j2
  ' 2>&1 | tee build-wii.log
```

A successful build produces:

```text
prince.elf
boot.dol
```

### Local devkitPro build

A local devkitPro installation can be used instead of Docker.

Install devkitPPC and the Wii portlibs required by the project, including SDL2 and SDL2_image, then configure the standard devkitPro environment.

For the usual `/opt/devkitpro` installation:

```bash
cd ~/projetos/SDLPoP

export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=$DEVKITPRO/devkitPPC
export PATH=$DEVKITPPC/bin:$DEVKITPRO/tools/bin:$PATH
export WIIPORTLIBS=$DEVKITPRO/portlibs/wii
export PPCPORTLIBS=$DEVKITPRO/portlibs/ppc
export PKG_CONFIG_PATH=$WIIPORTLIBS/lib/pkgconfig:$PPCPORTLIBS/lib/pkgconfig

make -f Makefile.wii clean
make -f Makefile.wii -j2
```

If devkitPro is installed somewhere else, adjust `DEVKITPRO` accordingly.

### Creating the Wii package

After building `boot.dol`, create the Homebrew Channel directory and release ZIP with:

```bash
cd ~/projetos/SDLPoP
./wii/package.sh
```

The packaging script validates the Homebrew Channel icon and creates:

```text
dist-wii/apps/sdlpop/
SDLPoP-Wii-1.0.zip
```

The package can be inspected with:

```bash
find dist-wii -type f | sort
unzip -l SDLPoP-Wii-1.0.zip
```

## Credits

* [Jordan Mechner](https://github.com/jmechner) — creator of *Prince of Persia*.
* [Dávid Nagy (NagyD)](https://github.com/NagyD) — creator of SDLPoP.
* [Alberto Mardegan (mardy)](https://github.com/mardy) — for his Wii/GameCube SDL2 work, which was an important reference for this port.
* **devkitPro / libogc** — for the Wii development toolchain and libraries used by this port.

See [`doc/THIRD_PARTY_NOTICES.md`](doc/THIRD_PARTY_NOTICES.md) for additional third-party attribution and license information.

## Special Thanks

* [Ismael Cardoso](https://github.com/ismaelcardosos), my cousin, for introducing me to AI tools and teaching me how to use them to accelerate my learning and development process. His guidance made this port possible much sooner than it otherwise would have been.
* **Raimunda Aparecida Carvalho Cardoso**, my mother, and **Maria Sonia de Carvalho Cardoso**, my aunt, for their support and encouragement.
* **Erika da Conceição de Abreu Cardoso**, my future wife, for her support, patience and encouragement throughout this project.

## Upstream SDLPoP

SDLPoP is an open-source port/conversion of the DOS game *Prince of Persia*, based on the disassembly of the original PoP1 for DOS and extended with many additional features.

Upstream repository:

https://github.com/NagyD/SDLPoP

SDLPoP forum board:

https://forum.princed.org/viewforum.php?f=126

## License

SDLPoP is free software distributed under the terms of the **GNU General Public License, version 3 or later**.

See:

* `COPYING`
* `src/GPLv3.h`

The following source files are external components with their own licenses:

* `src/opl3.c`
* `src/opl3.h`
* `src/stb_vorbis.c`
