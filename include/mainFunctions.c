#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"


GameObj * initGame()                /*Generate the gameObj, create the window, ...*/
{
    GameObj * gameObj = allocate(sizeof(GameObj));   /*Define gameObj variable*/

    gameObj->currTurn = 0;          /*Set current turn as 0*/

    gameObj->nbrShips[1] = 0;       /*Set nbr of sheep for every size*/
    gameObj->nbrShips[2] = 1;
    gameObj->nbrShips[3] = 2;
    gameObj->nbrShips[4] = 1;
    gameObj->nbrShips[5] = 1;

    gameObj->wWidth = 1100;         /*Set window height*/
    gameObj->wHeight = 800;         /*Set window width*/

    gameObj->nbrToPrint = 0;        /*Set number of element to print as 0;*/

    MLV_create_window("Battleship", "Battleship", gameObj->wWidth, gameObj->wHeight);   /*Create the game window*/  
    
    /*Set default fonts*/
    gameObj->inputFont = MLV_load_font("fonts/LCD_Solid.ttf", 18);
    
    /*Set default values */
    gameObj->defaultInputColor = rgba(51, 38, 29, 255);
    gameObj->defaultPlaceHolderColor = rgba(70, 60, 60, 255);

    gameObj->woodBckg =  MLV_load_image("images/woodenBackground.png"); /*Let's preload the main background for later*/

    gameObj->gameState = 'm';

    gameObj->printLogs = false;     /*Should we display the logs?*/

    return gameObj;                 /*Return the gameObj*/
}

void mainMenu()                     /*display the main menu and wait for actions from the user*/
{
    char callback;
    Button * playBtn, * rulesBtn, * quitBtn;
    Picture * mainTitlePicture;
    PrintElement * playBtnElement, * rulesBtnElement, * quitBtnElement;

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

    quitBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, 'g');
    quitBtn->idleImage = MLV_load_image("images/quitBtn_small_idle.png");
    quitBtn->hoverImage = MLV_load_image("images/quitBtn_small_hover.png");
    quitBtn->activeImage = MLV_load_image("images/quitBtn_small_active.png");
    quitBtn->callback = 'q';

    /*Now we add them to the toPrint list*/
    addToPrint(mainTitlePicture, 'p');

    playBtnElement = addToPrint(playBtn, 'b');
    playBtnElement->state = 'i';

    rulesBtnElement = addToPrint(rulesBtn, 'b');
    rulesBtnElement->state = 'i';

    quitBtnElement = addToPrint(quitBtn, 'b');
    quitBtnElement->state = 'i';

    /*printFrame();*/                   
    callback = waitForAction(); 		            /*Keep application idle until a button callBack is fired. It handle mouse hovering*/ 

    /*Free created elements*/
    freeBtn(playBtn);
    freeBtn(rulesBtn);
    freeBtn(quitBtn);
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
    Button * onePlayerBtn, * twoPlayersBtn, * backBtn;
    PrintElement * onePlayerBtnElement, * twoPlayersBtnElement, * backBtnElement;

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

    backBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, 'g');
    backBtn->idleImage = MLV_load_image("images/backBtn_small_idle.png");
    backBtn->hoverImage = MLV_load_image("images/backBtn_small_hover.png");
    backBtn->activeImage = MLV_load_image("images/backBtn_small_active.png");
    backBtn->callback = 'b';

    /*Now we add them to the toPrint list*/
    onePlayerBtnElement = addToPrint(onePlayerBtn, 'b');
    onePlayerBtnElement->state = 'i';

    twoPlayersBtnElement = addToPrint(twoPlayersBtn, 'b');
    twoPlayersBtnElement->state = 'i';

    backBtnElement = addToPrint(backBtn, 'b');
    backBtnElement->state = 'i';

    callback = waitForAction();                /*Wait for the user to do something*/

    /*Free created elements*/
    freeBtn(onePlayerBtn);
    freeBtn(twoPlayersBtn);
    freeBtn(backBtn);

    /*And finally call next action*/
    if(callback == '1')
        initNewGame(1);
    else if(callback == '2')
        initNewGame(2);
    else if(callback == 'b')
        mainMenu();
}

void initNewGame(int nbrPlayer)                /*Ask the player.s to enter it's name*/
{
    char callback;
    TextBox * player1, * player2;
    Button * validBtn, * backBtn;
    PrintElement * player1Element, * player2Element, * validBtnElement, * backBtnElement;

    cleanToPrint();

    if(nbrPlayer == 1)
    {
        player1 = createTextBox(percentOffset(50, 'w', -126), percent(60, 'h'), 252, 40, 'g', "Joueur 1");
    }
    else
    {
        player1 = createTextBox(percentOffset(50, 'w', -262), percent(60, 'h'), 252, 40, 'g', "Joueur 1");

        player2 = createTextBox(percentOffset(50, 'w', 10), percent(60, 'h'), 252, 40, 'g', "Joueur 2");
        player2->backImage = MLV_load_image("images/textField.png");
        player2->imgOffsetX = -5;
        player2->imgOffsetY = -2;

        player2Element = addToPrint(player2, 'i');
        player2Element->state = 'b';
    }

    player1->backImage = MLV_load_image("images/textField.png");
    player1->imgOffsetX = -5;
    player1->imgOffsetY = -2;

    validBtn = createBtn(percentOffset(50, 'w', -72), percentOffset(60, 'h', 50), 145, 36, 'g');
    validBtn->idleImage = MLV_load_image("images/confirmBtn_small_idle.png");
    validBtn->hoverImage = MLV_load_image("images/confirmBtn_small_hover.png");
    validBtn->activeImage = MLV_load_image("images/confirmBtn_small_active.png");
    validBtn->callback = 'v';

    backBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, 'g');
    backBtn->idleImage = MLV_load_image("images/backBtn_small_idle.png");
    backBtn->hoverImage = MLV_load_image("images/backBtn_small_hover.png");
    backBtn->activeImage = MLV_load_image("images/backBtn_small_active.png");
    backBtn->callback = 'b';

    player1Element = addToPrint(player1, 'i');
    player1Element->state = 'b';

    validBtnElement = addToPrint(validBtn, 'b');
    validBtnElement->state = 'i';

    backBtnElement = addToPrint(backBtn, 'b');
    backBtnElement->state = 'i';

    callback = waitForAction();

    freeBtn(validBtn);
    freeBtn(backBtn);
    freeTextBox(player1);
    if(nbrPlayer == 2)
        freeTextBox(player2);

    if(callback == 'b')
        choicePlayers();
    else if(callback == 'v')
    {
        /*Save user name blablabla*/
        startGame(nbrPlayer);
    }
}

void startGame(int nbrPlayer)
{
    createBoardGame(10, 10);        /*Generate a map with the given dimensions*/
    gameObj->gameState = 'a';       /*Set game state as active, so the cleanScreen will reset with the gameBoard*/
    gameObj->nbrPlayer = nbrPlayer;

    setUpPlayer(1);
    setUpPlayer(2);
    waitForAction();
}

void setUpPlayer(int playerID)
{
    int i, j, marginTop, stepTop = 50;
    Picture * board;
    int leftOffset;

    cleanToPrint();

    if(playerID == 1 || (playerID == 2 && gameObj->nbrPlayer == 2))
    {                               /*Human player*/
        if(playerID == 1)
        {
            board = createPicture(0, 0, "images/woodPlankRight.png");
            leftOffset = percentOffset(50, 'w', 50);
        }
        else
        {
            board = createPicture(0, 0, "images/woodPlankLeft.png");
            leftOffset = 25;
        }

        addToPrint(board, 'p');
        marginTop = 100;

        addToPrint(board, 'p');
        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {
                /*Add boatBtn*/
                printf("%d %d\n", i, j);
                /*Using dirt bloc as a placeholder unitl sheeps are ready*/
                addToPrint(createPicture(leftOffset, marginTop, "images/dirtBloc.png"), 'p');
                marginTop += stepTop;
            }
        }

        /*Add a button for every cell on the grid*/
        /*loop on every boat (same loop as before)*/
        /*For each boat, wait for a user click on a cell
            If the boat can be placed here, then go to the next boat
            Otherwise do not do anything
            Also allow user to rotate the boat using buttons placed at the bottom of the panel
            And show on the grid wich cells the boat will be occuping when the cells get hovered    
        */

        waitForAction();    /*Now just a hold on to be remove*/

        freePicture(board);
    }
    else
    {                               /*AI*/

    }

}