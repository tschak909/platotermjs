#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "splash.h"

unsigned char already_started=false;
SDL_Event event;
int something_happened;

static double _emsc_width = 0;
static double _emsc_height = 0;

extern unsigned char DoNotSend;

void loop(void)
{
  something_happened=SDL_PollEvent(&event);
  keyboard_main();
  io_main();
  screen_main();
}

/* track CSS element size changes and update the WebGL canvas size */
static EM_BOOL _emsc_size_changed(int event_type, const EmscriptenUiEvent* ui_event, void* user_data) {
  emscripten_get_element_css_size("#canvas", &_emsc_width, &_emsc_height);
  emscripten_set_canvas_element_size("#canvas", _emsc_width, _emsc_height);
  return true;
}

int main(void)
{
  screen_init();
  DoNotSend=1;
  ShowPLATO((padByte *)splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  DoNotSend=0;
  emscripten_get_element_css_size("#canvas", &_emsc_width, &_emsc_height);
  emscripten_set_canvas_element_size("#canvas", _emsc_width, _emsc_height);
  emscripten_set_resize_callback(0, 0, false, _emsc_size_changed);
  emscripten_set_main_loop(loop,0,0);
}
