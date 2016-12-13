#include <stdio.h>
#include <stdlib.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"


GameObj * initGame()                                 //Generate the gameObj, create the window, ...
{
    GameObj * gameObj = allocate(sizeof(GameObj));   //Define gameObj variable
    gameObj->currTurn = 0;                           //Set current turn as 0
    gameObj->wWidth = 480;                           //Set window height
    gameObj->wHeight = 320;                          //Set window width

    gameObj->nbrToPrint = 0;                         //Set number of element to print as 0;

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   //Create the game window

    return gameObj;                                  //Return the gameObj
}

void mainMenu()              //display the main menu and wait for actions from the user
{
    cleanScreen(gameObj);                            //Clean screen before printing menu

    MLV_draw_text_box (0, 20, gameObj->wWidth, 40, "Battleship", 15, rgba(0, 0, 0, 0), MLV_COLOR_WHITE, rgba(0, 0, 0, 0), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    Button * playBtn = createBtn(percentOffset(50, 'w', -125), percentOffset(60, 'h', -20), 250, 40, 'c');
    strcpy(playBtn->text, "Jouer");
    playBtn->idleBackColor = rgba(255, 0, 0, 255);
    playBtn->idleTextColor = rgba(255, 255, 255, 255);
    playBtn->hoverBackColor = rgba(0, 255, 0, 255);
        
    printElement * playBtnElement = addToPrint(playBtn, 'b');
    playBtnElement->state = 'i';

    printFrame();

    MLV_actualise_window();
}






/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type)
{
    Button * btn = allocate(sizeof(Button));
    btn->x = x;
    btn->y = y;
    btn->width = width;
    btn->height = height;
    btn->type = type;

    return btn;
}