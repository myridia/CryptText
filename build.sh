#!/bin/sh
rm build -Rf
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local/nappgui
cmake --build build
build/Release/bin/crypttext

