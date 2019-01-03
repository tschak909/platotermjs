#include <stdbool.h>
#include <stdio.h>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "splash.h"

unsigned char already_started=false;

int main(void)
{
  screen_init();
  ShowPLATO((padByte *)splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  for (;;)
    {
      keyboard_main();
      io_main();
    }
}
