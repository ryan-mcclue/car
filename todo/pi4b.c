// SPDX-License-Identifier: zlib-acknowledgement

// TODO(Ryan): Why arm used in embedded?
#pragma once // Easier and supported?

typedef uint32_t u32;
typedef volatile u32 reg32;

// TODO(Ryan): Make these figures tangible through programs using them
// NOTE(Ryan): BCM2711 SoC  
// quad-core cortex-a72 armv8, 1.5GHz
// 8GB LPDDR4-2400 SDRAM
// 32Kb data + 48Kb instruction L1 cache per core. 1MB l2 cache
// opengl es, 3.0
// faster i/o due to pci-e bus

// NOTE(Ryan):
// Can power board with USB-TO-TTL (green is TX for a UART. can use wires from USB mouse)
// This overcomes cable tightness with micro-HDMI and USB-C
// sudo screen /dev/ttyUSB0 115200
// sudo shutdown -h now

// NOTE(Ryan):
// 1. Boot sequence:
//   - GPU will load bootcode.bin into L2 cache then it goes and loads start.elf into RAM.
//   - start.elf deals with config.txt and will then load kernel8.img at 0x8000 (this will be different for pi4)
//   (when you say a word is the size the cpu can conveniently manipulate?)
//   - So, to start simply replace kernel8.img with machine code for infinite loop
//
//   armv8 architecture reference manual
//   raspberry pi is von neumann architecture, i.e. cpu (alu, general/special registers, control unit), ram and peripherals (on the SoC like timer, UART, gpu) all connected via a bus
//   it is a store and load architecture, i.e. if wanting to talk to peripheral store, get input load
//   general purpose registers (program counter, link register, stack pointer, etc.)
//   special register (instruction register, cpsr (status register with flags, control bits etc.))
//   TODO(Ryan): Is this prefetch instruction pipeline unique to ARM?, i.e. having to -2 offsets
//   instruction pipeline is fetch, decode and execute. while we are decoding, we can fetch, etc. for branching, this causes the pipeline to be reloaded
//
//   inside SoC, have GPIO controller (peripherals) which in itself has registers.
//   although 0x7e20, we use 0x2020 due to processor mode?
//   immediate value is constant

void
kernel_main(void)
{
  uart_init();
  uart_send_string("hello world!\n");
}
