//=================================================================
// Implementation for the player module
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#include "player_private.h"

PLAYER player; // structure of player
//knife_boundingBox kbox; 
boundingBox box;

PLAYER player_get_info(void){
    return player;
}

void player_init(void) {   
    player.y = 0;
    player.height = 10; //size of the player
    player.score = 0;
    player.knife_length = 5;
    //boundingBox
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.y = player.y + 2;
    player.knife_boundingBox.topLeft.x = 6;
    player.knife_boundingBox.bottomRight.x = player.knife_length + 6;
    player.player_has_knife = 1;
    player.lives = 2;
    player.fruitHit = 0;
    player.coinHit = 0;
    player.mysteryBoxHit = 0;
}

void player_moveUp(void) { 
    //pc.printf("mu_PlayerY. %d, /n", player.y);
    if(player.y >= 10 && player.y < 127 - get_compost_tallest_height()) {
        //erase player's current place
        player_draw(BACKGROUND_COLOR);
        player_knife_clear();
        player_knife_return();
        player.y -= player.height;
        //pc.printf("Player is erased. %d, /n", player.y);
        //redraw the player w color
        player_draw(PLAYER_COLOR);
        player_knife_draw();
        
        
        //do the same thing for the knife
    }
}

void player_moveDown(void) { 
    //pc.printf("md_PlayerY. %d, /n", player.y);
    if(player.y >= 0 && player.y < 127 - get_compost_tallest_height() - 10) {
        player_draw(BACKGROUND_COLOR);
        player_knife_clear();
        player_knife_return();
        player.y += player.height;
        //pc.printf("Player is erased. %d, \n", player.y);
        player_draw(PLAYER_COLOR);
        player_knife_draw();
    }
}

void player_throw(void) { 
    
    player.player_has_knife = 0; //knife in air 
    //draw_nothing(box);  //clear the current knife
}

void player_knife_return(void) {
    
    if (player.knife_boundingBox.topLeft.x >= 127) {
    player.player_has_knife = 1;
    //draw_nothing(box); //erase prev version of knife
    
    //uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, 
    //player.knife_boundingBox.topLeft.y, player.knife_boundingBox.bottomRight.x, 
    //player.knife_boundingBox.bottomRight.y, BLUE); 
    
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.y = player.y + 2;
    player.knife_boundingBox.topLeft.x = 6;
    player.knife_boundingBox.bottomRight.x = player.knife_length + 6;
    
    player_knife_draw();
    }
    
    else {
        //move to the player 
        //if the player has the knife
        
        if(player.player_has_knife == 1) {
        player.knife_boundingBox.topLeft.y = player.y;
        player.knife_boundingBox.bottomRight.y = player.y + 2;
        player.knife_boundingBox.topLeft.x = 6;
        player.knife_boundingBox.bottomRight.x = player.knife_length + 6;
        }
    }
    
}

void player_knife_draw(void) {
    //check the status of the knife and draw the knife accordingly
    
    if (player.player_has_knife) { 
        //player has the knife
        uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.topLeft.y, 
        player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y, RED); 
    }
    
    if (!player.player_has_knife) {
        //knife is in the air
        
        //while (player.knife_boundingBox.bottomRight.x <= 128) {
        //draw_nothing(box);
        
        uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.topLeft.y,
        player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y, BACKGROUND_COLOR);
        
        //draw knife moving over by some pixels until end of screen
        player.knife_boundingBox.topLeft.x += 20; //update the location of knife
        player.knife_boundingBox.bottomRight.x += 20;
    
        uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, 
        player.knife_boundingBox.topLeft.y, player.knife_boundingBox.bottomRight.x, 
        player.knife_boundingBox.bottomRight.y, RED); 
    
        //player.knife_length = 5;  
    }
    //player_knife_return();
}

void player_knife_clear() {
    uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.topLeft.y,
        player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.bottomRight.y, BACKGROUND_COLOR);
}


// ==== player_private.h implementation ====
void player_draw(int color) {
    uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, color); 
}

void player_score_inc(void) {
    player.score += 1;
}

void player_score_dec(void) {
    player.score -= 1;
}

void player_life_inc(void) {
    if (player.lives < 3) player.lives += 1;
}

void player_life_dec(void) {
    player.lives -= 1;
}

void player_fruitHit(void) {
    player.fruitHit++;
}

void player_coinHit(void) {
    player.coinHit++;
}

void player_mysteryBoxHit(void) {
    player.mysteryBoxHit++;
}