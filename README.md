# SDLPoP Wii

Nintendo Wii port of [SDLPoP](https://github.com/NagyD/SDLPoP), the open-source port of *Prince of Persia* based on the disassembly of the DOS version.

SDLPoP was created by **Dávid Nagy (NagyD)** with contributions from many other developers over the years. The Nintendo Wii version was ported by **OiJorgeLucas**.

The goal of this port is to preserve the original SDLPoP experience while making it feel at home on Nintendo Wii, with native controller support, Wii-specific video handling, optimized loading, portable application paths, Homebrew Channel integration, and support for the major features of SDLPoP.

## Features

* Wii Remote support.
* Wii Remote + Nunchuk support.
* Classic Controller support.
* GameCube Controller support.
* USB keyboard support.
* Controller hotplug support.
* Controller-based text entry without requiring a keyboard.
* Quicksave and quickload.
* 4× fast-forward.
* Screenshot capture.
* SDLPoP mods and custom levelsets.
* Replay playback and replay recording, with replay filtering by the active levelset.
* Wii-specific 4:3 and 16:9 presentation handling.
* Optimized loading for both DAT and extracted resources.
* Portable application paths and support for multiple independent installations.
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

The internal SDLPoP resource layout remains unchanged. Keep `data/`, `mods/` and other game resources in their normal locations inside the application directory.

The application folder does not need to be named `sdlpop`. See [Portable Application Paths](#portable-application-paths) for information about using multiple independent installations.

## Controls

SDLPoP Wii provides dedicated layouts for Wii Remote, Wii Remote + Nunchuk, Classic Controller and GameCube Controller.

Some *Prince of Persia* actions are contextual. Movement and action inputs may also be used for climbing, sword fighting and other situations when appropriate.

### Wii Remote — NES/Master System-style layout

Hold the Wii Remote horizontally.

| Button | Gameplay | Menus |
| --- | --- | --- |
| D-Pad | Movement | Navigate |
| 2 | Forward Jump / Block | Confirm |
| 1 | Special Actions / Grab | Back |
| A | Show remaining time | — |
| B | Crouch | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

### Wii Remote + Nunchuk — Wii-style layout

A Wii-specific layout built around analog movement.

| Button | Gameplay | Menus |
| --- | --- | --- |
| Nunchuk Stick | Movement | Navigate |
| Wii Remote D-Pad | Replay shortcuts | Navigate |
| A | Forward Jump / Block | Confirm |
| B | Special Actions / Grab | Back |
| Z | Crouch | — |
| C | Show remaining time | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

During gameplay, the Wii Remote D-Pad is reserved for replay controls and does not move the character when a Nunchuk is connected.

### Classic Controller — SNES-style layout

Designed as the traditional 16-bit-style control option.

| Button | Gameplay | Menus |
| --- | --- | --- |
| D-Pad / Left Stick | Movement | Navigate |
| B | Forward Jump / Block | Back |
| A / X | Special Actions / Grab | A: Confirm |
| Y | Show remaining time | — |
| L / R / ZL / ZR | Crouch | — |
| + | Pause menu | — |
| HOME | Quit confirmation | — |

The Right Stick is reserved for replay shortcuts and does not move the character.

### GameCube Controller

| Button | Gameplay | Menus |
| --- | --- | --- |
| D-Pad / Control Stick | Movement | Navigate |
| A | Forward Jump / Block | Confirm |
| B / X | Special Actions / Grab | B: Back |
| Y | Show remaining time | — |
| L / R | Crouch | — |
| Start | Pause menu | — |
| Z | Shortcut modifier | — |

The C-Stick is reserved for replay shortcuts and does not move the character. `Z` + `Start` opens the quit confirmation.

### Controller priority

When a Classic Controller is connected, it controls gameplay while only the Wii Remote `HOME` button remains active.

When a GameCube Controller is connected, it takes priority for gameplay. Wii Remote `HOME` remains available for the quit confirmation.

### USB keyboard

USB keyboards are supported and retain the original SDLPoP keyboard controls.

## Replay and Recording Shortcuts

When replay support is enabled, the following shortcuts are available:

| Action | Wii Remote | Nunchuk | Classic Controller | GameCube Controller |
| --- | --- | --- | --- | --- |
| Start / stop recording | `-` + D-Pad Left | D-Pad Left | `-` + Right Stick Left | `Z` + C-Stick Left |
| Start / next replay | `-` + D-Pad Right | D-Pad Right | `-` + Right Stick Right | `Z` + C-Stick Right |
| Next level during replay | `-` + D-Pad Up | D-Pad Up | `-` + Right Stick Up | `Z` + C-Stick Up |
| Next room during replay | `-` + D-Pad Down | D-Pad Down | `-` + Right Stick Down | `Z` + C-Stick Down |

On Wii Remote, Classic Controller and GameCube Controller, hold the modifier button before pressing or moving the directional control.

The Nunchuk uses the Wii Remote D-Pad directly for replay shortcuts and does not require a modifier.

USB keyboard replay controls remain unchanged from SDLPoP: `Ctrl` + `Tab` starts or stops recording, and `Tab` starts replay playback from the title screen.

## Screenshots

Screenshots can be captured directly from the supported Wii controllers:

| Controller | Shortcut |
| --- | --- |
| Wii Remote | `-` + `A` |
| Wii Remote + Nunchuk | `1` |
| Classic Controller | `-` + `Y` |
| GameCube Controller | `Z` + `Y` |

For shortcuts that use a modifier, hold the modifier button first and then press the screenshot button.

## Fast-Forward

SDLPoP Wii supports 4× fast-forward for quickly moving through gameplay and cutscenes.

| Controller | Shortcut |
| --- | --- |
| Wii Remote | — |
| Wii Remote + Nunchuk | Hold `2` |
| Classic Controller | Hold `-` + `ZR` |
| GameCube Controller | — |
| USB keyboard | Hold `` ` `` |

Fast-forward remains active only while the shortcut is held. Gameplay and audio are accelerated together.

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

## Game Data and Loading

SDLPoP Wii supports both original `.DAT` files and extracted game resources.

Both formats are fully supported and include Wii-specific loading optimizations. Extracted resources already load quickly enough that gameplay is not interrupted by noticeable waiting in normal use.

Using the original `.DAT` files is still recommended for the best possible performance, as many transitions can become effectively instantaneous.

Mods may also use the standard SDLPoP data layouts supported by the game.

## Video and Aspect Ratio

SDLPoP Wii automatically adapts its default presentation to the Wii system aspect ratio.

On a Wii configured for **16:9**, the default presentation uses **16:10 aspect correction** with **Fuzzy** scaling, providing proportions close to the original PC presentation while making good use of widescreen displays.

On a Wii configured for **4:3**, the game uses the normal full-width presentation with **Sharp** scaling.

Aspect correction can be changed from the in-game settings:

* **Off** — use the full available width.
* **16:10** — preserve the original 320×200-style proportions.
* **4:3** — present the game in a narrower traditional 4:3 frame.

The aspect correction setting only affects widescreen Wii configurations. On a Wii configured for 4:3, changing this setting has no visual effect.

The scaling method can also be changed independently between **Sharp**, **Fuzzy**, and **Blurry**.

## Portable Application Paths

SDLPoP Wii supports multiple independent installations on the same SD card or USB device.

For example:

```text
apps/
├── sdlpop/
├── sdlpop-original/
├── sdlpop-mod/
└── sdlpop-another-setup/
```

Each installation can keep its own configuration, game data, mods, saves and other files without interfering with the others.

The application folder can also be renamed freely, making it easy to keep separate setups for the original game, different mods or different configurations.

## Building

The Wii version can be built using the official devkitPro Docker image.

From the root of the repository, run:

```bash
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
  '
```

The resulting Wii executable is:

```text
boot.dol
```

To create the complete Homebrew Channel package, run:

```bash
./wii/package.sh
```

The packaging script validates the required metadata and icon, creates the Homebrew Channel directory structure under `dist-wii/`, and generates a versioned release ZIP.

## Credits

* **Jordan Mechner** — creator of *Prince of Persia* and author of the original Apple II source code that helped document and preserve the game.
* **Dávid Nagy (NagyD)** and all **SDLPoP contributors** — for creating, maintaining and expanding SDLPoP over the years. See the [upstream SDLPoP repository](https://github.com/NagyD/SDLPoP) for the full contributor credits.
* **Alberto Mardegan (mardy)** — for his Wii/GameCube SDL2 work, which was an important reference for this port.
* **devkitPro / libogc** — for the Wii development toolchain and libraries used by this port.

## Special Thanks

* **Ismael Cardoso**, my cousin, for introducing me to AI tools and teaching me how to use them to accelerate my learning and development process. His guidance made this port possible much sooner than it otherwise would have been.
* **Raimunda Aparecida Carvalho Cardoso**, my mother, and **Maria Sonia de Carvalho Cardoso**, my aunt, for their support and encouragement.
* **Erika da Conceição de Abreu Cardoso**, my future wife, for her support, patience and encouragement throughout this project.

## Upstream SDLPoP

SDLPoP is the upstream project on which SDLPoP Wii is based.

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

For third-party software used by the Nintendo Wii build, see:

```text
doc/THIRD_PARTY_NOTICES.md
```
