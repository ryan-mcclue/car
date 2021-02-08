<!-- SPDX-License-Identifier: zlib-acknowledgement -->

IMPORTANT(Ryan): Seems better to just scp files over? 
gdbserver localhost:2001 binary

gdb-multiarch localhost:2001

/etc/incron.allow
incrontab -e 
script




1. Network boot Raspberry Pi OS (remote gdb debugging)
We have PXE (preboot execution environment) standard which boots software from network
Pi4 supports this (is this property of board, cpu, soc?)
For Pi4, we want to boot from SPI attached EEPROM

2. Network boot buildroot linux without X11 (remote gdb debugging)

3. Baremetal serial port boot (JTAG debugging with crossworks for arm)






install gcc-arm and gdb-arm (gdb-multiarch?)

we want to do nfs boot (can this be done via ethernet?)
or is simple ssh+scp the binary sufficient?

embedded linux is just referencing environment in which linux is run, i.e. low memory, architecture, etc.
buildroot simpler than yocto (no way to update on the fly)
just get libc and busybox


use an rtos if time-sensitive
