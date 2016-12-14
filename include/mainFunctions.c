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
    playBtn->callback = &choicePlayers;

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



void choicePlayers()
{
    cleanScreen(gameObj);                            //Clean screen before printing menu

    Button * onePlayerBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    onePlayerBtn->idleImage = MLV_load_image("images/onePlayerBtn_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/onePlayerBtn_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/onePlayerBtn_active.png");
    onePlayerBtn->callback = &clicked;

    printElement * onePlayerBtnElement = addToPrint(onePlayerBtn, 'b');
    onePlayerBtnElement->state = 'i';

    Button * twoPlayersBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 40, 'g');
    twoPlayersBtn->idleImage = MLV_load_image("images/twoPlayersBtn_idle.png");
    twoPlayersBtn->hoverImage = MLV_load_image("images/twoPlayersBtn_hover.png");
    twoPlayersBtn->activeImage = MLV_load_image("images/twoPlayersBtn_active.png");
    twoPlayersBtn->callback = &clicked;

    printElement * twoPlayersBtnElement = addToPrint(twoPlayersBtn, 'b');
    twoPlayersBtnElement->state = 'i';

    printFrame();
    waitForAction();
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
    int x = Btn->x;                     //Get X position of the button
    int y = Btn->y;                     //Get Y position of of the button
    int width = Btn->width;             //Get width of the button
    int height = Btn->height;           //Get height of the button

    if(mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    else
        return false;
}









/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type)  //Create a Btn and assign specified values
{
    Button * btn = allocate(sizeof(Button));    //Create an empty button
    btn->x = x;                                 //Set X position of the button
    btn->y = y;                                 //Set Y position of the button
    btn->width = width;                         //Set width of the button
    btn->height = height;                       //Set height of the button
    btn->type = type;                           //Set type of the button
    btn->callback = NULL;                       //Set callback as NULL 

    if(type == 'g')                             //If the button is a graphic one
    {
        btn->idleImage = NULL;                  //Set images as default  
        btn->hoverImage = NULL;
        btn->activeImage = NULL;
    }
    else                                        //Otherwise, treat as a plain color button
    {
        btn->idleBackColor = MLV_COLOR_BLACK;   //Set default background color
        btn->hoverBackColor = MLV_COLOR_BLACK;
        btn->activeBackColor = MLV_COLOR_BLACK;
        
        btn->idleTextColor = MLV_COLOR_WHITE;   //Set default text color
        btn->hoverTextColor = MLV_COLOR_WHITE;
        btn->activeTextColor = MLV_COLOR_WHITE;
    }

    return btn;
}

Image * createImage(int x, int y, int width, int height, char fileURL[])    //Create an Image element and return it
{
    Image * img = allocate(sizeof(Image));                      //create the element
    img->x = x;                                                 //Set X position
    img->y = y;                                                 //Set Y position
    img->image = MLV_load_image(fileURL);                       //Load image
    MLV_get_image_size(img->image, &img->width, &img->height);  //Get image height and width;

    return img;                                                 //Return the newly created element
}