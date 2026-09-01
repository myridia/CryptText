# AGENTS.md — CryptText

## What this is
A C-based notepad/editor built with the NAppGUI toolkit that encrypts text entered by the user.

## Stack
- C (NAppGUI toolkit)
- CMake build system

## Build
```bash
sudo apt-get install libcurl4-gnutls-dev libgtk-3-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
./build.sh
```

## Run
```bash
./build/./crypttext   # output binary
```

## Structure
- `src/crypttext.c` — main application
- `src/libs.c`, `src/libs.h` — helper libraries (encryption logic)
- `src/res/` — icons (icns/ico)
- `CMakeLists.txt` — top-level build config
- `build.sh` — build script

## Conventions
- No comments in code unless asked.
- Verify: `cmake . && make`