#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

GameObj * initGame();                      // Init the game and return the gameObject with default values

void mainMenu(struct GameObj * gameObj);            // Display Main menu



/********************************************************************************/
/***** Game functions definitions ***********************************************/
/********************************************************************************/

//Begin a new game
void startGame();

// Show the grid if it's mine or the ennemy's one
void printGrid (struct Grid g, bool self);

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
void throwCriticalError();

//Allocate encapsulate malloc to better handle failing behavior.
void * allocate(int size);

//reAllocate encapsulate malloc to better handle failing behavior.
void * reAllocate(void * var, int newSize);

//erase everything on the screen but don't refresh the window
void cleanScreen(struct GameObj * gameObj);

//MLV_rgba encapsulation for simpler syntax 
MLV_Color rgba(int r, int g, int b, int a);