#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "globals.h"
 
// TODO: Determine X and Y Ranges
#define SIZE_X 127
#define SIZE_Y 127

// The bottom of the screen => y=127
// lets the compost piles grow up from the bottom of the screen. It is awkward.
// Thus, we use a macro to reverse the coordinate for convenience.
#define REVERSE_Y(x) (SIZE_Y-(x))

/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int key);
 
/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions.
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(boundingBox b);
void draw_bomb(boundingBox b);
void draw_banana(boundingBox b);
void draw_starfruit(boundingBox b);
void draw_coconut(boundingBox b);
void draw_mango(boundingBox b);
void draw_coin(boundingBox b);
void draw_mysteryBox(boundingBox b);
 
#endif // GRAPHICS_H
