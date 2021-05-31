//=================================================================
// The header file is for module "player"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#ifndef PLAYER_PUBLIC_H
#define PLAYER_PUBLIC_H

#include "doubly_linked_list.h"

typedef struct {
    int y;                          // The y-coordinate of knife current position
    int height;
    int score;                      // Current score
    int knife_length;
    boundingBox knife_boundingBox;
    bool player_has_knife;          // The knife status: 0->In the air 1->With Player
    int lives;
    int fruitHit;
    int coinHit;
    int mysteryBoxHit;
} PLAYER;

typedef struct {
    int topLeft_x;
    int topLeft_y;
    int bottomRight_x;
    int bottomRight_y;
} knife_boundingBox;

/** getter for user to acquire info without accessing structure
 */
PLAYER player_get_info(void);

/** Initialize all values in the PLAYER struct, then draw the player
*/
void player_init(void);

/** Check if player's current location is valid, then move the player
 *  "player.height" pixels up
 */
void player_moveUp(void);

/** Check if player's current location is valid, then move the player
 *  "player.height" pixels down
 */
void player_moveDown(void);

/** Throw knife by only by changing a value in the PLAYER struct
 */
void player_throw(void);

/** Check the status of the knife in the PLAYER struct and draw the knife
 * accordingly
 */
void player_knife_draw(void);

/** Draw the player
 */
void player_draw(int color);

/** Reset knife's coordinates so that it comes back to the player's position,
 *  then redraw the knife 
 */
void player_knife_return(void);

/** Increment the score by 1
 */
void player_score_inc(void);

/** Decrement the score by 1
 */
void player_score_dec(void);

/** Clear the knife
*/
void player_knife_clear(void);

/** Adds one life to player
*/
void player_life_inc(void);

/** Subtracts one life from player
*/
void player_life_dec(void);

/** +1 fruit hit
*/
void player_fruitHit(void);

/** +1 coin hit
*/
void player_coinHit(void);

/** +1 mBox hit
*/
void player_mysteryBoxHit(void);


#endif //PLAYER_PUBLIC_H