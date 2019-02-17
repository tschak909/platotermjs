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
SDL_Event event;
int something_happened;

extern unsigned char DoNotSend;

void loop(void)
{
  something_happened=SDL_PollEvent(&event);
  keyboard_main();
  io_main();
  screen_main();
}

int main(void)
{
  screen_init();
  DoNotSend=1;
  ShowPLATO((padByte *)splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  DoNotSend=0;
  emscripten_set_main_loop(loop,0,0);
}
