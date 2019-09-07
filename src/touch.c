/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * touch.c - Touchscreen functions
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "touch.h"
#include "protocol.h"

extern int something_happened;
extern SDL_Event event;

/**
 * touch_init() - Set up touch screen
 */
void touch_init(void)
{
  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0,&mode);
  printf("X: %d Y: %d \n",mode.w,mode.h);
}

/**
 * touch_main() - Main loop for touch screen
 */
void touch_main(void)
{  
  if (something_happened==0)
    return;
  
  if (event.type==SDL_MOUSEBUTTONUP)
    {
      padPt pt={event.button.x,((event.button.y^0x1FF)&0x1FF)};
      Touch(&pt);
    }
  else if (event.type==SDL_FINGERUP)
    {
      SDL_DisplayMode mode;
      padPt pt;

      SDL_GetCurrentDisplayMode(0,&mode);
      pt.x=ceil(event.tfinger.x*mode.w);
      pt.y=ceil(event.tfinger.y*mode.h);
      Touch(&pt);      
    }
}

/**
 * touch_allow - Set whether touchpanel is active or not.
 */
void touch_allow(padBool allow)
{
}

/**
 * handle_mouse - Process mouse events and turn into scaled touch events
 */
void handle_mouse(void)
{
}

/**
 * touch_hide() - hide the mouse cursor
 */
void touch_hide(void)
{
}

/**
 * touch_done() - Stop the mouse driver
 */
void touch_done(void)
{
}

