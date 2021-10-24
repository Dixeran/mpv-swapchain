#!/bin/sh

DEST_OS=win32 TARGET=x86_64-w64-mingw32.static ./waf configure --enable-d3d11 --enable-libmpv-shared --disable-manpage-build
