# Third-Party Notices

This document summarizes third-party software used by the Nintendo Wii build of SDLPoP.

SDLPoP itself is distributed under the GNU General Public License, version 3 or later.
See the repository's `COPYING` file for the main project license.

## SDLPoP upstream

SDLPoP is an open-source port/conversion of Prince of Persia based on the DOS version disassembly.

Copyright (C) 2013-2025 Dávid Nagy and SDLPoP contributors.

License: GPL-3.0-or-later.

The upstream project also identifies `src/opl3.c`, `src/opl3.h` and
`src/stb_vorbis.c` as external components with their own licenses.

## Nuked OPL3

Files used by SDLPoP:

- `src/opl3.c`
- `src/opl3.h`

Copyright (C) 2013-2018 Alexey Khokholov (Nuke.YKT).

License: LGPL-2.1-or-later.

The complete license notice is retained in the corresponding source files.

## stb_vorbis

File used by SDLPoP:

- `src/stb_vorbis.c`

Original implementation by Sean Barrett.

`stb_vorbis` is offered under a choice of the MIT license or public-domain
dedication. The complete license notice is retained in the source file.

## SDL2 and SDL2_image

The Wii build links statically against SDL2 2.28.5 and SDL2_image 2.8.2.
supplied by the devkitPro Wii toolchain.

SDL2 and SDL2_image are distributed under the zlib license by their upstream
projects. Their original copyright and license notices remain available in the
respective upstream source distributions.

The Wii SDL2 package used by this port is maintained through devkitPro's
`pacman-packages` project and includes Wii-specific platform support.

## devkitPro / libogc Wii libraries

The Wii build also links against libraries from the devkitPro ecosystem,
including components represented by the following linker entries:

- `pthread`
- `aesnd`
- `opengx`
- `fat`
- `wiiuse`
- `bte`
- `wiikeyboard`
- `ogc`

These components are provided by devkitPro, libogc and related projects.
Individual files and subcomponents carry their own permissive copyright and
license notices. The applicable notices in the upstream projects remain the
authoritative terms.

libogc is principally maintained by Michael Wiedenbauer (shagkur), Dave Murphy
(WinterMute), and other contributors. Portions of its threading support are
derived from RTEMS/OAR work, as documented in libogc's license file.

libfat includes work by Michael "Chishm" Chisholm and Dave "WinterMute" Murphy
and is distributed under a BSD-style license.

OpenGX provides the OpenGL-like graphics layer used by the Wii SDL2 stack.

## libpng and zlib

SDL2_image in this Wii build links against libpng and zlib.

libpng is distributed under the PNG Reference Library License.

zlib is Copyright (C) Jean-loup Gailly and Mark Adler and is distributed under
the zlib license.

## libjpeg-turbo

SDL2_image in this Wii build also links against libjpeg-turbo through the
`jpeg` library interface.

libjpeg-turbo is distributed under compatible BSD-style and Independent JPEG
Group license terms.

Required attribution:

> This software is based in part on the work of the Independent JPEG Group.

## Source and license references

The complete source and license texts for the components listed above are
available from their respective upstream projects:

- SDLPoP: NagyD/SDLPoP
- SDL2: libsdl-org/SDL
- SDL2_image: libsdl-org/SDL_image
- devkitPro Wii packages: devkitPro/pacman-packages
- libogc: devkitPro/libogc
- libfat: devkitPro/libfat
- OpenGX: devkitPro/opengx
- libpng: pnggroup/libpng
- zlib: madler/zlib
- libjpeg-turbo: libjpeg-turbo/libjpeg-turbo
- stb: nothings/stb

This file is an attribution and license-reference summary. Where a component's
source file or upstream distribution contains a more specific notice, that
notice controls.

## Included redistribution notices

The release package also includes the following license and redistribution
notices:

- `doc/licenses/libogc-LICENSE.txt`
- `doc/licenses/libfat-LICENSE.txt`

These files are included with the binary distribution to preserve the
applicable upstream copyright, attribution and redistribution notices.