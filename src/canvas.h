/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * canvas.h - Canvas functions
 */

#ifndef CANVAS_H
#define CANVAS_H

/**
 * Canvas initialization
 */
void canvas_init(void);

/**
 * canvas_set_pixel(x,y,color)
 * Locks surface and plots pixel, intended to be called from screen_*
 */
void canvas_set_pixel(int x, int y, Uint32 pixel);

/**
 * _canvas_set_pixel(x,y,color)
 * Low level set pixel on surface. Assumes surface is locked.
 */
void _canvas_set_pixel(int x, int y, Uint32 pixel);

/**
 * primitive get/set pixel functions. Assume that
 * surface is locked. 
 */
Uint32 canvas_get_pixel32(int x, int y );

/**
 * canvas_clear(Uint32 pixel)
 * Clear the canvas with the requested background color.
 */
void canvas_clear(Uint32 pixel);

/**
 * canvas_line(x1,y1,x2,y2,pixel)
 * Plot a line with pixel color from x1,y1 to x2,y2
 */
void canvas_line(int x1, int y1, int x2, int y2, Uint32 pixel);

/**
 * canvas_block_fill(x1, y1, x2, y2, pixel)
 * Fill rectangular area with color
 */
void canvas_block_fill(int x1, int y1, int x2, int y2, Uint32 pixel);


#endif /* CANVAS_H */
