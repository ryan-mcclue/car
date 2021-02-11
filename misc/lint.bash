#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

# must provide compiler defined macros: -dFOO, -dFOO=1 (the location of these may be important)

# IMPORTANT(Ryan): For some reason, running from $PATH will not pick up license file 
# 9080 --> 
~/prog/apps/pc-lint/pclp64_linux \
        -i/home/ryan/prog/personal/car \
        -i/home/ryan/prog/apps/pc-lint/config \
        -format="%f:%l:%c: %m" -summary -max_threads=$(getconf _NPROCESSORS_ONLN) \
        /home/ryan/prog/apps/pc-lint/lnt/au-misra3.lnt \
        /home/ryan/prog/apps/pc-lint/config/pclint-conf-gcc.lnt \
        -wlib\(4\) -wlib\(1\) \
        -e970 \
        rpo.c

# IMPORTANT(Ryan): 970: Ignore no typedef for integer variable
# probably best to include this for the entire platform layer
