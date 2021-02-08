#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

gcc-aarch64-linux-gnu -g rpo.c -o rpo | tee compile-output.txt

[[ $(grep -q error compile-output.txt) ]] && exit 1;

# add -q ?
scp rpo ryan@10.0.0.8:~/rpo
