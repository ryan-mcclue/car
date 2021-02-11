#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

gcc-aarch64-linux-gnu -g rpo.c -o rpo | tee compile-output.txt

[[ $(grep -q error compile-output.txt) ]] && exit 1;

# add -q ?
scp rpo ryan@10.0.0.8:~/rpo

#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

# IMPORTANT(Ryan): For sources (TODO(Ryan): add vim lookups)
# GLIBC (crashes if trying to start within libc --> perhaps something to do with not finding library?)
# sudo apt install libc6-dbg glibc-source
# tar xvf /usr/src/glibc/....tar.xz
# add path mapping in source lookup for cdt debugger 

# MUSL
# ./configure --enable-debug; make; sudo make install
# /lib/ld-musl-$ARCH.so.1
# /etc/ld-musl-$ARCH.path

# XLIB
# sudo apt install build-essential xutils-dev
# ./autogen.sh; CC=musl-gcc ./configure; make; sudo make install
# echo /usr/local/lib >> /etc/ld.so.conf.d/99local.conf; sudo ldconfig

[[ ! -d rpo-build ]] && mkdir rpo-build


# gcc -g rpo.c -o rpo-build/rpo -I/usr/local/include -L/usr/local/lib -lX11
# IMPORTANT(Ryan): This wrapper only supports C applications out of the box.
# gcc can be changed with $REALGCC
/usr/local/musl/bin/musl-gcc -static -g rpo.c -o rpo-build/rpo -I/usr/local/include -L/usr/local/lib -l:libxcb.a
