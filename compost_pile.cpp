//=================================================================
// The file is for module "compost pile"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

#include "compost_pile_private.h"

COMPOST compost_record[NUM_PILE];
int tallest_pile_height;


// See the comments in compost_pile_public.h
void compost_pile_init() {
    
    int i, x = 0;
    for(i = 0; i < 11; i++) { //max 11 compost piles
        COMPOST c;
        //update x every time
        c.y = 127;
        c.height = 10;
        c.width = PILE_WIDTH; // < 128/11
        c.x = x;
        x = x + 11; //updating width for next one
        
        compost_record[i] = c;
    }
    
    tallest_pile_height = 0;
}

COMPOST compost_get_info(int index){

    //if(compost_record[index] < 11) {
        return compost_record[index];
    //} else return;
}

void compost_add(int index) {    
    compost_record[index].height +=  11; // fruit size = 11
    
    if (tallest_pile_height < compost_record[index].height) {
        tallest_pile_height = compost_record[index].height;
    }
    
    COMPOST c = compost_record[index];
    
    uLCD.filled_rectangle(c.x, c.y - compost_record[index].height, 
         c.x + c.width, c.y, GREEN);
}

void draw_compost(void){
    int i;
    for (i=0; i < 11; i++) {
        COMPOST c = compost_record[i];
        uLCD.filled_rectangle(c.x, c.y - compost_record[i].height, 
         c.x + c.width, c.y, GREEN);
    }
}

void clear_compost_col() {
    int i, tallestCol; 
    COMPOST c;
    
    for (i=0; i < 11; i++){
        c = compost_record[i];
        
        if (c.height == get_compost_tallest_height()) {
            tallestCol = c.height;
            break;
        }
    }       
    compost_record[i].height = 0;
    
    uLCD.filled_rectangle(c.x, c.y - tallestCol, 
       c.x + c.width, c.y, BACKGROUND_COLOR);
}

int get_compost_tallest_height() {
    return tallest_pile_height;
}

int get_compost_height(int index) {
    return compost_record[index].height;
}