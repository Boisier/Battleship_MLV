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
    gameObj->inputFont = NULL;      /*Set inputFont as null*/

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   /*Create the game window*/

    return gameObj;                 /*Return the gameObj*/
}

void mainMenu()                     /*display the main menu and wait for actions from the user*/
{
    Button * playBtn, * rulesBtn;
    Picture * mainTitlePicture;
    PrintElement * playBtnElement, * rulesBtnElement;

    cleanToPrint();                 /*Empty the list of element to print before doing anything*/

    /*Let's create the elements to be displayed*/
    /*Main Title*/
    mainTitlePicture = createPicture(percentOffset(50, 'w', -353), 70, "images/mainTitle.png");

    /*Play Button*/
    playBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    playBtn->idleImage = MLV_load_image("images/playBtn_idle.png");
    playBtn->hoverImage = MLV_load_image("images/playBtn_hover.png");
    playBtn->activeImage = MLV_load_image("images/playBtn_active.png");
    playBtn->callback = &choicePlayers;

    /*Rules Button*/
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

    /*printFrame();*/                   /*And now we print the frame*/
    waitForAction(); 		        /*Keep application idle until a button callBack is fired. It handle mouse hovering*/ 

    /*Free created elements*/
    free(playBtn);
    free(rulesBtn);
    free(mainTitlePicture);
}

void choicePlayers()                /*Display the number of player screen and wait for user to select a gameMode*/
{
    Button * onePlayerBtn, * twoPlayersBtn;
    PrintElement * onePlayerBtnElement, * twoPlayersBtnElement;

    cleanToPrint();                 /*empty current list of elements to print*/

    /*Let's create the elements to be displayed*/
    /*One player Btn*/
    onePlayerBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 40, 'g');
    onePlayerBtn->idleImage = MLV_load_image("images/onePlayerBtn_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/onePlayerBtn_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/onePlayerBtn_active.png");
    onePlayerBtn->callback = &onePlayerInit;

    /*Two player Btn*/
    twoPlayersBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 40, 'g');
    twoPlayersBtn->idleImage = MLV_load_image("images/twoPlayersBtn_idle.png");
    twoPlayersBtn->hoverImage = MLV_load_image("images/twoPlayersBtn_hover.png");
    twoPlayersBtn->activeImage = MLV_load_image("images/twoPlayersBtn_active.png");
    twoPlayersBtn->callback = &twoPlayerInit;

    /*Now we add them to the toPrint list*/
    onePlayerBtnElement = addToPrint(onePlayerBtn, 'b');
    onePlayerBtnElement->state = 'i';

    twoPlayersBtnElement = addToPrint(twoPlayersBtn, 'b');
    twoPlayersBtnElement->state = 'i';

    waitForAction();                /*Wait for user to do something*/

    /*Free created elements*/
    free(onePlayerBtn);
    free(twoPlayersBtn);
}

void onePlayerInit()
{
    TextBox * userName;
    PrintElement * userNameElement;

    cleanToPrint();

    userName = createTextBox(percentOffset(50, 'w', -195), percent(60, 'h'), 180, 40, 'g', "Pseudo...");
    userName->backImage = MLV_load_image("images/textField.png");
    userName->imgOffsetX = -10;

    userNameElement = addToPrint(userName, 'i');
    userNameElement->state = 'i';
    waitForAction();
}

void twoPlayerInit()
{

}