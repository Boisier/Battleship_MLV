#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

// Init the game and return the gameObject with default values
GameObj * initGame();

// Display Main menu
void mainMenu();


/********************************************************************************/
/***** Game functions definitions ***********************************************/
/********************************************************************************/

//Begin a new game
void startGame();

// Show the grid if it's mine or the ennemy's one
void printGrid (Grid g, bool self);

// The player give the position of his ships and their orientations, 
// call verifyPosition() to see if it's possible
void placeShip();

// Player give a position, 
void play();

// Verify the position if it's already used for the placment of the ship
int verifyPosition();


/********************************************************************************/
/***** Helper functions definitions *********************************************/
/********************************************************************************/

//Called when a function encountered a criticalError. Terminate the program.
void criticalError();

//Allocate encapsulate malloc to better handle failing behavior.
void * allocate(int size);

//reAllocate encapsulate malloc to better handle failing behavior.
void * reAllocate(void * var, int newSize);