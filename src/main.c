#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "splash.h"

unsigned char already_started=false;

void loop(void)
{
  keyboard_main();
  io_main();
  SDL_Delay(16);
}

int main(void)
{
  screen_init();
  ShowPLATO((padByte *)splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  emscripten_set_main_loop(loop,0,0);
}
