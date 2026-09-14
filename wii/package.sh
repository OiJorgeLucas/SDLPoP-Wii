#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

DIST="dist-wii"
APP="$DIST/apps/sdlpop"

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
    echo "Error: required file/directory not found: $item" >&2
    exit 1
  fi
done

rm -rf "$DIST"

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

echo
echo "Homebrew Channel metadata:"
echo

VERSION="$(
python3 - "$APP/meta.xml" <<'PY'
from datetime import datetime
from pathlib import Path
import re
import sys
import xml.etree.ElementTree as ET

path = Path(sys.argv[1])

try:
    root = ET.parse(path).getroot()
except ET.ParseError as exc:
    raise SystemExit(f"Error: {path} contains invalid XML: {exc}")

if root.tag != "app":
    raise SystemExit(f"Error: root element in {path} must be <app>.")

app_version = (root.get("version") or "").strip()
if app_version != "1":
    raise SystemExit(
        f'Error: invalid <app version="..."> attribute: '
        f'{app_version!r}; expected "1".'
    )

required_fields = (
    "name",
    "coder",
    "version",
    "release_date",
    "short_description",
    "long_description",
)

values = {}

for field in required_fields:
    element = root.find(field)

    if element is None:
        raise SystemExit(
            f"Error: required <{field}> field not found in {path}."
        )

    value = (element.text or "").strip()

    if not value:
        raise SystemExit(
            f"Error: required <{field}> field is empty in {path}."
        )

    values[field] = value

release_date = values["release_date"]
if not re.fullmatch(r"\d{14}", release_date):
    raise SystemExit(
        "Error: <release_date> must contain exactly 14 digits "
        "in YYYYMMDDHHMMSS format."
    )

try:
    datetime.strptime(release_date, "%Y%m%d%H%M%S")
except ValueError as exc:
    raise SystemExit(f"Error: <release_date> contains an invalid date/time: {exc}")

print(f"  app version:       {app_version}", file=sys.stderr)

for element in root:
    value = (element.text or "").strip()

    if "\n" in value:
        print(f"  {element.tag}:", file=sys.stderr)
        for line in value.splitlines():
            print(f"    {line}", file=sys.stderr)
    else:
        print(f"  {element.tag + ':':<19} {value}", file=sys.stderr)

print(values["version"])
PY
)"

ZIP="SDLPoP-Wii-${VERSION}.zip"

echo
echo "Homebrew Channel icon:"
echo

python3 - "$APP/icon.png" <<'PY'
from hashlib import sha256
from pathlib import Path
import struct
import sys

path = Path(sys.argv[1])
data = path.read_bytes()

if data[:8] != b"\x89PNG\r\n\x1a\n":
    raise SystemExit(f"Error: {path} is not a valid PNG file.")

if len(data) < 24:
    raise SystemExit(f"Error: {path} is truncated.")

width, height = struct.unpack(">II", data[16:24])

if (width, height) != (128, 48):
    raise SystemExit(
        f"Error: {path} is {width}x{height}; "
        "expected 128x48."
    )

print(f"  file:        {path}")
print(f"  dimensions:  {width}x{height} OK")
print(f"  SHA-256:    {sha256(data).hexdigest()}")
PY

rm -f "$ZIP"

(
  cd "$DIST"
  zip -qr "../$ZIP" apps
)

echo
echo "Package created:"
echo "  $DIST/apps/sdlpop/"
echo "  $ZIP"
