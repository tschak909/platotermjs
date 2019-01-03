/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * screen.c - Display output functions
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <unistd.h>
#include <stdlib.h>
#include "screen.h"
#include "protocol.h"
#include "font.h"

unsigned char CharHigh=16;
unsigned char CharWide=8;
padPt TTYLoc;

SDL_Window *window;
SDL_Renderer *renderer;
padRGB backgroundColor={0,0,0};
padRGB foregroundColor={255,255,255};

short max(short a, short b) { return ( a > b ) ? a : b; }
short min(short a, short b) { return ( a < b ) ? a : b; }

extern padBool FastText;

/**
 * screen_init() - Set up the screen
 */
void screen_init(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(512,512,0,&window,&renderer);
  screen_clear();
}

/**
 * screen_wait(void) - Sleep for approx 16.67ms
 */
void screen_wait(void)
{
}

/**
 * screen_beep(void) - Beep the terminal
 */
void screen_beep(void)
{
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
  SDL_SetRenderDrawColor(renderer,backgroundColor.red,backgroundColor.green,backgroundColor.blue,255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer,foregroundColor.red,foregroundColor.green,foregroundColor.blue,255);
}

/**
 * screen_set_pen_mode(void) - Set pen mode
 */
void screen_set_pen_mode(void)
{
  if ((CurMode==ModeErase)||(CurMode==ModeInverse))
    SDL_SetRenderDrawColor(renderer,backgroundColor.red,backgroundColor.green,backgroundColor.blue,255);
  else
    SDL_SetRenderDrawColor(renderer,foregroundColor.red,foregroundColor.green,foregroundColor.blue,255);
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{
  SDL_Rect rect;
  short x1;
  short y1;
  short x2;
  short y2;

  x1=min(Coord1->x,Coord2->x);
  x2=max(Coord1->x,Coord2->x);
  y1=min(Coord1->y,Coord2->y);
  y2=max(Coord1->y,Coord2->y);
  
  screen_set_pen_mode();
  rect.x=x1;
  rect.y=y1;
  rect.w=x2-x1;
  rect.h=y2-y1;
  SDL_RenderFillRect(renderer,&rect);
  SDL_RenderPresent(renderer);
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
  screen_set_pen_mode();
  SDL_RenderDrawPoint(renderer,Coord->x,Coord->y);
  SDL_RenderPresent(renderer);
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  screen_set_pen_mode();
  SDL_RenderDrawLine(renderer,Coord1->x,Coord1->y,Coord2->x,Coord2->y);
  SDL_RenderPresent(renderer);
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{
    short offset; /* due to negative offsets */
  unsigned short x;      /* Current X and Y coordinates */
  unsigned short y;
  unsigned short* px;   /* Pointers to X and Y coordinates used for actual plotting */
  unsigned short* py;
  unsigned char i; /* current character counter */
  unsigned char a; /* current character byte */
  unsigned char j,k; /* loop counters */
  char b; /* current character row bit signed */
  char width=8;
  char height=16;
  short deltaX=1;
  short deltaY=1;
  unsigned char *p;
  unsigned char* curfont;
  padRGB mainColor;
  padRGB altColor;

  if (CurMode==ModeRewrite)
    {
      altColor.red=backgroundColor.red;
      altColor.green=backgroundColor.green;
      altColor.blue=backgroundColor.blue;
    }
  else if (CurMode==ModeInverse)
    {
      altColor.red=foregroundColor.red;
      altColor.green=foregroundColor.green;
      altColor.blue=foregroundColor.blue;
    }

  if (CurMode==ModeErase || CurMode==ModeInverse)
    {
      mainColor.red=backgroundColor.red;
      mainColor.green=backgroundColor.green;
      mainColor.blue=backgroundColor.blue;
    }
  else
    {
      mainColor.red=foregroundColor.red;
      mainColor.green=foregroundColor.green;
      mainColor.blue=foregroundColor.blue;
    }

  switch(CurMem)
    {
    case M0:
      curfont=font;
      offset=-32;
      break;
    case M1:
      curfont=font;
      offset=64;
      break;
    case M2:
      curfont=fontm23;
      offset=-32;
      break;
    case M3:
      curfont=fontm23;
      offset=32;      
      break;
    }

  x=Coord->x;
  y=Coord->y;
  
  if (FastText==padF)
    {
      goto chardraw_with_fries;
    }

  /* the diet chardraw routine - fast text output. */
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      
      for (j=0;j<16;++j)
  	{
  	  b=*p;
	  
  	  for (k=0;k<8;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  SDL_SetRenderDrawColor(renderer,mainColor.red,mainColor.green,mainColor.blue,255);
		  SDL_RenderDrawPoint(renderer,x,y);
		  SDL_RenderPresent(renderer);
		}

	      ++x;
  	      b<<=1;
  	    }

	  ++y;
	  x-=width;
	  ++p;
  	}

      x+=width;
      y-=height;
    }

  return;

 chardraw_with_fries:
  if (Rotate)
    {
      deltaX=-abs(deltaX);
      width=-abs(width);
      px=&y;
      py=&x;
    }
    else
    {
      px=&x;
      py=&y;
    }
  
  if (ModeBold)
    {
      deltaX = deltaY = 2;
      width<<=1;
      height<<=1;
    }
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      for (j=0;j<16;++j)
  	{
  	  b=*p;

	  if (Rotate)
	    {
	      px=&y;
	      py=&x;
	    }
	  else
	    {
	      px=&x;
	      py=&y;
	    }

  	  for (k=0;k<8;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  SDL_SetRenderDrawColor(renderer,mainColor.red,mainColor.green,mainColor.blue,255);
		  if (ModeBold)
		    {
		      SDL_RenderDrawPoint(renderer,*px+1,*py);
		      SDL_RenderDrawPoint(renderer,*px,*py+1);
		      SDL_RenderDrawPoint(renderer,*px+1,*py+1);
		      SDL_RenderPresent(renderer);
		    }
		  SDL_RenderDrawPoint(renderer,*px,*py);
		  SDL_RenderPresent(renderer);
		}
	      else
		{
		  if (CurMode==ModeInverse || CurMode==ModeRewrite)
		    {
		      SDL_SetRenderDrawColor(renderer,altColor.red,altColor.green,altColor.blue,255);
		      if (ModeBold)
			{
			  SDL_RenderDrawPoint(renderer,*px+1,*py);
			  SDL_RenderDrawPoint(renderer,*px,*py+1);
			  SDL_RenderDrawPoint(renderer,*px+1,*py+1);
			  SDL_RenderPresent(renderer);
			}
		      SDL_RenderDrawPoint(renderer,*px,*py);
		      SDL_RenderPresent(renderer);
		    }
		}

	      x += deltaX;
  	      b<<=1;
  	    }

	  y+=deltaY;
	  x-=width;
	  ++p;
  	}

      Coord->x+=width;
      x+=width;
      y-=height;
    }

  return;
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  if ((theChar >= 0x20) && (theChar < 0x7F)) {
    screen_char_draw(&TTYLoc, &theChar, 1);
    TTYLoc.x += CharWide;
  }
  else if (theChar == 0x0b) /* Vertical Tab */
    {
      TTYLoc.y += CharHigh;
    }
  else if ((theChar == 0x08) && (TTYLoc.x > 7))/* backspace */
    {
      TTYLoc.x -= CharWide;
      // screen_block_draw(&scalex[TTYLoc.x],&scaley[TTYLoc.y],&scalex[TTYLoc.x+CharWide],&scaley[TTYLoc.y+CharHigh]);
    }
  else if (theChar == 0x0A)/* line feed */
    TTYLoc.y -= CharHigh;
  else if (theChar == 0x0D)/* carriage return */
    TTYLoc.x = 0;

  if (TTYLoc.x + CharWide > 511) {/* wrap at right side */
    TTYLoc.x = 0;
    TTYLoc.y -= CharHigh;
  }

  if (TTYLoc.y < 0) {
    screen_clear();
    TTYLoc.y=495;
  }
  
}

/**
 * screen_foreground - Called to set foreground color.
 */
void screen_foreground(padRGB* theColor)
{
}

/**
 * screen_background - Called to set foreground color.
 */
void screen_background(padRGB* theColor)
{
}

/**
 * screen_paint - Called to paint at location.
 */
void screen_paint(padPt* Coord)
{
}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
}
