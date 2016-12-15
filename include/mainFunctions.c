#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"


GameObj * initGame()                /*Generate the gameObj, create the window, ...*/
{
    GameObj * gameObj = allocate(sizeof(GameObj));   /*Define gameObj variable*/
    gameObj->currTurn = 0;          /*Set current turn as 0*/
    gameObj->wWidth = 1100;         /*Set window height*/
    gameObj->wHeight = 800;         /*Set window width*/

    gameObj->nbrToPrint = 0;        /*Set number of element to print as 0;*/

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   /*Create the game window*/

    return gameObj;                 /*Return the gameObj*/
}

void mainMenu()                     /*display the main menu and wait for actions from the user*/
{
    Button * playBtn, * rulesBtn;
    Picture * mainTitlePicture;
    printElement * playBtnElement, * rulesBtnElement;

    cleanToPrint();                 /*Empty the list of element to print before doing anything*/

    /*Let's create the elements to be displayed*/
    mainTitlePicture = createPicture(percentOffset(50, 'w', -353), 70, "images/mainTitle.png");

    playBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    playBtn->idleImage = MLV_load_image("images/playBtn_idle.png");
    playBtn->hoverImage = MLV_load_image("images/playBtn_hover.png");
    playBtn->activeImage = MLV_load_image("images/playBtn_active.png");
    playBtn->callback = &choicePlayers;

    rulesBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 40, 'g');
    rulesBtn->idleImage = MLV_load_image("images/rulesBtn_idle.png");
    rulesBtn->hoverImage = MLV_load_image("images/rulesBtn_hover.png");
    rulesBtn->activeImage = MLV_load_image("images/rulesBtn_active.png");
    rulesBtn->callback = &clicked;

    /*Now we add them to the toPrint list*/
    addToPrint(mainTitlePicture, 'p');

    playBtnElement = addToPrint(playBtn, 'b');
    playBtnElement->state = 'i';

    rulesBtnElement = addToPrint(rulesBtn, 'b');
    rulesBtnElement->state = 'i';

    
    printFrame();                   /*And now we print the frame*/
    waitForAction(); 		        /*Keep application idle until a button callBack is fired. It handle mouse hovering */

    free(playBtn);
    free(rulesBtn);
    free(mainTitlePicture);
}

void choicePlayers()                /*Display the number of player screen and wait for user to select a gameMode*/
{
    Button * onePlayerBtn, * twoPlayersBtn;
    printElement * onePlayerBtnElement, * twoPlayersBtnElement;

    cleanToPrint();             /*empty current list of elements to print*/
    /*One player Btn*/
    onePlayerBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    onePlayerBtn->idleImage = MLV_load_image("images/onePlayerBtn_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/onePlayerBtn_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/onePlayerBtn_active.png");
    onePlayerBtn->callback = &onePlayerInit;

    onePlayerBtnElement = addToPrint(onePlayerBtn, 'b');
    onePlayerBtnElement->state = 'i';

    /*Two player Btn*/
    twoPlayersBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 40, 'g');
    twoPlayersBtn->idleImage = MLV_load_image("images/twoPlayersBtn_idle.png");
    twoPlayersBtn->hoverImage = MLV_load_image("images/twoPlayersBtn_hover.png");
    twoPlayersBtn->activeImage = MLV_load_image("images/twoPlayersBtn_active.png");
    twoPlayersBtn->callback = &twoPlayerInit;

    twoPlayersBtnElement = addToPrint(twoPlayersBtn, 'b');
    twoPlayersBtnElement->state = 'i';

    printFrame();           /*Display frame*/
    waitForAction();        /*Wait for user to do something*/

    free(onePlayerBtn);
    free(twoPlayersBtn);
}

void onePlayerInit()
{

}

void twoPlayerInit()
{

}









/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type)  /*Create a Btn and assign specified values*/
{
    Button * btn = allocate(sizeof(Button));    /*Create an empty button*/
    btn->x = x;                                 /*Set X position of the button*/
    btn->y = y;                                 /*Set Y position of the button*/
    btn->width = width;                         /*Set width of the button*/
    btn->height = height;                       /*Set height of the button*/
    btn->type = type;                           /*Set type of the button*/
    btn->callback = NULL;                       /*Set callback as NULL */

    if(type == 'g')                             /*If the button is a graphic one*/
    {
        btn->idleImage = NULL;                  /*Set images as default  */
        btn->hoverImage = NULL;
        btn->activeImage = NULL;
    }
    else                                        /*Otherwise, treat as a plain color button*/
    {
        btn->idleBackColor = MLV_COLOR_BLACK;   /*Set default background color*/
        btn->hoverBackColor = MLV_COLOR_BLACK;
        btn->activeBackColor = MLV_COLOR_BLACK;
        
        btn->idleTextColor = MLV_COLOR_WHITE;   /*Set default text color*/
        btn->hoverTextColor = MLV_COLOR_WHITE;
        btn->activeTextColor = MLV_COLOR_WHITE;
    }

    return btn;
}

Picture * createPicture(int x, int y, char * fileURL)    /*Create an Image element and return it*/
{
    Picture * img = allocate(sizeof(Picture));                  /*create the element*/
    img->x = x;                                                 /*Set X position*/
    img->y = y;                                                 /*Set Y position*/
    img->image = MLV_load_image(fileURL);                       /*Load image*/
    MLV_get_image_size(img->image, &img->width, &img->height);  /*Get image height and width*/

    return img;                                                 /*Return the newly created element*/
}