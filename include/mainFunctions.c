#include <stdio.h>
#include <stdlib.h> 
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
    
    /*Set inputFont*/
    gameObj->inputFont = MLV_load_font("fonts/HelveticaNeue-Bold.otf", 18);
    
    /*Set default values */
    gameObj->defaultInputColor = rgba(51, 38, 29, 255);
    gameObj->defaultPlaceHolderColor = rgba(51, 44, 40, 255);

    gameObj->woodBckg =  MLV_load_image("images/woodenBackground.png"); /*Let's preload the main background for later*/

    gameObj->printLogs = false;     /*Should we display the logs?*/

    return gameObj;                 /*Return the gameObj*/
}

void mainMenu()                     /*display the main menu and wait for actions from the user*/
{
    char callback;
    Button * playBtn, * rulesBtn;
    Picture * mainTitlePicture;
    PrintElement * playBtnElement, * rulesBtnElement;

    cleanToPrint();                 /*Empty the list of element to print before doing anything*/

    /*Let's create the elements to be displayed*/
    /*Main Title*/
    mainTitlePicture = createPicture(percentOffset(50, 'w', -353), 70, "images/mainTitle.png");

    /*Play Button*/
    playBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 50, 'g');
    playBtn->idleImage = MLV_load_image("images/playBtn_idle.png");
    playBtn->hoverImage = MLV_load_image("images/playBtn_hover.png");
    playBtn->activeImage = MLV_load_image("images/playBtn_active.png");
    playBtn->callback = 'p';

    /*Rules Button*/
    rulesBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 50, 'g');
    rulesBtn->idleImage = MLV_load_image("images/rulesBtn_idle.png");
    rulesBtn->hoverImage = MLV_load_image("images/rulesBtn_hover.png");
    rulesBtn->activeImage = MLV_load_image("images/rulesBtn_active.png");
    rulesBtn->callback = 'r';

    /*Now we add them to the toPrint list*/
    addToPrint(mainTitlePicture, 'p');

    playBtnElement = addToPrint(playBtn, 'b');
    playBtnElement->state = 'i';

    rulesBtnElement = addToPrint(rulesBtn, 'b');
    rulesBtnElement->state = 'i';

    /*printFrame();*/                   
    callback = waitForAction(); 		            /*Keep application idle until a button callBack is fired. It handle mouse hovering*/ 

    /*Free created elements*/
    freeBtn(playBtn);
    freeBtn(rulesBtn);
    freePicture(mainTitlePicture);

    /*And finally call next action*/
    if(callback == 'p')
        choicePlayers();
    else if(callback == 'r')
        clicked();
}

void choicePlayers()                /*Display the number of player screen and wait for user to select a gameMode*/
{
    char callback;
    Button * onePlayerBtn, * twoPlayersBtn;
    PrintElement * onePlayerBtnElement, * twoPlayersBtnElement;

    cleanToPrint();                 /*empty current list of elements to print*/

    /*Let's create the elements to be displayed*/
    /*One player Btn*/
    onePlayerBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 50, 'g');
    onePlayerBtn->idleImage = MLV_load_image("images/onePlayerBtn_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/onePlayerBtn_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/onePlayerBtn_active.png");
    onePlayerBtn->callback = '1';

    /*Two player Btn*/
    twoPlayersBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 50, 'g');
    twoPlayersBtn->idleImage = MLV_load_image("images/twoPlayersBtn_idle.png");
    twoPlayersBtn->hoverImage = MLV_load_image("images/twoPlayersBtn_hover.png");
    twoPlayersBtn->activeImage = MLV_load_image("images/twoPlayersBtn_active.png");
    twoPlayersBtn->callback = '2';

    /*Now we add them to the toPrint list*/
    onePlayerBtnElement = addToPrint(onePlayerBtn, 'b');
    onePlayerBtnElement->state = 'i';

    twoPlayersBtnElement = addToPrint(twoPlayersBtn, 'b');
    twoPlayersBtnElement->state = 'i';

    callback = waitForAction();                /*Wait for the user to do something*/

    /*Free created elements*/
    freeBtn(onePlayerBtn);
    freeBtn(twoPlayersBtn);

    /*And finally call next action*/
    if(callback == '1')
        onePlayerInit();
    else if(callback == '2')
        twoPlayerInit();
}

void onePlayerInit()                        /*Ask the player to enter it's name*/
{
    char callback;
    TextBox * userName;
    Button * validBtn;
    PrintElement * userNameElement, * validBtnElement;

    cleanToPrint();

    userName = createTextBox(percentOffset(50, 'w', -272), percentOffset(60, 'h', 5), 252, 40, 'g', "Pseudo");
    userName->backImage = MLV_load_image("images/textField.png");
    userName->imgOffsetX = -5;

    validBtn = createBtn(percentOffset(50, 'w', 15), percent(60, 'h'), 185, 50, 'g');
    validBtn->idleImage = MLV_load_image("images/playBtn_idle.png");
    validBtn->hoverImage = MLV_load_image("images/playBtn_hover.png");
    validBtn->activeImage = MLV_load_image("images/playBtn_active.png");

    userNameElement = addToPrint(userName, 'i');
    userNameElement->state = 'b';

    validBtnElement = addToPrint(validBtn, 'b');
    validBtnElement->state = 'i';

    callback = waitForAction();
}

void twoPlayerInit()
{

}