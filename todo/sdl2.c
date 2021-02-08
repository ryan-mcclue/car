// SPDX-License-Identifier: zlib-acknowledgement

#include "SDL.h"

#include <stdint.h>

typedef uint8_t u8;

int
main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    // error
  }
  
  SDL_Window *window = SDL_CreateWindow("sdl2", 
                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         1024, 600, 0
                       );
  if (window == NULL) {
    // error
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    // error
  }

  u8 want_to_run = 1;
    while (want_to_run) {
    SDL_Event event = {0};
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        want_to_run = 0;
      }
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
