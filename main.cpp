//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "compost_pile_public.h"
#include "fruit_public.h"
#include "player_public.h"

//For sound components
////AnalogOut DACout(p18);
//PwmOut pwmout(p26);
////PwmOut speaker(p25);

////wave_player waver(&DACout);
//SDFileSystem sd(p5, p6, p7, p8, "sd"); // mosi, miso, sck, cs

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

// ===User implementations start===
int fruit_contact(void); // iterate through fruits and see if any collided
void compost_pile_update(void);

void playSound(char * wav);
void playNotes(void);
//int gameLevel = 0; 
void set_random_seed(Timer);
//void pauseGame();


int main()
{
    uLCD.baudrate(300000);
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting\n");

    // ===User implementations start===
    // Game state variables
    
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    set_random_seed(t);
    /*
    uLCD.cls();
    int gameMode = 0;
    
    while(1){
        
      if (inputs.b1) {
        uLCD.locate(2,5);
        uLCD.printf("Easy Mode - B1 & B2");
        uLCD.locate(2,7);
        uLCD.printf("Hard Mode - B3 & B4");
        
        if (inputs.b1 && inputs.b2) {
            gameMode = 1;
            uLCD.cls();
            break;
        }
        if (inputs.b3 && inputs.b4) {
            gameMode = 2;
            uLCD.cls();
            break;
        }
      }
        
        uLCD.cls();
        break;
        //set inputs to button press
        
        //clear screen
    }
    
    */
 
    //pwmout.period(1.0/4000.0);
    //playSound("/sd/wavfiles/BUZZER.wav");//test the sound convert to thread
    //wait(0.1);
    //playNotes();
    
    //initialize functions
    compost_pile_init();
    fruit_init();
    player_init();        
    pc.printf("Initialization complete\n");
    
    while(1)
    {
        t.start();

        // Draw fruits first
        //pc.printf("fruit_generator\n");
        fruit_generator();
        
        //Put score on screen
        // NOTE: Text is 8 pixels tall
        uLCD.locate(0,0);
        uLCD.printf("Score : %d", player_get_info().score);
        //uLCD.text_string("Score : " + score, 1, 0, FONT_7X8, RED);
        
        uLCD.locate(8,1);
        uLCD.printf("Lives: %d", player_get_info().lives);
        
        //pc.printf("player_fruit_draw\n");
        player_draw(0x0000FF);
        //player_knife_draw();
        
        //pc.printf("Reading inputs\n");
        
        inputs = read_inputs();
        //pc.printf("Inputs.ay %f\n", inputs.ay);
        //pc.printf("player motions\n");
        
        if (inputs.b1) { //button off to the side 
            player_throw();         
        }  
          
        if (inputs.b3 || inputs.ay >= 0.3) {
            player_moveUp();
        }
         
        if (inputs.b4 || inputs.ay <= -0.3) {
          player_moveDown();
        } 
        
        if (inputs.b2) { //middle of three 
            player_throw();   
        } 
        
        while (inputs.b1 && inputs.b2) { //pause
           inputs = read_inputs();
           
           uLCD.cls();
           uLCD.locate(3, 3);
           uLCD.printf("Game paused");
           uLCD.locate(3, 6);
           uLCD.printf("Score : %d", player_get_info().score);
           uLCD.locate(3, 9);
           uLCD.printf("Lives: %d", player_get_info().lives);
        
           wait_ms(25);
           uLCD.cls();

            //if(inputs.b1 && inputs.b3) difficulty = 2;
            //else if (inputs.b2 && inputs.b3) difficulty = 1; 
        }
        
        player_knife_draw();
        player_knife_return();  
        
        //pc.printf("compost_pile_update\n");
        draw_compost();
        compost_pile_update();
        
        /*
        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        //is knife intersecting w fruit/bomb, return 1 if bomb
        
        if (is_bomb == 1){ //bomb hit, go to end game
            uLCD.cls(); //clear screen
            uLCD.locate(0,0);
            uLCD.text_string("BOMB HIT :(", 3, 0, FONT_7X8, RED);
            //gamesLost++;
            break;
        } //else {
            //player_score_inc();
        //}*/
        
        /* CORRECT END GAME CODE
        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        //is knife intersecting w fruit/bomb, return 1 if bomb

        if (is_bomb == 1){ //bomb hit, go to end game
            uLCD.cls(); //clear screen
            uLCD.locate(0,0);
            uLCD.text_string("BOMB HIT :(", 3, 0, FONT_7X8, RED);
            //gamesLost++;
            break;
        } //else {
            //player_score_inc();
        //}
        } */

        int is_bomb = fruit_contact();
        if (is_bomb == 1) {
            player_life_dec();
        }

        if (player_get_info().lives == 0) {
            uLCD.cls();
            uLCD.locate(0,0);
            uLCD.text_string("YOU DIED :(", 3, 0, FONT_7X8, RED);
            uLCD.locate(0,5);
            uLCD.printf("Fruits sliced: %d", player_get_info().fruitHit);
            uLCD.locate(0,6);
            uLCD.printf("Coins hit: %d", player_get_info().coinHit);
            uLCD.locate(0,7);
            uLCD.printf("Mystery boxes hit: %d", player_get_info().mysteryBoxHit);
            //gameOver = 1;
            break;
        }
       
        // TODO: Check end of the game        
        //pc.printf("check endgame\n");
        
        
        // TODO: Check if game won
        if (player_get_info().score == 3) {
            //end game
            //win screen
            uLCD.cls(); //clear screen
            uLCD.locate(5,3);
            uLCD.text_string("YOU WON!", 3, 0, FONT_7X8, RED);
            uLCD.locate(0,5);
            uLCD.printf("Fruits sliced: %d", player_get_info().fruitHit);
            uLCD.locate(0,6);
            uLCD.printf("Coins hit: %d", player_get_info().coinHit);
            uLCD.locate(0,7);
            uLCD.printf("Mystery boxes hit: %d", player_get_info().mysteryBoxHit);
            //gamesWon++;
            
            break;
        } 
        
         if (get_compost_tallest_height() > 55) { //threshold = 5 fruits
         //game over
        //uLCD.cls(); //clear screen
        //uLCD.locate(0,0);
        //uLCD.text_string("FRUIT OVERFLOW, YOU LOSE :(", 3, 0, FONT_7X8, RED);
        
        //*tetris implementation*
        //clear that compost pile
        clear_compost_col();
        //decrement score by 1
        player_score_dec();
        
        //break;
    }   
        
        // Compute update time
        t.stop();
        dt = t.read_ms();
        
        if (dt < 100) wait_ms(100 - dt);
    } //end of while
    

    //pc.printf("out of main loop\n");
    destroyList(get_fruit_list());
    
    /*
    uLCD.cls();
    
    //new game mode starts here
    compost_pile_init();
    fruit_init();
    player_init();        
    pc.printf("Initialization complete\n");
    
    while(gameMode == 2)
    {
        uLCD.baudrate(300000);
        t.start();

        // Draw fruits first
        //pc.printf("fruit_generator\n");
        fruit_generator();
        
        //Put score on screen
        // NOTE: Text is 8 pixels tall
        uLCD.locate(0,0);
        uLCD.printf("Score : %d", player_get_info().score);
        //uLCD.text_string("Score : " + score, 1, 0, FONT_7X8, RED);
        
        uLCD.locate(8,1);
        uLCD.printf("Lives: %d", player_get_info().lives);
        
        //pc.printf("player_fruit_draw\n");
        player_draw(0x0000FF);
        //player_knife_draw();
        
        //pc.printf("Reading inputs\n");
        
        inputs = read_inputs();
        //pc.printf("Inputs.ay %f\n", inputs.ay);
        //pc.printf("player motions\n");
        
        if (inputs.b1) { //button off to the side 
            player_throw();         
        }  
          
        if (inputs.b3 || inputs.ay >= 0.3) {
            player_moveUp();
        }
         
        if (inputs.b4 || inputs.ay <= -0.3) {
          player_moveDown();
        } 
        
        if (inputs.b2) { //middle of three 
            player_throw();   
        } 
        
        while (inputs.b1 && inputs.b2) { //pause
           inputs = read_inputs();
           
           uLCD.cls();
           uLCD.locate(3, 3);
           uLCD.printf("Game paused");
           uLCD.locate(3, 6);
           uLCD.printf("Score : %d", player_get_info().score);
           uLCD.locate(3, 9);
           uLCD.printf("Lives: %d", player_get_info().lives);
        
           wait_ms(25);
           uLCD.cls();

            //if(inputs.b1 && inputs.b3) difficulty = 2;
            //else if (inputs.b2 && inputs.b3) difficulty = 1; 
        }
        
        player_knife_draw();
        player_knife_return();  
        
        //pc.printf("compost_pile_update\n");
        draw_compost();
        compost_pile_update();
        
        /*
        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        //is knife intersecting w fruit/bomb, return 1 if bomb
        
        if (is_bomb == 1){ //bomb hit, go to end game
            uLCD.cls(); //clear screen
            uLCD.locate(0,0);
            uLCD.text_string("BOMB HIT :(", 3, 0, FONT_7X8, RED);
            //gamesLost++;
            break;
        } //else {
            //player_score_inc();
        //}*/
        
        /* CORRECT END GAME CODE
        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        //is knife intersecting w fruit/bomb, return 1 if bomb

        if (is_bomb == 1){ //bomb hit, go to end game
            uLCD.cls(); //clear screen
            uLCD.locate(0,0);
            uLCD.text_string("BOMB HIT :(", 3, 0, FONT_7X8, RED);
            //gamesLost++;
            break;
        } //else {
            //player_score_inc();
        //}
        } 

        int is_bomb = fruit_contact();
        if (is_bomb == 1) {
            player_life_dec();
        }

        if (player_get_info().lives == 0) {
            uLCD.cls();
            uLCD.locate(0,0);
            uLCD.text_string("YOU DIED :(", 3, 0, FONT_7X8, RED);
            //gameOver = 1;
            break;
        }
       
        // TODO: Check end of the game        
        //pc.printf("check endgame\n");
        
        
        // TODO: Check if game won
        if (player_get_info().score == 5) {
            //end game
            //win screen
            uLCD.cls(); //clear screen
            uLCD.locate(3,3);
            uLCD.text_string("YOU WON!", 3, 0, FONT_7X8, RED);
            uLCD.locate(3,5);
            uLCD.printf("Fruits sliced: %d", player_get_info().fruitHit);
            uLCD.locate(3,6);
            uLCD.printf("Coins hit: %d", player_get_info().coinHit);
            uLCD.locate(3,7);
            uLCD.printf("Mystery boxes hit: %d", player_get_info().mysteryBoxHit);
            //gamesWon++;
            
            break;
        } 
        
         if (get_compost_tallest_height() > 55) { //threshold = 5 fruits
         //game over
        //uLCD.cls(); //clear screen
        //uLCD.locate(0,0);
        //uLCD.text_string("FRUIT OVERFLOW, YOU LOSE :(", 3, 0, FONT_7X8, RED);
        
        //*tetris implementation*
        //clear that compost pile
        clear_compost_col();
        //decrement score by 1
        player_score_dec();
        
        break;
    }   
        
        // Compute update time
        t.stop();
        dt = t.read_ms();
        
        if (dt < 100) wait_ms(100 - dt);
    } //end of while
    

    //pc.printf("out of main loop\n");
    destroyList(get_fruit_list()); */
    
    return 0;
}
// ===User implementations end===   

// ===User implementations start===

/* This function iterate through the fruit list, checking if anyone one of them is contacting 
*  with the player's knife. Don't forget to check if the "fruit" is the bomb, since we 
*  generated bombs using the fruit_generator. 
*/ 


int fruit_contact(void) {
    DLinkedList* fruitList = get_fruit_list();
    LLNode* fruitHead = fruitList->head; 
    bool overlapping;
    
    while(fruitHead != NULL) {
        pc.printf("enter fruit_contact while loop \n");
        FRUIT* fruit =  (FRUIT*) fruitHead->data; 
        
       overlapping = !(player_get_info().knife_boundingBox.topLeft.x >= fruit->box.bottomRight.x
         || fruit->box.topLeft.x >= player_get_info().knife_boundingBox.bottomRight.x) &&  
        !(player_get_info().knife_boundingBox.topLeft.y >= fruit->box.bottomRight.y 
        || fruit->box.topLeft.y >= player_get_info().knife_boundingBox.bottomRight.y); 
        
        if (overlapping && player_get_info().player_has_knife == 0) {
            pc.printf("Fruit is overlapping \n");
            if (fruit->type == 0){ //is a bomb
                return 1;
            } else if (fruit->type == 5) { //is a coin
                clear_compost_col();
                player_coinHit();
            } else if (fruit->type == 6) { //is mysteryBox
                //add life functionality
                player_life_dec();
                player_fruitHit();
            } else { //fruit is being sliced
                player_score_inc();
                fruit->status = FRUIT_SLICED;
                player_knife_return();
                player_mysteryBoxHit();
            }
            //fruitHead = fruitHead->next;  //inside while
        }
        fruitHead = fruitHead->next;
    }
    return 0;
}



/** Call compost_pile_update() repeatedly in your game-loop. ex: main()
    This function iterate through the fruit list. Add fruits that reach the bottom of the screen
    to the compost pile.
    @return  Number of remaining cities. You might end the game when all cities are demolished.
*/

void compost_pile_update(void){
    DLinkedList* fruitList = get_fruit_list();
    LLNode* fruitHead = fruitList->head;
   
    
    while (fruitHead != NULL) {
        FRUIT* fruit =  (FRUIT*) fruitHead->data; 
        
        int fruitCol = (int)(fruit->box.bottomRight.x / compost_get_info(0).width); 
        int fruitHeight = get_compost_height(fruitCol);
        
        if (fruit->box.bottomRight.y >= REVERSE_Y(get_compost_height(fruitCol))){           
        
                //fruitHeight.box.topLeft.y)) {
                //fruit->status = FRUIT_SLICED;
                
                draw_nothing(fruit->box);
                deleteNode(fruitList, fruitHead);
                compost_add(fruitCol);
    }
    
        //*tetris implementation*
        //if (get_compost_tallest_height() > 55) {}
        
        
    fruitHead = fruitHead->next;
  }      
}


//fcn to play a wav
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
        return;
}

/* Wanna hear some annoying sounds?*/
void playNotes(void)
{
    int i;
// generate a 500Hz tone using PWM hardware output
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(3);
    speaker=0.0; // turn off audio
    wait(2);
// generate a short 150Hz tone using PWM hardware output
// something like this can be used for a button click effect for feedback
    for (i=0; i<10; i++) {
        speaker.period(1.0/150.0); // 500hz period
        speaker =0.25; //25% duty cycle - mid range volume
        wait(.02);
        speaker=0.0; // turn off audio
        wait(0.5);
    }

// sweep up in frequency by changing the PWM period
    for (i=0; i<8000; i=i+100) {
        speaker.period(1.0/float(i));
        speaker=0.25;
        wait(.1);
    }
    wait(2);

// two tone police siren effect -  two periods or two frequencies
// increase volume - by changing the PWM duty cycle
    for (i=0; i<26; i=i+2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    // decrease volume
    for (i=25; i>=0; i=i-2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    speaker =0.0;
    wait(2);
}

void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();
    //uLCD.printf("Welcome to Fruit Ninja!\n");
    uLCD.locate(2, 2);
    //uLCD.printf("Press any button to start.");
    uLCD.printf("WELCOME TO\n");
    uLCD.locate(1,4);
    uLCD.printf("FRUIT NINJA!");
    uLCD.locate(2,6);
    uLCD.printf("Slice to win!");
    
    /*
    uLCD.locate(5,2); 
    uLCD.printf("Games Won: %d", gamesWon);
    uLCD.locate(6,2);
    uLCD.printf("Games Lost: %d", gamesLost);*/
    
    //int gameLevel = 0;
    
    while(1){
      inputs = read_inputs();
      if (inputs.b1 || inputs.b2 || inputs.b3 || inputs.b4) break;
      //uLCD.cls();
    }
      
    uLCD.cls();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
    }

// ===User implementations end===
