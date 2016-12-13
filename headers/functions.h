#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

GameObj * initGame();                      // Init the game and return the gameObject with default values

void mainMenu();            // Display Main menu



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

//Throw a critical error and stop the application if the given pointer is null
void criticalIfNull(void * pointer);

//erase everything on the screen but don't refresh the window
void cleanScreen(struct GameObj * gameObj);

//MLV_rgba encapsulation for simpler syntax 
MLV_Color rgba(int r, int g, int b, int a);

int percent(float percent, char direction);//return a percentage based on the window size
int percentOffset(float percent, char direction, int offset); //return a percentage based on the window size and add the offset value to the result






/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type); //Create a Btn and assign specified values





/********************************************************************************/
/***** Printing functions definitions *******************************************/
/********************************************************************************/

void printFrame();                                  //print the currentFrame

printElement * addToPrint(void * element, char type);	//Add the given element to the list of Elements to print

void printBtn(struct Button * btn, char state);     //print the given btn at the given state