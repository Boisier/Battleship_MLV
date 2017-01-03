#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

GameObj * initGame();       		/* Init the game and return the gameObject with default values*/

void mainMenu();            		/* Display Main menu*/

void choicePlayers();				/* Screen with choice one or two players*/

void initNewGame(); 				/*Init the game for one or two player*/

void startGame(int nbrPlayer);		/*Set up a new game and start it*/

void createPlayer(int playerID, char * playerName, enum playerType type);	/*Generate the data needed for the player*/

void setUpPlayer(int playerID);		/*Ask player to place its boats on the map*/

bool addBoat(int boatX, int boatY, int boatSize, char boatDirection);	/*Place a boat on the map for the current player and return true if the action was successfull*/






/********************************************************************************/
/***** Core functions definitions ***********************************************/
/********************************************************************************/

int waitForAction(); 		/*Keep application idle until a button is pressed and a callback value returned. It handle mouse hovering */

bool isCursorOnBtn(Button * Btn, int mouseX, int mouseY);

bool isCursorOnInput(TextBox * input, int mouseX, int mouseY);	/*check if cursor is on textBox. Return true if it is, false otherwise*/

void updateTextBox(int inputPos, MLV_Keyboard_button keyPressed, int unicode);

void quitGame();

void createBoardGame(int w, int h);	/**/

void createGrid(char side, int w, int h, int topOffset, int topStep, int leftOffset, int leftStep, MLV_Image * mainBckg, MLV_Image * dirtBloc);







/********************************************************************************/
/***** Game functions definitions ***********************************************/
/********************************************************************************/


/* Show the grid if it's mine or the ennemy's one*/
void printGrid (struct Grid g, bool self);

/* The player give the position of his ships and their orientations,*/ 
/* call verifyPosition() to see if it's possible*/
void placeShip();

/* Player give a position, */
void play();

/* Verify the position if it's already used for the placment of the ship*/
int verifyPosition();


/********************************************************************************/
/***** Helper functions definitions *********************************************/
/********************************************************************************/

/*Called when a function encountered a criticalError. Terminate the program.*/
void throwCriticalError();

/*Allocate encapsulate malloc to better handle failing behavior.*/
void * allocate(int size);

/*reAllocate encapsulate malloc to better handle failing behavior.*/
void * reAllocate(void * var, int newSize);

/*Free a button and all linked data*/
void freeBtn(Button * btn);

/*Free a picture and all linked data*/
void freePicture(Picture * pic);

/*Free a text box and all linked data*/
void freeTextBox(TextBox * tB);

/*Throw a critical error and stop the application if the given pointer is null*/
void criticalIfNull(void * pointer);

/*erase everything on the screen but don't refresh the window*/
void cleanScreen();

/*MLV_rgba encapsulation for simpler syntax */
MLV_Color rgba(int r, int g, int b, int a);

int percent(float percent, char direction);/*return a percentage based on the window size*/
int percentOffset(float percent, char direction, int offset); /*return a percentage based on the window size and add the offset value to the result*/

void clicked();				/*Print a msg in the console. Used as a callBack tester*/

int mergeInts(int first, int second);	/*Merge two int into one int. Ints passed as parameters cannot exceed 65535*/

void splitInts(int merged, int *first, int*second);	/*Split two int merged with the mergedInts function*/

void printConsumption();	/*This function print the current consumption of RAM and CPU of the application*/



/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, enum btnType type); /*Create a Btn and assign specified values*/

Picture * createPicture(int x, int y, char fileURL[]);				/*Create a picture and assign specified values*/

TextBox * createTextBox(int x, int y, int width, int height, char type, char placeHolder[100]);


/********************************************************************************/
/***** Printing functions definitions *******************************************/
/********************************************************************************/

void printFrame();                                  	/*print the currentFrame*/

PrintElement * addToPrint(void * element, enum elType type);	/*Add the given element to the list of Elements to print*/

void cleanToPrint();									/*Empty th elist of element to print*/

void printBtn(struct Button * btn, char state);    		/*print the given btn at the given state*/

void printPicture(struct Picture * picture);			/*Print the given picture to it's set position*/

void printTextBox(struct TextBox * tB, char state);					/*Print given textBox on the screen*/

void printBoatShadow(int posInToPrint);