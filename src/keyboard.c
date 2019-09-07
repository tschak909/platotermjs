#include <SDL2/SDL.h>
#include <stdbool.h>
#include "keyboard.h"
#include "protocol.h"
#include "io.h"
#include "key.h"

unsigned char ch;

extern int something_happened;
extern SDL_Event event;

bool shift_pressed, ctrl_pressed;

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

/**
 * The following routines are literally because
 * SDL2 is fucking brain damaged, and sends each
 * and every key seperately. Thanks.
 */
unsigned char keyboard_ctrl_shift_sdlk_to_pkey(int k)
{
  switch(k)
    {
    case SDLK_1:
      ch=PKEY_GREATER_THAN;
      break;
    case SDLK_2:
      ch=PKEY_BRACKET_LEFT;
      break;
    case SDLK_3:
      ch=PKEY_BRACKET_RIGHT;
      break;
    case SDLK_4:
      ch=PKEY_DOLLAR;
      break;
    case SDLK_5:
      ch=PKEY_PERCENT;
      break;
    case SDLK_6:
      ch=PKEY_UNDERSCORE;
      break;
    case SDLK_7:
      ch=PKEY_APOSTROPHE;
      break;
    case SDLK_8:
      ch=PKEY_ASTERISK;
      break;
    case SDLK_9:
      ch=PKEY_PARENTHESIS_LEFT;
      break;
    case SDLK_0:
      ch=PKEY_LESS_THAN;
      break;
    case SDLK_MINUS:
      ch=PKEY_DELTA;
      break;
    case SDLK_EQUALS:
      ch=PKEY_PARENTHESIS_RIGHT;
      break;
    case SDLK_BACKSPACE:
      ch=PKEY_BACKSPACE;
      break;
    case SDLK_TAB:
      ch=PKEY_CR;
      break;
    case SDLK_q:
      ch=PKEY_ACCESS;
      break;
    case SDLK_w:
      break;
    case SDLK_e:
      ch=PKEY_EDIT1;
      break;
    case SDLK_r:
      ch=PKEY_ERASE1;
      break;
    case SDLK_t:
      ch=PKEY_TERM;
      break;
    case SDLK_u:
      break;
    case SDLK_i:
      break;
    case SDLK_o:
      break;
    case SDLK_p:
      ch=PKEY_SUPER1;
      break;
    case SDLK_LEFTBRACKET:
      ch=PKEY_BRACKET_LEFT;
      break;
    case SDLK_RIGHTBRACKET:
      ch=PKEY_BRACKET_RIGHT;
      break;
    case SDLK_BACKSLASH:
      break;
    case SDLK_a:
      ch=PKEY_TERM;
      break;
    case SDLK_s:
      ch=PKEY_STOP1;
      break;
    case SDLK_d:
      ch=PKEY_DATA1;
      break;
    case SDLK_f:
      ch=PKEY_FONT;
      break;
    case SDLK_g:
      ch=PKEY_INTERSECT;
      break;
    case SDLK_h:
      ch=PKEY_HELP1;
      break;
    case SDLK_j:
      break;
    case SDLK_k:
      break;
    case SDLK_l:
      ch=PKEY_LAB1;
      break;
    case SDLK_SEMICOLON:
      ch=PKEY_COLON;
      break;
    case SDLK_QUOTE:
      ch=PKEY_APOSTROPHE;
      break;
    case SDLK_RETURN:
      ch=PKEY_NEXT1;
      break;
    case SDLK_z:
      break;
    case SDLK_x:
      ch=PKEY_UNION;
      break;
    case SDLK_c:
      ch=PKEY_COPY1;
      break;
    case SDLK_v:
      break;
    case SDLK_b:
      ch=PKEY_BACK1;
      break;
    case SDLK_n:
      ch=PKEY_NEXT1;
      break;
    case SDLK_m:
      ch=PKEY_FONT;
      break;
    case SDLK_COMMA:
      ch=PKEY_QUOTE;
      break;
    case SDLK_PERIOD:
      ch=PKEY_EXCLAMATION;
      break;
    case SDLK_SLASH:
      ch=PKEY_QUESTION_MARK;
      break;
    case SDLK_SPACE:
      break;
    default:
      printf("Uncaught CTRL key 0x%02x",k);
    }
  return ch;
}

unsigned char keyboard_shift_sdlk_to_pkey(int k)
{
  switch(k)
    {
    case SDLK_UNKNOWN:
      break;
    case SDLK_ESCAPE:
      ch=PKEY_SHIFT;
      break;
    case SDLK_BACKQUOTE:
      ch=PKEY_TILDE;
      break;
    case SDLK_1:
      ch=PKEY_EXCLAMATION;
      break;
    case SDLK_2:
      ch=PKEY_QUOTE;
      break;
    case SDLK_3:
      ch=PKEY_POUND;
      break;
    case SDLK_4:
      ch=PKEY_DOLLAR;
      break;
    case SDLK_5:
      ch=PKEY_PERCENT;
      break;
    case SDLK_6:
      ch=PKEY_CIRCUMFLEX;
      break;
    case SDLK_7:
      ch=PKEY_AMPERSAND;
      break;
    case SDLK_8:
      ch=PKEY_ASTERISK;
      break;
    case SDLK_9:
      ch=PKEY_PARENTHESIS_LEFT;
      break;
    case SDLK_0:
      ch=PKEY_PARENTHESIS_RIGHT;
      break;
    case SDLK_MINUS:
      ch=PKEY_UNDERSCORE;
      break;
    case SDLK_EQUALS:
      ch=PKEY_PLUS;
      break;
    case SDLK_BACKSPACE:
      ch=PKEY_ERASE1;
      break;
    case SDLK_TAB:
      ch=PKEY_CR;
      break;
    case SDLK_q:
      ch=PKEY_Q;
      break;
    case SDLK_w:
      ch=PKEY_W;
      break;
    case SDLK_e:
      ch=PKEY_E;
      break;
    case SDLK_r:
      ch=PKEY_R;
      break;
    case SDLK_t:
      ch=PKEY_T;
      break;
    case SDLK_y:
      ch=PKEY_Y;
      break;
    case SDLK_u:
      ch=PKEY_U;
      break;
    case SDLK_i:
      ch=PKEY_I;
      break;
    case SDLK_o:
      ch=PKEY_O;
      break;
    case SDLK_p:
      ch=PKEY_P;
      break;
    case SDLK_LEFTBRACKET:
      ch=PKEY_LEFT_CURLY_BRACE;
      break;
    case SDLK_RIGHTBRACKET:
      ch=PKEY_RIGHT_CURLY_BRACE;
      break;
    case SDLK_BACKSLASH:
      ch=PKEY_BAR;
      break;
    case SDLK_a:
      ch=PKEY_A;
      break;
    case SDLK_s:
      ch=PKEY_S;
      break;
    case SDLK_d:
      ch=PKEY_D;
      break;
    case SDLK_f:
      ch=PKEY_F;
      break;
    case SDLK_g:
      ch=PKEY_G;
      break;
    case SDLK_h:
      ch=PKEY_H;
      break;
    case SDLK_j:
      ch=PKEY_J;
      break;
    case SDLK_k:
      ch=PKEY_K;
      break;
    case SDLK_l:
      ch=PKEY_L;
      break;
    case SDLK_SEMICOLON:
      ch=PKEY_COLON;
      break;
    case SDLK_QUOTE:
      ch=PKEY_QUOTE;
      break;
    case SDLK_RETURN:
      ch=PKEY_NEXT1;
      break;
    case SDLK_z:
      ch=PKEY_Z;
      break;
    case SDLK_x:
      ch=PKEY_X;
      break;
    case SDLK_c:
      ch=PKEY_C;
      break;
    case SDLK_v:
      ch=PKEY_V;
      break;
    case SDLK_b:
      ch=PKEY_B;
      break;
    case SDLK_n:
      ch=PKEY_N;
      break;
    case SDLK_m:
      ch=PKEY_M;
      break;
    case SDLK_COMMA:
      ch=PKEY_LESS_THAN;
      break;
    case SDLK_PERIOD:
      ch=PKEY_GREATER_THAN;
      break;
    case SDLK_SLASH:
      ch=PKEY_QUESTION_MARK;
      break;
    case SDLK_SPACE:
      ch=PKEY_BACKSPACE;
      break;
    default:
      printf("Uncaught SHIFT key: 0x%02x",k);
      break;
    }
  return ch;
}

unsigned char keyboard_ctrl_sdlk_to_pkey(int k)
{
  switch(k)
    {
    case SDLK_1:
      ch=PKEY_GREATER_THAN;
      break;
    case SDLK_2:
      ch=PKEY_BRACKET_LEFT;
      break;
    case SDLK_3:
      ch=PKEY_BRACKET_RIGHT;
      break;
    case SDLK_4:
      ch=PKEY_DOLLAR;
      break;
    case SDLK_5:
      ch=PKEY_PERCENT;
      break;
    case SDLK_6:
      ch=PKEY_UNDERSCORE;
      break;
    case SDLK_7:
      ch=PKEY_APOSTROPHE;
      break;
    case SDLK_8:
      ch=PKEY_ASTERISK;
      break;
    case SDLK_9:
      ch=PKEY_PARENTHESIS_LEFT;
      break;
    case SDLK_0:
      ch=PKEY_LESS_THAN;
      break;
    case SDLK_MINUS:
      ch=PKEY_DELTA;
      break;
    case SDLK_EQUALS:
      ch=PKEY_PARENTHESIS_RIGHT;
      break;
    case SDLK_BACKSPACE:
      ch=PKEY_ERASE;
      break;
    case SDLK_TAB:
      ch=PKEY_TAB;
      break;
    case SDLK_q:
      ch=PKEY_SQUARE;
      break;
    case SDLK_w:
      break;
    case SDLK_e:
      ch=PKEY_EDIT;
      break;
    case SDLK_r:
      ch=PKEY_ERASE;
      break;
    case SDLK_t:
      ch=PKEY_TERM;
      break;
    case SDLK_u:
      break;
    case SDLK_i:
      break;
    case SDLK_o:
      break;
    case SDLK_p:
      ch=PKEY_SUPER;
      break;
    case SDLK_LEFTBRACKET:
      ch=PKEY_BRACKET_LEFT;
      break;
    case SDLK_RIGHTBRACKET:
      ch=PKEY_BRACKET_RIGHT;
      break;
    case SDLK_BACKSLASH:
      break;
    case SDLK_a:
      ch=PKEY_ANS;
      break;
    case SDLK_s:
      ch=PKEY_STOP;
      break;
    case SDLK_d:
      ch=PKEY_DATA;
      break;
    case SDLK_f:
      ch=PKEY_FONT;
      break;
    case SDLK_g:
      ch=PKEY_DIVIDE;
      break;
    case SDLK_h:
      ch=PKEY_HELP;
      break;
    case SDLK_j:
      break;
    case SDLK_k:
      break;
    case SDLK_l:
      ch=PKEY_LAB;
      break;
    case SDLK_SEMICOLON:
      ch=PKEY_COLON;
      break;
    case SDLK_QUOTE:
      ch=PKEY_APOSTROPHE;
      break;
    case SDLK_RETURN:
      ch=PKEY_NEXT;
      break;
    case SDLK_z:
      break;
    case SDLK_x:
      ch=PKEY_MULTIPLY;
      break;
    case SDLK_c:
      ch=PKEY_COPY;
      break;
    case SDLK_v:
      break;
    case SDLK_b:
      ch=PKEY_BACK;
      break;
    case SDLK_n:
      ch=PKEY_NEXT;
      break;
    case SDLK_m:
      ch=PKEY_MICRO;
      break;
    case SDLK_COMMA:
      ch=PKEY_QUOTE;
      break;
    case SDLK_PERIOD:
      ch=PKEY_EXCLAMATION;
      break;
    case SDLK_SLASH:
      ch=PKEY_QUESTION_MARK;
      break;
    case SDLK_SPACE:
      break;
    default:
      printf("Uncaught CTRL key 0x%02x",k);
    }
  return ch;
}

unsigned char keyboard_sdlk_to_pkey(int k)
{
  switch(k)
    {
    case SDLK_UNKNOWN:
      break;
    case SDLK_ESCAPE:
      ch=PKEY_ASSIGN;
      break;
    case SDLK_BACKQUOTE:
      ch=PKEY_GRAVE;
      break;
    case SDLK_1:
      ch=PKEY_1;
      break;
    case SDLK_2:
      ch=PKEY_2;
      break;
    case SDLK_3:
      ch=PKEY_3;
      break;
    case SDLK_4:
      ch=PKEY_4;
      break;
    case SDLK_5:
      ch=PKEY_5;
      break;
    case SDLK_6:
      ch=PKEY_6;
      break;
    case SDLK_7:
      ch=PKEY_7;
      break;
    case SDLK_8:
      ch=PKEY_8;
      break;
    case SDLK_9:
      ch=PKEY_9;
      break;
    case SDLK_0:
      ch=PKEY_0;
      break;
    case SDLK_MINUS:
      ch=PKEY_MINUS;
      break;
    case SDLK_EQUALS:
      ch=PKEY_EQUALS;
      break;
    case SDLK_BACKSPACE:
      ch=PKEY_ERASE;
      break;
    case SDLK_TAB:
      ch=PKEY_TAB;
      break;
    case SDLK_q:
      ch=PKEY_q;
      break;
    case SDLK_w:
      ch=PKEY_w;
      break;
    case SDLK_e:
      ch=PKEY_e;
      break;
    case SDLK_r:
      ch=PKEY_r;
      break;
    case SDLK_t:
      ch=PKEY_t;
      break;
    case SDLK_y:
      ch=PKEY_y;
      break;
    case SDLK_u:
      ch=PKEY_u;
      break;
    case SDLK_i:
      ch=PKEY_i;
      break;
    case SDLK_o:
      ch=PKEY_o;
      break;
    case SDLK_p:
      ch=PKEY_p;
      break;
    case SDLK_LEFTBRACKET:
      ch=PKEY_BRACKET_LEFT;
      break;
    case SDLK_RIGHTBRACKET:
      ch=PKEY_BRACKET_RIGHT;
      break;
    case SDLK_BACKSLASH:
      ch=PKEY_BACKSLASH;
      break;
    case SDLK_a:
      ch=PKEY_a;
      break;
    case SDLK_s:
      ch=PKEY_s;
      break;
    case SDLK_d:
      ch=PKEY_d;
      break;
    case SDLK_f:
      ch=PKEY_f;
      break;
    case SDLK_g:
      ch=PKEY_g;
      break;
    case SDLK_h:
      ch=PKEY_h;
      break;
    case SDLK_j:
      ch=PKEY_j;
      break;
    case SDLK_k:
      ch=PKEY_k;
      break;
    case SDLK_l:
      ch=PKEY_l;
      break;
    case SDLK_SEMICOLON:
      ch=PKEY_SEMICOLON;
      break;
    case SDLK_QUOTE:
      ch=PKEY_APOSTROPHE;
      break;
    case SDLK_RETURN:
      ch=PKEY_NEXT;
      break;
    case SDLK_z:
      ch=PKEY_z;
      break;
    case SDLK_x:
      ch=PKEY_x;
      break;
    case SDLK_c:
      ch=PKEY_c;
      break;
    case SDLK_v:
      ch=PKEY_v;
      break;
    case SDLK_b:
      ch=PKEY_b;
      break;
    case SDLK_n:
      ch=PKEY_n;
      break;
    case SDLK_m:
      ch=PKEY_m;
      break;
    case SDLK_COMMA:
      ch=PKEY_COMMA;
      break;
    case SDLK_PERIOD:
      ch=PKEY_PERIOD;
      break;
    case SDLK_SLASH:
      ch=PKEY_SLASH;
      break;
    case SDLK_SPACE:
      ch=PKEY_SPACE;
      break;
    default:
      printf("Uncaught key: 0x%02x",k);
      break;
    }
  return ch;
}

void keyboard_main(void)
{
  
  if (something_happened==0)
    return;

  if (event.key.type==SDL_KEYDOWN)
    {
      SDL_Keycode key = event.key.keysym.sym;
      if ((key==SDLK_LSHIFT) || (key==SDLK_RSHIFT))
	{
	  shift_pressed=true;
	}
      else if ((key==SDLK_LCTRL) || (key==SDLK_RCTRL))
	{
	  ctrl_pressed=true;
	}
    }  
  else if (event.key.type==SDL_KEYUP)
    {
      SDL_Keycode key = event.key.keysym.sym;

      // Since modifiers come seperately, we need to do some
      // tangly logic to map things sanely.

      if ((key==SDLK_LSHIFT) || (key==SDLK_RSHIFT))
	{
	  shift_pressed=false;
	}
      else if ((key==SDLK_LCTRL) || (key==SDLK_RCTRL))
	{
	  ctrl_pressed=false;
	}
      else if ((shift_pressed==true) && (ctrl_pressed==true))
	keyboard_out(keyboard_ctrl_shift_sdlk_to_pkey(key));
      else if (shift_pressed==true)
	keyboard_out(keyboard_shift_sdlk_to_pkey(key));
      else if (ctrl_pressed==true)
	keyboard_out(keyboard_ctrl_sdlk_to_pkey(key));
      else 
	keyboard_out(keyboard_sdlk_to_pkey(key));
    }  
}

void keyboard_clear(void)
{
}

void keyboard_out_tty(char ch)
{
  io_send_byte(ch);
}
