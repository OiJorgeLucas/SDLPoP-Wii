#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

VERSION="1.0"
DIST="dist-wii"
APP="$DIST/apps/sdlpop"
ZIP="SDLPoP-Wii-${VERSION}.zip"

required=(
  "boot.dol"
  "SDLPoP.ini"
  "src/gamecontrollerdb.txt"
  "wii/icon.png"
  "wii/meta.xml"
  "COPYING"
  "doc/THIRD_PARTY_NOTICES.md"
  "doc/licenses/libogc-LICENSE.txt"
  "doc/licenses/libfat-LICENSE.txt"
  "data"
  "mods/mods.txt"
)

for item in "${required[@]}"; do
  if [[ ! -e "$item" ]]; then
    echo "Erro: arquivo/diretório obrigatório não encontrado: $item" >&2
    exit 1
  fi
done

# Validate the Homebrew Channel icon without modifying it.
python3 - <<'PY'
from pathlib import Path
import struct

path = Path("wii/icon.png")
data = path.read_bytes()

if data[:8] != b"\x89PNG\r\n\x1a\n":
    raise SystemExit("Erro: wii/icon.png não é um PNG válido.")

width, height = struct.unpack(">II", data[16:24])

if (width, height) != (128, 48):
    raise SystemExit(
        f"Erro: wii/icon.png tem {width}x{height}; "
        "o esperado é 128x48."
    )

print("icon.png: 128x48 OK")
PY

rm -rf "$DIST"
rm -f "$ZIP"

mkdir -p "$APP/mods" "$APP/doc/licenses"

cp boot.dol "$APP/"
cp SDLPoP.ini "$APP/"
cp src/gamecontrollerdb.txt "$APP/gamecontrollerdb.txt"

cp wii/icon.png "$APP/icon.png"
cp wii/meta.xml "$APP/meta.xml"

cp COPYING "$APP/"
cp doc/THIRD_PARTY_NOTICES.md "$APP/doc/THIRD_PARTY_NOTICES.md"
cp doc/licenses/libogc-LICENSE.txt "$APP/doc/licenses/libogc-LICENSE.txt"
cp doc/licenses/libfat-LICENSE.txt "$APP/doc/licenses/libfat-LICENSE.txt"
cp -r data "$APP/"
cp mods/mods.txt "$APP/mods/mods.txt"

(
  cd "$DIST"
  zip -qr "../$ZIP" apps
)

echo
echo "Pacote criado:"
echo "  $DIST/apps/sdlpop/"
echo "  $ZIP"
