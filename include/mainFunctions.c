#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"


GameObj * initGame()                                 //Generate the gameObj, create the window, ...
{
    GameObj * gameObj = allocate(sizeof(GameObj));   //Define gameObj variable
    gameObj->currTurn = 0;                           //Set current turn as 0
    gameObj->wWidth = 1100;                           //Set window height
    gameObj->wHeight = 800;                          //Set window width

    gameObj->nbrToPrint = 0;                         //Set number of element to print as 0;

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   //Create the game window

    return gameObj;                                  //Return the gameObj
}

void clicked()
{
    printf("Button clicked\n");
}

void mainMenu()              //display the main menu and wait for actions from the user
{
    cleanScreen(gameObj);                            //Clean screen before printing menu

    MLV_draw_text_box (0, 20, gameObj->wWidth, 40, "Battleship", 15, rgba(0, 0, 0, 0), MLV_COLOR_WHITE, rgba(0, 0, 0, 0), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    Button * playBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    playBtn->idleImage = MLV_load_image("images/playBtn_idle.png");
    playBtn->hoverImage = MLV_load_image("images/playBtn_hover.png");
    playBtn->activeImage = MLV_load_image("images/playBtn_active.png");
    playBtn->callback = &clicked;

    printElement * playBtnElement = addToPrint(playBtn, 'b');
    playBtnElement->state = 'i';

    Button * rulesBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 40, 'g');
    rulesBtn->idleImage = MLV_load_image("images/rulesBtn_idle.png");
    rulesBtn->hoverImage = MLV_load_image("images/rulesBtn_hover.png");
    rulesBtn->activeImage = MLV_load_image("images/rulesBtn_active.png");
    rulesBtn->callback = &clicked;

    printElement * rulesBtnElement = addToPrint(rulesBtn, 'b');
    rulesBtnElement->state = 'i';

    printFrame();
    waitForAction(); 		//Keep application idle until a button callBack is fired. It handle mouse hovering 
}





void waitForAction() 		//Keep application idle until a button callBack is fired. It handle mouse hovering 
{
    //bool btnPressed = false;
    int mouseX, mouseY, i;
    MLV_Event event;
    void (*callbackFunction)() = NULL;

    do                                                          //Loop until the user press a btn
    {
        event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mouseX, &mouseY, NULL, NULL);    //Get last event

        if( event == MLV_MOUSE_MOTION )                         //Is this a movement of the mouse?
        {
            for(i = 0; i < gameObj->nbrToPrint; i++)            //iterate through all the element to print
            {
                if(gameObj->toPrint[i].type == 'b')             //is this a button ?
                {
                    if(isCursorOnBtn(((Button *)gameObj->toPrint[i].element), mouseX, mouseY))  //Is the cursoron this button?
                        gameObj->toPrint[i].state = 'h';        //yes, set state as hover
                    else
                        gameObj->toPrint[i].state = 'i';        //no, make sure state is idle
                }
            }
        }
        else if(event == MLV_MOUSE_BUTTON)                      //Is this a click of the mouse ?
        {
            for(i = 0; i < gameObj->nbrToPrint; i++)            //iterate through all the element to print
            {
                if(gameObj->toPrint[i].type == 'b')             //Is this a button ?
                {
                    if(isCursorOnBtn(((Button *)gameObj->toPrint[i].element), mouseX, mouseY)) //is the cursor on the Btn?
                        if(((Button *)gameObj->toPrint[i].element)->callback != NULL)   //Is the callback function defined ?
                        {
                            gameObj->toPrint[i].state = 'a';
                            callbackFunction = ((Button *)gameObj->toPrint[i].element)->callback;    //Yes, set the callback and stop the loop
                        }
                }
            }
        }

        printFrame();                                           //Update window

    } while(callbackFunction == NULL);

    callbackFunction();
}

bool isCursorOnBtn(Button * Btn, int mouseX, int mouseY)                  //check if cursor is on Button. Return true if it is, false otherwise
{
    int x = Btn->x;
    int y = Btn->y;
    int width = Btn->width;
    int height = Btn->height;

    if(mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    else
        return false;
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
    btn->callback = NULL;

    if(type == 'g')
    {
        btn->idleBackColor = rgba(0, 0, 0, 0);
        btn->hoverBackColor = rgba(0, 0, 0, 0);
        btn->activeBackColor = rgba(0, 0, 0, 0);
    }
    else
    {
        btn->idleBackColor = MLV_COLOR_BLACK;
        btn->hoverBackColor = MLV_COLOR_BLACK;
        btn->activeBackColor = MLV_COLOR_BLACK;
    }

    btn->idleTextColor = MLV_COLOR_WHITE;
    btn->hoverTextColor = MLV_COLOR_WHITE;
    btn->activeTextColor = MLV_COLOR_WHITE;

    btn->idleImage = NULL;
    btn->hoverImage = NULL;
    btn->activeImage = NULL;

    return btn;
}