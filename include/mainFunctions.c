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

    gameObj->gridSizeX = 10;
    gameObj->gridSizeY = 10;

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
        /*Create users and save their user name*/
        createPlayer(1, player1->content, 'h');

        if(nbrPlayer == 2)
            createPlayer(2, player2->content, 'h');
        else
            createPlayer(1, "Ordinateur", 'c');

        startGame(nbrPlayer);
    }
}

void createPlayer(int playerID, char * playerName, char playerType) /*Init the player struct in the gameObj*/
{
    Player * player;                    /*creating temporary structs*/
    Grid * grid;
    Cell ** cells;
    int i;

    player = allocate(sizeof(Player));  /*Defining player*/

    player->type = 'h';
    strcpy(player->name, playerName);

    grid = allocate(sizeof(grid));      /*Defining the grid*/
    grid->sizeX = gameObj->gridSizeX;
    grid->sizeY = gameObj->gridSizeY;

    cells = allocate(sizeof(Cell *) * gameObj->gridSizeX);
    for(i = 0; i < gameObj->gridSizeX; i++)
    {
        cells[i] = allocate(sizeof(Cell *) * gameObj->gridSizeY);
    }

    grid->cells = cells;
    player->grid = grid;

    if(playerID == 1)                   /*Inserting newly created data inside the gameObj*/
        gameObj->player1 = player;
    else
        gameObj->player2 = player;
}

void startGame(int nbrPlayer)
{
    createBoardGame(gameObj->gridSizeX, gameObj->gridSizeY);        /*Generate a map with the given dimensions*/
    gameObj->gameState = 'a';       /*Set game state as active, so the cleanScreen will reset with the gameBoard*/
    gameObj->nbrPlayer = nbrPlayer;

    setUpPlayer(1);
    setUpPlayer(2);
}

void setUpPlayer(int playerID)
{
    int i, j, k, marginTop, stepTop = 50, callback = 0;
    int gridOffsetTop = 307, gridOffsetLeft = 94, leftOffset = 0;
    Picture * board = NULL;
    Picture * currentBoatIndicator = NULL;
    Button * tempBtn = NULL, * rotateBtn = NULL;
    MLV_Image * targetImage = NULL;
    PrintElement * tempElement;
    bool added = false;

    cleanToPrint();  
    
    if(playerID == 1 || (playerID == 2 && gameObj->nbrPlayer == 2))
    {                               /*Human player*/
        gameObj->currTurn = playerID;

        /*Create and add to print the wooden board*/
        if(playerID == 1)
        {
            board = createPicture(0, 0, "images/woodPlankRight.png");
            leftOffset = percentOffset(50, 'w', 25);
        }
        else
        {
            board = createPicture(0, 0, "images/woodPlankLeft.png");
            leftOffset = 25;
            gridOffsetLeft = 654;
        }

        addToPrint(board, 'p');
        marginTop = 100;

        /*Print a list of all the boats to add*/
        currentBoatIndicator = createPicture(leftOffset, marginTop-stepTop, "images/selector_cursor.png");
        addToPrint(currentBoatIndicator, 'p');

        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {
                for(k = 0; k < i; k++)
                {
                    addToPrint(createPicture(leftOffset+(35*(k+1)), marginTop, "images/sheep_idle.png"), 'p');
                }

                marginTop += stepTop;
            }
        }

        /*Add a button for every cell on the grid*/
        targetImage = MLV_load_image("images/sheep_fade.png");

        for(i = 0; i < gameObj->gridSizeX; i++)
        {
            for(j = 0; j < gameObj->gridSizeY; j++)
            {
                tempBtn = createBtn(gridOffsetLeft+(i*35), gridOffsetTop+(j*35), 35, 35, 'g');
                tempBtn->hoverImage = targetImage;
                tempBtn->callback = i | (j << 16);
                tempBtn->hoverCallback = printBoatShadow;

                tempElement = addToPrint(tempBtn, 'b');
                tempElement->canFade = true;
            }
        }

        /*Add a button to rotate the current boat*/
        rotateBtn = createBtn(leftOffset+10, 725, 185, 50, 'g');
        rotateBtn->idleImage = MLV_load_image("images/rotateBtn_idle.png");
        rotateBtn->hoverImage = MLV_load_image("images/rotateBtn_hover.png");
        rotateBtn->activeImage = MLV_load_image("images/rotateBtn_active.png");
        rotateBtn->callback = 'r';

        addToPrint(rotateBtn, 'b');

        /*loop on every boat to add them (same loop as before)*/
        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {
                currentBoatIndicator->y += stepTop;
                
                gameObj->boatBeingPlacedSize = i;
                gameObj->boatBeingPlacedDirection = 'h';

                do
                {
                    callback = waitForAction();

                    if(callback == 'r') 
                    {               /*Rotate the boat*/
                        if(gameObj->boatBeingPlacedDirection == 'h')
                            gameObj->boatBeingPlacedDirection = 'v';
                        else
                            gameObj->boatBeingPlacedDirection = 'h';

                        added = false;
                    }
                    else
                    {               /*Try to add the boat*/
                        added = addBoat((callback & 0xFFFF), (callback >> 16) & 0xFFFF, i, gameObj->boatBeingPlacedDirection);
                    }

                } while(added == false);
            }
        }

        freePicture(board);
        freePicture(currentBoatIndicator);
        MLV_free_image(targetImage);

        cleanToPrint();    
    }
    else
    {                               /*AI*/

    }
}

bool addBoat(int boatX, int boatY, int boatSize, char boatDirection)
{
    return true;
}

void printBoatShadow(int posInToPrint)
{
    bool canBePrinted = true;
    int i, boatSize = gameObj->boatBeingPlacedSize;
    
    /*Are the targeted buttons in range ?*/
    if(gameObj->boatBeingPlacedDirection == 'h' && posInToPrint+gameObj->gridSizeY*(boatSize-1) < gameObj->nbrToPrint)
    {
        for(i = 0; i < (boatSize-1); i++)
        {
            if(gameObj->toPrint[posInToPrint+i*gameObj->gridSizeY].canFade == false)
            {
                canBePrinted = false;
            }
        }
    }
    else if(gameObj->boatBeingPlacedDirection == 'v' && posInToPrint+(boatSize-1) < gameObj->nbrToPrint)
    {
        for(i = 0; i < boatSize; i++)
        {
            if(gameObj->toPrint[posInToPrint+i].canFade == false || ((Button *)gameObj->toPrint[posInToPrint+i].element)->x != ((Button *)gameObj->toPrint[posInToPrint].element)->x)
            {
                canBePrinted = false;
            }
        }
    }
    else
    {
        canBePrinted = false;
    }

    /*Clean up every forced hover*/
    for(i = 0; i < gameObj->nbrToPrint; i++)
    {
        if(gameObj->toPrint[i].state == 'f')
            gameObj->toPrint[i].state = 'i';
    }

    if(canBePrinted)
    {   /*The boat can be safely printed*/
        for(i = 0; i < boatSize; i++)
        {
            if(gameObj->boatBeingPlacedDirection == 'h')
            {
                gameObj->toPrint[posInToPrint+i*gameObj->gridSizeY].state = 'f';
            }
            else if(gameObj->boatBeingPlacedDirection == 'v')
            {
                gameObj->toPrint[posInToPrint+i].state = 'f';
            }
        }
    }
}