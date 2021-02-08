#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

gcc -I ~/Downloads/SDL2-2.0.14/include -L ~/Downloads/SDL2-2.0.14/build -g sdl2.c -o sdl2 -lSDL2 -ldl -lm -pthread
