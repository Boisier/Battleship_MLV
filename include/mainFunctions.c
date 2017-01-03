#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"


GameObj * initGame()                /*Generate the gameObj, create the window, ...*/
{
    GameObj * gameObj = allocate(sizeof(GameObj));   /*Define gameObj variable*/

    gameObj->currTurn = 0;          /*Set current turn as 0*/

    gameObj->nbrShips[1] = 0;       /*Set nbr of boat for every size*/
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
    /*Printing the logs when ASAN is active is not relevant because ASAN use a lot of memory*/

    return gameObj;                 /*Return the gameObj*/
}

void mainMenu()                     /*display the main menu and wait for actions from the user*/
{
    char callback;
    Button * playBtn, * rulesBtn, * quitBtn;
    Picture * mainTitlePicture;

    cleanToPrint();                 /*Empty the list of element to print before doing anything*/

    /*Let's create the elements to be displayed*/
    /*Main Title*/
    mainTitlePicture = createPicture(percentOffset(50, 'w', -353), 70, "images/mainTitle.png");

    /*Play Button*/
    playBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', -26), 185, 50, BTN_GRAPHIC);
    playBtn->idleImage = MLV_load_image("images/buttons/playBtn_idle.png");
    playBtn->hoverImage = MLV_load_image("images/buttons/playBtn_hover.png");
    playBtn->activeImage = MLV_load_image("images/buttons/playBtn_active.png");
    playBtn->callback = 'p';

    /*Rules Button*/
    rulesBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 50, BTN_GRAPHIC);
    rulesBtn->idleImage = MLV_load_image("images/buttons/rulesBtn_idle.png");
    rulesBtn->hoverImage = MLV_load_image("images/buttons/rulesBtn_hover.png");
    rulesBtn->activeImage = MLV_load_image("images/buttons/rulesBtn_active.png");
    rulesBtn->callback = 'r';

    quitBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, BTN_GRAPHIC);
    quitBtn->idleImage = MLV_load_image("images/buttons/quitBtn_small_idle.png");
    quitBtn->hoverImage = MLV_load_image("images/buttons/quitBtn_small_hover.png");
    quitBtn->activeImage = MLV_load_image("images/buttons/quitBtn_small_active.png");
    quitBtn->callback = 'q';

    /*Now we add them to the toPrint list*/
    addToPrint(mainTitlePicture, PICTURE);
    addToPrint(playBtn, BUTTON);
    addToPrint(rulesBtn, BUTTON);
    addToPrint(quitBtn, BUTTON);

    callback = waitForAction(); 		            /*Keep application idle until a button callBack is fired. It handle mouse hovering*/ 

    /*Free created elements*/
    freeBtn(playBtn);
    freeBtn(rulesBtn);
    freeBtn(quitBtn);
    freePicture(mainTitlePicture);

    /*And finally call next action*/
    if(callback == 'p')
        initNewGame(0);
    else if(callback == 'r')
        clicked();
}

void initNewGame()                /*Ask the player.s to enter his.their name.s*/
{
    int nbrPlayer = 2;
    char callback = NULL;
    TextBox * player1, * player2;
    Button * validBtn, * backBtn, * onePlayerBtn, * twoPlayerBtn;
    PrintElement * player2Element;

    cleanToPrint();

    onePlayerBtn = createBtn(percentOffset(50, 'w', -118), percent(10, 'h'), 118, 40, BTN_GRAPHIC);
    onePlayerBtn->idleImage = MLV_load_image("images/buttons/onePlayerTab_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/buttons/onePlayerTab_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/buttons/onePlayerTab_active.png");
    onePlayerBtn->canToggle = true;
    onePlayerBtn->callback = 1;

    twoPlayerBtn = createBtn(percent(50, 'w'), percent(10, 'h'), 118, 40, BTN_GRAPHIC);
    twoPlayerBtn->idleImage = MLV_load_image("images/buttons/twoPlayerTab_idle.png");
    twoPlayerBtn->hoverImage = MLV_load_image("images/buttons/twoPlayerTab_hover.png");
    twoPlayerBtn->activeImage = MLV_load_image("images/buttons/twoPlayerTab_active.png");
    twoPlayerBtn->canToggle = true;
    twoPlayerBtn->checked = true;
    twoPlayerBtn->callback = 2;
    
    player1 = createTextBox(percentOffset(50, 'w', -262), percentOffset(10, 'h', 50), 252, 40, 'g', "Joueur 1");
    player1->backImage = MLV_load_image("images/textField.png");
    player1->imgOffsetX = -5;
    player1->imgOffsetY = -2;

    player2 = createTextBox(percentOffset(50, 'w', 10), percentOffset(10, 'h', 50), 252, 40, 'g', "Joueur 2");
    player2->backImage = MLV_load_image("images/textField.png");
    player2->imgOffsetX = -5;
    player2->imgOffsetY = -2;

    validBtn = createBtn(percentOffset(50, 'w', -72), percentOffset(60, 'h', 50), 145, 36, BTN_GRAPHIC);
    validBtn->idleImage = MLV_load_image("images/buttons/confirmBtn_small_idle.png");
    validBtn->hoverImage = MLV_load_image("images/buttons/confirmBtn_small_hover.png");
    validBtn->activeImage = MLV_load_image("images/buttons/confirmBtn_small_active.png");
    validBtn->callback = 'v';

    backBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, BTN_GRAPHIC);
    backBtn->idleImage = MLV_load_image("images/buttons/backBtn_small_idle.png");
    backBtn->hoverImage = MLV_load_image("images/buttons/backBtn_small_hover.png");
    backBtn->activeImage = MLV_load_image("images/buttons/backBtn_small_active.png");
    backBtn->callback = 'b';

    addToPrint(onePlayerBtn, BUTTON);
    addToPrint(twoPlayerBtn, BUTTON);
    addToPrint(player1, TEXTBOX);
    addToPrint(validBtn, BUTTON);
    addToPrint(backBtn, BUTTON);
    player2Element = addToPrint(player2, TEXTBOX);

    do
    {
        callback = waitForAction();

        if(callback == 1)
        {
            onePlayerBtn->checked = true;
            twoPlayerBtn->checked = false;

            player2Element->display = false;
            player1->x = percentOffset(50, 'w', -126);  
            nbrPlayer = 1;
        }
        else if(callback == 2)
        {
            onePlayerBtn->checked = false;
            twoPlayerBtn->checked = true;

            player2Element->display = true; 
            player1->x = percentOffset(50, 'w', -262);
            nbrPlayer = 2;
        }

    } while(callback != 'v' && callback != 'b');

    freeBtn(validBtn);
    freeBtn(backBtn);
    freeBtn(onePlayerBtn);
    freeBtn(twoPlayerBtn);

    if(callback == 'b')
        mainMenu();
    else if(callback == 'v')
    {
        /*Create users and save their user name*/
        createPlayer(1, player1->content, PLAYER_HUMAN);

        if(nbrPlayer == 2)
            createPlayer(2, player2->content, PLAYER_HUMAN);
        else
            createPlayer(2, "Ordinateur", PLAYER_AI);

        startGame(nbrPlayer);
    }
}

void startGame(int nbrPlayer)
{
    createBoardGame(gameObj->gridSizeX, gameObj->gridSizeY);        /*Generate a map with the given dimensions*/
    gameObj->gameState = 'a';       /*Set game state as active, so the cleanScreen will reset with the gameBoard*/
    gameObj->nbrPlayer = nbrPlayer;

    gameObj->currTurn = 1;
    setUpPlayer(1);

    gameObj->currTurn = 2;
    setUpPlayer(2);

    waitForAction();
}

void createPlayer(int playerID, char * playerName, enum playerType type) /*Init the player struct in the gameObj*/
{
    Player player;                    /*creating temporary structs*/
    Grid grid;
    int i, j;

    player.type = type;
    strcpy(player.name, playerName);

    grid.sizeX = gameObj->gridSizeX;
    grid.sizeY = gameObj->gridSizeY;
    grid.nbrOfShips = 0;
    grid.ships = allocate(sizeof(Ship) * 5);

    for(i = 0; i < gameObj->gridSizeX; i++)
    {
        for(j = 0; j < gameObj->gridSizeY; j++)
        {
            grid.cells[i][j].type = CELL_EMPTY;
            grid.cells[i][j].hit = false;
        }
    }

    player.grid = grid;

    if(playerID == 1)                   /*Inserting newly created data inside the gameObj*/
        gameObj->player1 = player;
    else
        gameObj->player2 = player;
}

void setUpPlayer(int playerID)
{
    int i, j, k, marginTop, stepTop = 50, callback = 0, boatX, boatY;
    int gridOffsetTop = gameObj->gridOffsetTop, gridOffsetLeft = gameObj->gridOffsetLeft, leftOffset = 0;
    char direction;
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
            leftOffset = percentOffset(50, 'w', 35);
        }
        else
        {
            board = createPicture(0, 0, "images/woodPlankLeft.png");
            leftOffset = 25;
            gridOffsetLeft += 560;
        }

        addToPrint(board, PICTURE);
        marginTop = 85;

        /*Add a BEAUTIFUL title*/
        addToPrint(createPicture(leftOffset+115, marginTop, "images/placeYourBoats.png"), PICTURE);
        marginTop += 150;

        /*Add a cursor to tell wich boat we are placing*/
        currentBoatIndicator = createPicture(leftOffset+150, marginTop, "images/selector_cursor.png");
        addToPrint(currentBoatIndicator, PICTURE);

        /*Add a button to rotate the current boat*/
        rotateBtn = createBtn(leftOffset, marginTop, 145, 36, BTN_GRAPHIC);
        rotateBtn->idleImage = MLV_load_image("images/buttons/rotateBtn_small_idle.png");
        rotateBtn->hoverImage = MLV_load_image("images/buttons/rotateBtn_small_hover.png");
        rotateBtn->activeImage = MLV_load_image("images/buttons/rotateBtn_small_active.png");
        rotateBtn->callback = 'r';
        addToPrint(rotateBtn, BUTTON);

        /*Print a list of all the boats to add*/
        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {
                for(k = 0; k < i; k++)
                {
                    addToPrint(createPicture(leftOffset+160+(35*(k+1)), marginTop, "images/sheep_idle.png"), PICTURE);
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
                tempBtn = createBtn(gridOffsetLeft+(i*35), gridOffsetTop+(j*35), 35, 35, BTN_GRAPHIC);
                tempBtn->hoverImage = targetImage;
                tempBtn->callback = mergeInts(i, j);
                tempBtn->hoverCallback = printBoatShadow;

                tempElement = addToPrint(tempBtn, BUTTON);
                tempElement->canFade = true;
            }
        }

        /*loop on every boat to add them (same loop as before)*/
        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {                
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
                        splitInts(callback, &boatX, &boatY);

                        added = addBoat(boatX, boatY, i, gameObj->boatBeingPlacedDirection);
                        
                        if(added)
                        {   /*The ship has been added, so we print it on the screen;*/

                            addToPrint(createPicture(leftOffset+150, currentBoatIndicator->y, "images/tick.png"), PICTURE);
                            currentBoatIndicator->y += stepTop;
                            rotateBtn->y += stepTop;

                            if(gameObj->boatBeingPlacedDirection == 'h')
                            {
                                for(k = boatX; k < boatX+i; k++)
                                {
                                    addToPrint(createPicture(gridOffsetLeft+(k*35), gridOffsetTop+(boatY*35), "images/sheep_idle.png"), PICTURE);
                                }
                            }
                            else if(gameObj->boatBeingPlacedDirection == 'v')
                            {
                                for(k = boatY; k < boatY+i; k++)
                                {
                                    addToPrint(createPicture(gridOffsetLeft+(boatX*35), gridOffsetTop+(k*35), "images/sheep_idle.png"), PICTURE);
                                }
                            }
                        }
                    }

                } while(added == false);
            }
        }

        freePicture(board);
        freePicture(currentBoatIndicator);
        freeBtn(rotateBtn);
        MLV_free_image(targetImage);

        cleanToPrint();    
    }
    else
    {                               /*AI*/
        srand(time(NULL));
        for(i = 5; i > 0; i--)
        {
            for(j = 0; j < gameObj->nbrShips[i]; j++)
            {                
                gameObj->boatBeingPlacedSize = i;
                do
                {

                    if(rand() % 2 == 0)
                    {
                        direction = 'h';
                        boatX = rand() % (gameObj->gridSizeX - i);
                        boatY = rand() % gameObj->gridSizeY;
                    }
                    else
                    {
                        direction = 'v';
                        boatX = rand() % gameObj->gridSizeX;
                        boatY = rand() % (gameObj->gridSizeY - i);
                    }
                    
                    printf("addBoat(%d, %d, %d, %c)\n", boatX, boatY, i, direction);

                    added = addBoat(boatX, boatY, i, direction);

                } while(added == false);
            }
        }
    }
}

bool addBoat(int boatX, int boatY, int boatSize, char boatDirection)
{
    int i;
    Grid grid;
    Ship newShip;

    /*Make sure given data are between the grid boudaries*/
    if(boatX < 0 || boatX > gameObj->gridSizeX || boatY < 0 || boatY > gameObj->gridSizeY)
        return false;

    /*get the current player grid*/
    if(gameObj->currTurn == 1)
        grid = gameObj->player1.grid;
    else
        grid = gameObj->player2.grid;
    
    /*check if every concerned cells are availables*/
    if(boatDirection == 'h' && boatX+boatSize-1 < grid.sizeX)
    {
        for(i = boatX; i < boatX+boatSize; i++)
        {
            if(grid.cells[i][boatY].type != CELL_EMPTY)
            {
                return false;
            }
        }
    }
    else if(boatDirection == 'v' && boatY+boatSize-1 < grid.sizeY)
    {
        for(i = boatY; i < boatY+boatSize; i++)
        {
            if(grid.cells[boatX][i].type != CELL_EMPTY)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    /*If we are here it means the boat can be added safely*/
    newShip.size = boatSize;
    newShip.direction = boatDirection;
    newShip.posX = boatX;
    newShip.posY = boatY;
    newShip.hits[0] = false;
    newShip.hits[1] = false;
    newShip.hits[2] = false;
    newShip.hits[3] = false;
    newShip.hits[4] = false;

    grid.ships[grid.nbrOfShips] = newShip;
    grid.nbrOfShips++;
    /*The ship is on the list, now we mark the cells has taken*/
    if(boatDirection == 'h')
    {
        for(i = boatX; i < boatX+boatSize; i++)
        {
            grid.cells[i][boatY].type = 's';
        }
    }
    else if(boatDirection == 'v')
    {
        for(i = boatY; i < boatY+boatSize; i++)
        {
            grid.cells[boatX][i].type = 's';
        }
    }

    if(gameObj->currTurn == 1)
        gameObj->player1.grid = grid;
    else
        gameObj->player2.grid = grid;

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
        if(gameObj->toPrint[i].state == FORCEHOVER)
            gameObj->toPrint[i].state = IDLE;
    }

    if(canBePrinted)
    {   /*The boat can be safely printed*/
        for(i = 0; i < boatSize; i++)
        {
            if(gameObj->boatBeingPlacedDirection == 'h')
            {
                gameObj->toPrint[posInToPrint+i*gameObj->gridSizeY].state = FORCEHOVER;
            }
            else if(gameObj->boatBeingPlacedDirection == 'v')
            {
                gameObj->toPrint[posInToPrint+i].state = FORCEHOVER;
            }
        }
    }
}