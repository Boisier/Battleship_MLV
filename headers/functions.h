#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

GameObj * initGame();       /* Init the game and return the gameObject with default values*/

void mainMenu();            /* Display Main menu*/

void choicePlayers();		/* Screen with choice one or two players*/

void initNewGame(int nbrPlayer); /*Init the game for one or two player*/



/********************************************************************************/
/***** Core functions definitions ***********************************************/
/********************************************************************************/

char waitForAction(); 		/*Keep application idle until a button is pressed and a callback value returned. It handle mouse hovering */

bool isCursorOnBtn(Button * Btn, int mouseX, int mouseY);

bool isCursorOnInput(TextBox * input, int mouseX, int mouseY);	/*check if cursor is on textBox. Return true if it is, false otherwise*/

void updateTextBox(int inputPos, MLV_Keyboard_button keyPressed, int unicode);

void quitGame();





/********************************************************************************/
/***** Game functions definitions ***********************************************/
/********************************************************************************/

/*Begin a new game*/
void startGame();

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

/*Print a msg in the console. Used as a callBack tester*/
void clicked();

void printConsumption();	/*This function print the current consumption of RAM and CPU of the application*/



/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type); /*Create a Btn and assign specified values*/

Picture * createPicture(int x, int y, char fileURL[]);				/*Create a picture and assign specified values*/

TextBox * createTextBox(int x, int y, int width, int height, char type, char placeHolder[100]);


/********************************************************************************/
/***** Printing functions definitions *******************************************/
/********************************************************************************/

void printFrame();                                  	/*print the currentFrame*/

PrintElement * addToPrint(void * element, char type);	/*Add the given element to the list of Elements to print*/

void cleanToPrint();									/*Empty th elist of element to print*/

void printBtn(struct Button * btn, char state);    		/*print the given btn at the given state*/

void printPicture(struct Picture * picture);			/*Print the given picture to it's set position*/

void printTextBox(struct TextBox * tB, char state);					/*Print given textBox on the screen*/