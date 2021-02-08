#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

# IMPORTANT(Ryan):
# libx11-dev

[[ ! -d rpo-build ]] && mkdir rpo-build

gcc -g rpo.c -o rpo-build/rpo
