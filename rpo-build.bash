#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

[[ ! -d rpo-build ]] && mkdir rpo-build

# libx11-dev
gcc -g rpo.c -o rpo-build/rpo -lX11
