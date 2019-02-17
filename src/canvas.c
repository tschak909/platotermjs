/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * canvas.c - Canvas functions
 */

#include <SDL2/SDL_surface.h>
#include "canvas.h"

SDL_Surface* surface;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/**
 * Canvas initialization
 */
void canvas_init(void)
{
  surface = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_RGBA32);
}

/**
 * primitive get/set pixel functions. Assume that
 * surface is locked. 
 */
Uint32 canvas_get_pixel32(int x, int y )
{
  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[ ( y * surface->w ) + x ];
}

void canvas_put_pixel32(int x, int y, Uint32 pixel )
{
  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[ ( y * surface->w ) + x ] = pixel;
}

/**
 * canvas_set_pixel(x,y,color)
 * Locks surface and plots pixel, intended to be called from screen_*
 */
void canvas_set_pixel(int x, int y, Uint32 pixel)
{
  SDL_LockSurface(surface);
  canvas_put_pixel32(x,y,pixel);
  SDL_UnlockSurface(surface);
}

/**
 * canvas_line(x1,y1,x2,y2,pixel)
 * Plot a line with pixel color from x1,y1 to x2,y2
 */
void canvas_line(int x1, int y1, int x2, int y2, Uint32 pixel)
{
  int dx, dy;
  int stepx, stepy;

  dx = x2 - x1;
  dy = y2 - y1;

  if (dx < 0)
    {
      dx = -dx;
      stepx = -1;
    }
  else
    {
      stepx = 1;
    }

  if (dy < 0)
    {
      dy = -dy;
      stepy = -1;
    }
  else
    {
      stepy = 1;
    }
  dx <<= 1;
  dy <<= 1;

  // draw first point
  canvas_put_pixel32 (x1, y1, pixel);

  // check for shallow line

  if (dx > dy)
    {
      int fraction = dy - (dx >> 1);
      while (x1 != x2)
	{
	  if (fraction >= 0)
	    {
	      y1 += stepy;
	      fraction -= dx;
	    }
	  x1 += stepx;
	  fraction += dy;
	  canvas_put_pixel32 (x1, y1, pixel);
	}
    } // otherwise steep line
  else
    {
      int fraction = dx - (dy >> 1);
      while (y1 != y2)
	{
	  if (fraction >= 0)
	    {
	      x1 += stepx;
	      fraction -= dy;
	    }
	  y1 += stepy;
	  fraction += dx;
	  canvas_put_pixel32 (x1, y1, pixel);
	}
    }
}

/**
 * canvas_clear(Uint32 pixel)
 * Clear the canvas with the requested background color.
 */
void canvas_clear(Uint32 pixel)
{
  SDL_FillRect(surface, NULL, pixel);
}

/**
 * canvas_block_fill(x1, y1, x2, y2, pixel)
 * Fill rectangular area with color
 */
void canvas_block_fill(int x1, int y1, int x2, int y2, Uint32 pixel)
{
  int _x1 = MIN(x1,x2);
  int _x2 = MAX(x1,x2);
  int _y1 = MIN(y1,y2);
  int _y2 = MAX(y1,y2);
  SDL_Rect rect = {_x1,_y1,(_x2-_x1),(_y2-_y1)};
  SDL_FillRect(surface,&rect,pixel);
}

