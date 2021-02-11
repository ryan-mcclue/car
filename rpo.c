// SPDX-License-Identifier: zlib-acknowledgement

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <X11/Xlib.h>

#define INTERNAL static
// IMPORTANT(Ryan): Ignore integer constant used as NULL pointer
#define ZERO_STRUCT_INIT /*lint -e9080*/ {0} /*lint +e9080*/

typedef unsigned int uint;

// IMPORTANT(Ryan): Ignore having no side-effects
//lint -esym(522 523, DEBUGGER_BREAK)
// NOTE(Ryan): Setup debugger to automatically break at this function call.
// include logging of error code with XGetErrorText() and just set xlib error handlers to nothing?
INTERNAL void DEBUGGER_BREAK(void)
{
  return;
}

int
main(int argc, char *argv[])
{
  // signed + unsigned (unsigned converted to signed)
  // will typically do sign extension when converting from signed to unsigned
  // note that only in expressions (or expression statement), not declarations
  // small integer data types, e.g char, short will be promoted to signed int before used in an expression.
  // if unsigned int, result will be unsigned
  // if (0xaa == 0xaa) --> how will these be converted to signed int (e.g. how is sign bit handled?)
  // will first try signed int if it can fit, will then try unsigned int

  return 0;
}
