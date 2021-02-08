#! /usr/bin/env bash
# SPDX-License-Identifier: zlib-acknowledgement

if [[ ! -d pi4b-build ]] && mkdir pi4b-build

# TODO(Ryan): Support NEON registers
aarch64-linux-gnu-gcc -nostartfiles -nostdlib -ffreestanding \
        -mgeneral-regs-only -c pi4b.c -o pi4b-build/pi4b.o 

aarch64-linux-gnu-gcc -c pi4b.s -o pi4b-build/pi4b.o

aarch64-linux-gnu-ld -T pi4b-linker.ld pi4b-build/pi4b.o pi4b-build/pi4b.o -o pi4b-build/pi4b.elf

# NOTE(Ryan): ELF file is intended to be executed by OS, so we extract relevent data
# kernel8 name indicates ARMv8, i.e. boot in 64-bit mode
aarch64-linux-gnu-objcopy pi4b-build/pi4b.elf -o pi4b-build/kernel8.img





copy_location_after_compiling=/media/parallels/boot

aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles --ffreestanding \
        -mgeneral-regs-only -MMD?? -c bmp.s -o bmp.o

# kernel image depends on linker script and object files
aarch64-linux-gnu-ld -T linker.ld -o kernel8.elf object_files

aarch64-linux-gnu-objcopy kernel8.elf -O binary kernel8.img 

cp {kernel8.img, config.txt} $copy_location_after_compiling

sync??

# 11:00 (1) for config.txt explanation
# opengl es for videocore

# raspberry pi 4b uses BCM2711 broadcom SoC
# what is the difference between bus and peripheral address?

# 1:00 (2) investigate UART from javidx9. can use GPIO or aux instead of uart?
# what about I2C, SPI, MMC??
# 2:50 (2) disparity between using c-style functions in our assebly code?
# 5:00 (2) assembly functions
# 9:00 (2) boot assembly file

# require USB to TTL serial cable for raspberry (i.e. USB to serial converter)

# 1. Understand boot sequence
# as the GPU firmware loads the elf file and then activates the cpu, the boot process is safe, i.e. can't brick board.
# hardware driver is essentially reading and writing words at special addresses with side effects.

# have to enable caching to get decent performance
# however, must state io regions of memory not cacheable as they have side effects.

# for multiple processors, have to assign different stack pointer to each
