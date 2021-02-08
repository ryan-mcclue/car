from zero to main()
crossworks for ARM includes JTAG/SWD debugger
# assembly sections
Code and data are stored in sections, which are contiguous areas of memory.
There are no hard rules on the number of sections required.
Typically put symbols in same section if same region of memory, or initialised together
In ELF object file format, by convention we have (they can be named differently):
(they start with dot as they are convention)
.text --> code and constants (ROM)
.bss --> uninitialised data
.stack --> stack (RAM)
.data --> initialised data

what does the linker with these sections exactly?
word is natural size for processor?
what is the purpose of interrupts?
why are addresses for reset, interrupts, etc. called vector locations?

interrupt request:
interrupts may have to be enabled as a bit in a status register (so when in an interrupt can disable handling further interrupts) 
the cpu will communicate with source interrupt telling it has handled it, i.e. acknowledge (to handle many interrupts from same source)
designed for multiple sources
non-maskable interrupt:
negative edge (falling edge), i.e on initial. will run no matter what (highest priority. useful in small number of cases, e.g. on power loss)

linker and other code post-processing tools so that they are loaded into memory in a sensible way.
object files vs executables?
what are segments?
compiler generates object files which don't have addresses or symbols?
linker is most useful for referencing other object files and libraries.

# cpu nomenclature
arm ltd. is a company that develops ARM architecture. they license this out to companies who develop cpus using this arch?
do arm ltd. create cortex-m family which implements arm architecture? 
atmel ATSAMD21 uses cortex-m arm processor. so do atmel and other companies just introduce things like flash and peripherals packaging arm cpu as an mcu?
boards like Adafruit METRO M0 Express will use a mcu and add convenient ways to interface with this mcu like headers and power regulators?

# debugging
JTAG/SWD debug kit?
