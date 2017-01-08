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
    gameObj->waitFont = MLV_load_font("fonts/LCD_Solid.ttf", 36);
    
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
    enum returnValues
    {
        PLAY = 1,
        RULES = 2,
        QUIT = 3
    } callback;
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
    playBtn->callback = PLAY;

    /*Rules Button*/
    rulesBtn = createBtn(percentOffset(50, 'w', -92), percentOffset(60, 'h', 40), 185, 50, BTN_GRAPHIC);
    rulesBtn->idleImage = MLV_load_image("images/buttons/rulesBtn_idle.png");
    rulesBtn->hoverImage = MLV_load_image("images/buttons/rulesBtn_hover.png");
    rulesBtn->activeImage = MLV_load_image("images/buttons/rulesBtn_active.png");
    rulesBtn->callback = RULES;

    quitBtn = createBtn(percentOffset(50, 'w', -72), percent(90, 'h'), 145, 36, BTN_GRAPHIC);
    quitBtn->idleImage = MLV_load_image("images/buttons/quitBtn_small_idle.png");
    quitBtn->hoverImage = MLV_load_image("images/buttons/quitBtn_small_hover.png");
    quitBtn->activeImage = MLV_load_image("images/buttons/quitBtn_small_active.png");
    quitBtn->callback = QUIT;

    /*Now we add them to the toPrint list*/
    addToPrint(mainTitlePicture, PICTURE);
    addToPrint(playBtn, BUTTON);
    addToPrint(rulesBtn, BUTTON);
    addToPrint(quitBtn, BUTTON);

    callback = waitForAction(); 		            /*Keep application idle until a button callBack is fired. It handle mouse hovering*/ 

    /*And finally call next action*/
    if(callback == PLAY)
        initNewGame(0);
    else if(callback == RULES)
        clicked();
    else if(callback == QUIT)
        quitGame();
}

void initNewGame()                /*Ask the player.s to enter his.their name.s*/
{
    int nbrPlayer = 2;
    char player1Name[100], player2Name[100];
    enum returnValues
    {
        SETONEPLAYER = 1,
        SETTWOPLAYERS = 2,
        CONFIRM = 3,
        BACK = 4
    } callback;
    TextBox * player1, * player2;
    Button * validBtn, * backBtn, * onePlayerBtn, * twoPlayerBtn;
    NumberBox * gridSizeX, * gridSizeY, * fiveBlocksBoats, * fourBlocksBoats, * threeBlocksBoats, * twoBlocksBoats, *oneBlockBoats;
    PrintElement * player2Element;

    cleanToPrint();

    gameObj->gameState = 'm';       /*Set game state as in menu, so the cleanScreen will reset with the wooden background*/

    addToPrint(createPicture(percentOffset(50, 'w', -212), 40, "images/newGameTitle.png"), PICTURE);

    onePlayerBtn = createBtn(percentOffset(50, 'w', -118), 140, 118, 40, BTN_GRAPHIC);
    onePlayerBtn->idleImage = MLV_load_image("images/buttons/onePlayerTab_idle.png");
    onePlayerBtn->hoverImage = MLV_load_image("images/buttons/onePlayerTab_hover.png");
    onePlayerBtn->activeImage = MLV_load_image("images/buttons/onePlayerTab_active.png");
    onePlayerBtn->canToggle = true;
    onePlayerBtn->callback = SETONEPLAYER;

    twoPlayerBtn = createBtn(percent(50, 'w'), 140, 118, 40, BTN_GRAPHIC);
    twoPlayerBtn->idleImage = MLV_load_image("images/buttons/twoPlayerTab_idle.png");
    twoPlayerBtn->hoverImage = MLV_load_image("images/buttons/twoPlayerTab_hover.png");
    twoPlayerBtn->activeImage = MLV_load_image("images/buttons/twoPlayerTab_active.png");
    twoPlayerBtn->canToggle = true;
    twoPlayerBtn->checked = true;
    twoPlayerBtn->callback = SETTWOPLAYERS;
    
    player1 = createTextBox(percentOffset(50, 'w', -264), 190, 252, 40, 'g', "Joueur 1");
    player1->backImage = MLV_load_image("images/textField.png");
    player1->imgOffsetX = -5;
    player1->imgOffsetY = -2;

    player2 = createTextBox(percentOffset(50, 'w', 8), 190, 252, 40, 'g', "Joueur 2");
    player2->backImage = MLV_load_image("images/textField.png");
    player2->imgOffsetX = -5;
    player2->imgOffsetY = -2;

    addToPrint(createPicture(percentOffset(50, 'w', -325), 250, "images/hDivider.png"), PICTURE);
    addToPrint(createPicture(percentOffset(50, 'w', -142), 280, "images/gridSize.png"), PICTURE);
    addToPrint(createPicture(percentOffset(50, 'w', -16), 337, "images/times.png"), PICTURE);

    gridSizeX = createNumberBox(percentOffset(50, 'w', -192), 330, 10, 5, 10);
    gridSizeY = createNumberBox(percentOffset(50, 'w', 18), 330, 10, 5, 10);

    addToPrint(createPicture(percentOffset(50, 'w', -325), 400, "images/hDivider.png"), PICTURE);
    addToPrint(createPicture(percentOffset(50, 'w', -174), 430, "images/sheepNbr.png"), PICTURE);

    addToPrint(createPicture(86, 490, "images/sheepGroup5.png"), PICTURE);
    addToPrint(createPicture(286, 490, "images/sheepGroup4.png"), PICTURE);
    addToPrint(createPicture(486, 490, "images/sheepGroup3.png"), PICTURE);
    addToPrint(createPicture(686, 490, "images/sheepGroup2.png"), PICTURE);
    addToPrint(createPicture(886, 490, "images/sheepGroup1.png"), PICTURE);


    fiveBlocksBoats = createNumberBox(65, 520, 1, 0, 2);
    fourBlocksBoats = createNumberBox(265, 520, 1, 0, 2);
    threeBlocksBoats = createNumberBox(465, 520, 2, 0, 3);
    twoBlocksBoats = createNumberBox(665, 520, 1, 0, 3);
    oneBlockBoats = createNumberBox(865, 520, 0, 0, 3);

    addToPrint(createPicture(percentOffset(50, 'w', -325), 590, "images/hDivider.png"), PICTURE);
    
    validBtn = createBtn(percentOffset(50, 'w', -92), 620, 183, 50, BTN_GRAPHIC);
    validBtn->idleImage = MLV_load_image("images/buttons/goBtn_idle.png");
    validBtn->hoverImage = MLV_load_image("images/buttons/goBtn_hover.png");
    validBtn->activeImage = MLV_load_image("images/buttons/goBtn_active.png");
    validBtn->callback = CONFIRM;

    backBtn = createBtn(percentOffset(50, 'w', -72), 720, 145, 36, BTN_GRAPHIC);
    backBtn->idleImage = MLV_load_image("images/buttons/backBtn_small_idle.png");
    backBtn->hoverImage = MLV_load_image("images/buttons/backBtn_small_hover.png");
    backBtn->activeImage = MLV_load_image("images/buttons/backBtn_small_active.png");
    backBtn->callback = BACK;

    addToPrint(onePlayerBtn, BUTTON);
    addToPrint(twoPlayerBtn, BUTTON);
    addToPrint(player1, TEXTBOX);
    addToPrint(validBtn, BUTTON);
    addToPrint(backBtn, BUTTON);
    addToPrint(gridSizeX, NUMBERBOX);
    addToPrint(gridSizeY, NUMBERBOX);
    addToPrint(fiveBlocksBoats, NUMBERBOX);
    addToPrint(fourBlocksBoats, NUMBERBOX);
    addToPrint(threeBlocksBoats, NUMBERBOX);
    addToPrint(twoBlocksBoats, NUMBERBOX);
    addToPrint(oneBlockBoats, NUMBERBOX);
    player2Element = addToPrint(player2, TEXTBOX);

    do
    {
        callback = waitForAction();

        if(callback == SETONEPLAYER)
        {
            onePlayerBtn->checked = true;
            twoPlayerBtn->checked = false;

            player2Element->display = false;
            player1->x = percentOffset(50, 'w', -126);  
            nbrPlayer = 1;
        }
        else if(callback == SETTWOPLAYERS)
        {
            onePlayerBtn->checked = false;
            twoPlayerBtn->checked = true;

            player2Element->display = true; 
            player1->x = percentOffset(50, 'w', -262);
            nbrPlayer = 2;
        }

    } while(callback != CONFIRM && callback != BACK);

    if(callback == BACK)
        mainMenu();
    else if(callback == CONFIRM)
    {
        /*Save users parameters*/

        gameObj->gridSizeX = gridSizeX->value;
        gameObj->gridSizeY = gridSizeY->value;

        gameObj->nbrShips[1] = oneBlockBoats->value;
        gameObj->nbrShips[2] = twoBlocksBoats->value;
        gameObj->nbrShips[3] = threeBlocksBoats->value;
        gameObj->nbrShips[4] = fourBlocksBoats->value;
        gameObj->nbrShips[5] = fiveBlocksBoats->value;

        /*Create users and save their user name*/
        strcpy(player1Name, player1->content);
        if(strlen(player1Name) == 0)
            strcpy(player1Name, player1->placeHolder);
        createPlayer(1, player1Name, PLAYER_HUMAN);

        if(nbrPlayer == 2)
        {
            strcpy(player2Name, player2->content);
            if(strlen(player2Name) == 0)
                strcpy(player2Name, player2->placeHolder);
            createPlayer(2, player2Name, PLAYER_HUMAN);
        }
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

    if(setUpPlayer(1) == 1)
    {   /*Continue if the player hasn't exited the setup function*/
        gameObj->currTurn = 2;
        setUpPlayer(2);

        inGame();
    }
}

void createPlayer(int playerID, char * playerName, playerType type) /*Init the player struct in the gameObj*/
{
    Player player;                    /*creating temporary structs*/
    Grid grid;
    int i, j, boatsNbr = 0;

    player.type = type;
    strcpy(player.name, playerName);

    grid.sizeX = gameObj->gridSizeX;
    grid.sizeY = gameObj->gridSizeY;
    grid.nbrOfShips = 0;

    for(i = 1; i < 6; i++)
        boatsNbr += gameObj->nbrShips[i];

    grid.ships = allocate(sizeof(Ship) * boatsNbr);

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

int setUpPlayer(int playerID)
{
    enum returnValues
    {
        ROTATE = 1,
        RESTART = 2,
        QUIT = 3,
        CONFIRM = 4
    } callback;
    int i, j, k, marginTop, stepTop = 40, boatX, boatY;
    int gridOffsetTop = gameObj->gridOffsetTop, gridOffsetLeft = gameObj->gridOffsetLeft, leftOffset = 0;
    char direction;
    Picture * board;
    Picture * currentBoatIndicator;
    Button * tempBtn, * rotateBtn, * quitBtn, * restartBtn, * confirmBtn;
    PrintElement * tempElement;
    bool added = false;
    
    if(playerID == 1 || (playerID == 2 && gameObj->player2.type == PLAYER_HUMAN))
    {                               /*Human player*/
        if(gameObj->currTurn != playerID)
        {
            gameObj->currTurn = playerID;
            waitForPlayer();
        }

        cleanToPrint();  

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
        marginTop += 130;

        /*Add a cursor to tell wich boat we are placing*/
        currentBoatIndicator = createPicture(leftOffset+150, marginTop, "images/selector_cursor.png");
        addToPrint(currentBoatIndicator, PICTURE);

        /*Add a button to rotate the current boat*/
        rotateBtn = createBtn(leftOffset, marginTop, 145, 36, BTN_GRAPHIC);
        rotateBtn->idleImage = MLV_load_image("images/buttons/rotateBtn_small_idle.png");
        rotateBtn->hoverImage = MLV_load_image("images/buttons/rotateBtn_small_hover.png");
        rotateBtn->activeImage = MLV_load_image("images/buttons/rotateBtn_small_active.png");
        rotateBtn->callback = ROTATE;
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

        for(i = 0; i < gameObj->gridSizeX; i++)
        {
            for(j = 0; j < gameObj->gridSizeY; j++)
            {
                tempBtn = createBtn(gridOffsetLeft+(i*35), gridOffsetTop+(j*35), 35, 35, BTN_GRAPHIC);
                tempBtn->hoverImage = MLV_load_image("images/sheep_fade.png");
                tempBtn->activeImage = MLV_load_image("images/sheep_fade.png");
                tempBtn->callback = mergeInts(i, j);
                tempBtn->hoverCallback = printBoatShadow;

                tempElement = addToPrint(tempBtn, BUTTON);
                tempElement->canFade = true;
            }
        }

        /*Add some control buttons*/
        restartBtn = createBtn(leftOffset + 160 + 15, 750, 145, 36, BTN_GRAPHIC);
        restartBtn->idleImage = MLV_load_image("images/buttons/restartBtn_small_idle.png");
        restartBtn->hoverImage = MLV_load_image("images/buttons/restartBtn_small_hover.png");
        restartBtn->activeImage = MLV_load_image("images/buttons/restartBtn_small_active.png");
        restartBtn->callback = RESTART;
        addToPrint(restartBtn, BUTTON);

        if(gameObj->currTurn == 1)
        {
            quitBtn = createBtn(leftOffset + 15 + 320, 750, 145, 36, BTN_GRAPHIC);
            quitBtn->idleImage = MLV_load_image("images/buttons/quitBtn_small_idle.png");
            quitBtn->hoverImage = MLV_load_image("images/buttons/quitBtn_small_hover.png");
            quitBtn->activeImage = MLV_load_image("images/buttons/quitBtn_small_active.png");
            quitBtn->callback = QUIT;
            addToPrint(quitBtn, BUTTON);
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

                    if(callback == ROTATE) 
                    {               /*Rotate the boat*/
                        if(gameObj->boatBeingPlacedDirection == 'h')
                            gameObj->boatBeingPlacedDirection = 'v';
                        else
                            gameObj->boatBeingPlacedDirection = 'h';

                        added = false;
                    }
                    else if(callback == QUIT)
                    {
                        initNewGame();
                        return 0;
                    }
                    else if(callback == RESTART)
                    {
                        resetPlayerGrid(playerID);
                        setUpPlayer(playerID);
                        return 0;
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

        /*All boats are now placed. Let's deactive all interactions on the grid then adding the confirm Btn*/

        gameObj->boatBeingPlacedDirection = 0;
        gameObj->boatBeingPlacedSize = 0;

        for(i = 0; i < gameObj->nbrToPrint; i++)
        {
            if(gameObj->toPrint[i].canFade == true)
            {
                gameObj->toPrint[i].display = false;
            }
        }


        currentBoatIndicator->y = -500;
        rotateBtn->y = -500;

        confirmBtn = createBtn(leftOffset + 15, 750, 145, 36, BTN_GRAPHIC);
        confirmBtn->idleImage = MLV_load_image("images/buttons/confirmBtn_small_idle.png");
        confirmBtn->hoverImage = MLV_load_image("images/buttons/confirmBtn_small_hover.png");
        confirmBtn->activeImage = MLV_load_image("images/buttons/confirmBtn_small_active.png");
        confirmBtn->callback = CONFIRM;
        if(gameObj->currTurn == 2)
            confirmBtn->x = leftOffset + 15 + 320;
        addToPrint(confirmBtn, BUTTON);

        callback = waitForAction();

        if(callback == QUIT)
        {
            initNewGame();
            return 0;
        }
        else if(callback == RESTART)
        {
            resetPlayerGrid(playerID);
            setUpPlayer(playerID);
            return 0;
        }
    }
    else
    {                               /*AI*/
        cleanToPrint();  
        
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

        waitForComputer();
    }

    return 1;
}

void inGame()
{
    enum
    {
        MISS,
        HIT,
        SINKED
    } turnResult;
    bool keepPlaying = true, beenSinked;
    Player * self, * opponent;
    int topOffset = gameObj->gridOffsetTop, leftOffsetOpponent, leftOffsetSelf, i, j, callback, targetX, targetY, boatTouched, sinkedCells = 0, sinkedBoats = 0;
    Button * tempBtn;

    gameObj->currTurn = 1;

    do
    {
        waitForPlayer();
        cleanToPrint();

        turnResult = MISS;

        /*Initialize data of self and opponent*/
        if(gameObj->currTurn == 1)
        {
            self = &gameObj->player1;
            opponent = &gameObj->player2;
            leftOffsetSelf = gameObj->gridOffsetLeft;
            leftOffsetOpponent = gameObj->gridOffsetLeft + 560;
        }
        else 
        {
            self = &gameObj->player2;
            opponent = &gameObj->player1;
            leftOffsetOpponent = gameObj->gridOffsetLeft;
            leftOffsetSelf = gameObj->gridOffsetLeft + 560;
        }

        /*Show the two maps*/
        for(i = 0; i < gameObj->gridSizeX; i++)
        {
            for(j = 0; j < gameObj->gridSizeY; j++)
            { 
                /*Self map*/
                if(self->grid.cells[i][j].type == CELL_BOAT)
                    addToPrint(createPicture(leftOffsetSelf+(35*i), topOffset+(35*j), "images/sheep_idle.png"), PICTURE);

                if(opponent->grid.cells[i][j].hit == false)
                {
                    tempBtn = createBtn(leftOffsetOpponent+(35*i), topOffset+(35*j), 35, 35, BTN_GRAPHIC);
                    tempBtn->idleImage = MLV_load_image("images/fog.png");
                    tempBtn->hoverImage = MLV_load_image("images/target_green.png");
                    tempBtn->activeImage = MLV_load_image("images/target_green.png");
                    tempBtn->callback = mergeInts(i, j);

                    addToPrint(tempBtn, BUTTON);
                }
                else if(opponent->grid.cells[i][j].type == CELL_BOAT)
                {
                    addToPrint(createPicture(leftOffsetOpponent+(35*i), topOffset+(35*j), "images/sheep_idle.png"), PICTURE);
                }
            }
        }

        /*Save the position where the player has play*/
        callback = waitForAction();
        splitInts(callback, &targetX, &targetY);
        
        opponent->grid.cells[targetX][targetY].hit = true;

        /*Test to see if a boat has been hit*/
        for(i = 0; i < opponent->grid.nbrOfShips; i++)
        {
            if(!opponent->grid.ships[i].sinked)
            {
                sinkedCells = 0;

                for(j = 0; j < opponent->grid.ships[i].size; j++)
                {
                    if(opponent->grid.ships[i].direction == 'h' && opponent->grid.ships[i].posX + j == targetX && opponent->grid.ships[i].posY == targetY)
                    {
                        /*The clicked cell match this part of this boat*/

                        /*Set the ship's part as hit*/
                        opponent->grid.ships[i].hits[j] = true;

                        turnResult = HIT;           /*a boat got hit, it is now the current result of the turn*/
                        boatTouched = i;

                        /*We found what we searched for but we stay in the loop to keep counting sinked boats*/
                    }

                    /*Counter to know how many of the boat cells have been hits*/
                    if(opponent->grid.ships[i].hits[j] == true)
                    {
                        sinkedCells++;
                    }

                    /*Ship has sinked*/
                    if(sinkedCells == opponent->grid.ships[i].size)
                    {
                        sinkedBoats += 1;
                    }
                }
            }
            else
                sinkedBoats++;
        }

        if(sinkedBoats == opponent->grid.nbrOfShips)
            keepPlaying = false;                    /*All the boats have been sinked, let's stop playing*/
    
        if(turnResult == HIT)
        {
            /*Is the boat touched sinked?*/
            beenSinked = true;
            for(i = 0; i < opponent->grid.ships[boatTouched].size; i++)
            {
                if(!opponent->grid.ships[boatTouched].hits[i])
                {
                    beenSinked = false;
                    break;
                }
            }

            if(beenSinked)
                turnResult = SINKED;
        }

        /*Take action based on turn result*/
        switch(turnResult)
        {
            case MISS:
                addToPrint(createPicture(0, 0, "images/missedCaption.png"), PICTURE);
            break;
            case HIT:
                addToPrint(createPicture(0, 0, "images/hitCaption.png"), PICTURE);
            break;
            case SINKED:
                addToPrint(createPicture(0, 0, "images/sinkedCaption.png"), PICTURE);
            break;
        }

        printFrame();
        MLV_wait_seconds(3);

        /*Who's next ?*/
        if(gameObj->currTurn == 1)
            gameObj->currTurn = 2;
        else
            gameObj->currTurn = 1;

    }while(keepPlaying);

    printf("End of the game\n");
}