#include <SDL2/SDL.h>
#include "keyboard.h"
#include "key.h"
#include "protocol.h"
#include "io.h"

unsigned char ch;

extern int something_happened;
extern SDL_Event event;

void keyboard_out(unsigned char platoKey)
{
  if (platoKey==0xff)
    return;
  
  if (platoKey>0x7F)
    {
      Key(ACCESS);
      Key(ACCESS_KEYS[platoKey-0x80]);
      return;
    }
  Key(platoKey);
  return;
}

void keyboard_main(void)
{
  if (something_happened==0)
    return;

  if (event.key.type==SDL_KEYDOWN)
    {
      SDL_Keycode key = event.key.keysym.sym;
      keyboard_out(key_to_pkey[key]);
    }
  
  /* if (kbhit()) */
  /*   { */
  /*     ch=cgetc(); */
  /*     if (TTY) */
  /* 	{ */
  /* 	  keyboard_out_tty(ch); */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  keyboard_out(key_to_pkey[ch]); */
  /* 	}  */
  /*   } */
}

void keyboard_clear(void)
{
}

void keyboard_out_tty(char ch)
{
  io_send_byte(ch);
}
