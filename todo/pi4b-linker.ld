MEMORY 
{
  rom (rx): ORIGIN = 0x2000, LENGTH = 0x0400
  ram (rwx): ORIGIN = 0x2400, LENGTH = 0x5000
}
/* 
 * NOTE(Ryan): The compiler knows nothing about physical addresses
 */
SECTIONS 
{
  /* code and constants */
  /* input-filename(section) */
  .text:
  {
    *(.text*)    
  } > rom
  /* uninitialised static memory */
  .bss (NOLOAD):
  {
    *(.bss*)
  /* int global_x */
    *(COMMON) 
  } > ram

  STACK_SIZE = 0x2000;
  /* location counter tracks current offset into a memory region */
  /* align 8byte boundary per ARM procedure call standards */
  .stack (NOLOAD):
  {
    . = ALIGN(8);
    . = . + STACK_SIZE;
    . = ALIGN(8);
  } > ram
}
