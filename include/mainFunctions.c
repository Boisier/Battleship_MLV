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

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   //Create the game window

    return gameObj;                                  //Return the gameObj
}

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

void printBtn(struct Button * btn, char state)
{
    MLV_Color backColor;
    MLV_Color textColor;
    
    if(state == 'h')                        //hover state
    {
        backColor = btn->hoverBackColor;
        textColor = btn->hoverTextColor;
    }
    else if(state == 'a')                   //Active state
    {
        backColor = btn->activeBackColor;
        textColor = btn->activeTextColor;
    }
    else                                    //Idle state
    {
        backColor = btn->idleBackColor;
        textColor = btn->idleTextColor;
    }

    MLV_draw_text_box(
        btn->x, btn->y, 
        btn->width, btn->height, 
        btn->text, 
        12, 
        rgba(0, 0, 0, 0), textColor, backColor,
        MLV_TEXT_CENTER,
    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

}

void mainMenu(struct GameObj * gameObj)              //display the main menu and wait for actions from the user
{
    cleanScreen(gameObj);                            //CLean screen before printing menu

    MLV_draw_text_box (0, 20, gameObj->wWidth, 40, "Battleship", 15, rgba(0, 0, 0, 0), MLV_COLOR_WHITE, rgba(0, 0, 0, 0), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    Button * playBtn = createBtn(percentOffset(50, 'w', -125), percentOffset(60, 'h', -20), 250, 40, 'c');
    strcpy(playBtn->text, "Jouer");
    playBtn->idleBackColor = rgba(255, 0, 0, 255);
    playBtn->idleTextColor = rgba(255, 255, 255, 255);
        
    printBtn(playBtn, 'i');

    MLV_actualise_window();
}