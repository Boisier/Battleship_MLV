 #pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

void initGame();       		        /* Init the game and return the gameObject with default values*/

void mainMenu();            	    /* Display Main menu*/

void displayRules();                /* DIsplay the rules */

void choicePlayers();               /* Screen with choice one or two players*/

void initNewGame(); 				/*Init the game for one or two player*/

void startGame();					/*Set up a new game and start it*/

void createPlayer(int playerID, char * playerName, enum playerType type);	/*Generate the data needed for the player*/

int setUpPlayer(int playerID);		/*Ask player to place its boats on the map*/

void inGame();                      /* Player give a position, */

void replay();						/*Restart a new game with the exact same parameters*/

void endGame();						/*clean up last game data and redirect to main menu*/





/********************************************************************************/
/***** Core functions definitions ***********************************************/
/********************************************************************************/

int waitForAction(); 		                                    /*Keep application idle until a button is pressed and a callback value returned. It handle mouse hovering */

bool isCursorOnBtn(Button * Btn, int mouseX, int mouseY);		/*Check if the cursor is on the given Button. Return true if it is, false otherwise*/

bool isCursorOnInput(TextBox * input, int mouseX, int mouseY);	/*check if cursor is on textBox. Return true if it is, false otherwise*/

void updateTextBox(int inputPos, MLV_Keyboard_button keyPressed, int unicode); /*Update the content of the given textBox*/

void incrementNumberBox(void * nB);								/*if Possible, increment by 1 the value of the given numberBox*/

void decrementNumberBox(void * nB);								/*if possible, decrement by 1 the value of the given numberBox*/

void quitGame();												/*Clean up the used memory, then close the application*/

void waitFor(char type);										/*Display a wait screen for the player or the computer*/

void waitForPlayer();											/*call waitFor() to display a wait screen for the player*/

void waitForComputer();											/*call waitFor() to display a wait screen for the computer*/

void createBoardGame(int w, int h);								/*Generate the background image for the game with the given grid size*/

void createGrid(char side, int w, int h, int topOffset, int topStep, int leftOffset, int leftStep, MLV_Image * mainBckg, MLV_Image * dirtBloc); /*Print a grid on the given image*/

bool addBoat(int boatX, int boatY, int boatSize, char boatDirection);	/*Place a boat on the map for the current player and return true if the action was successfull*/

void printBoatShadow(int posInToPrint);							/*Display the fade position on the grid. Used when placing the boats*/

int hitResult(int targetX, int targetY, Player * self, Player * opponent);	/*Return the result of the player/computer action*/





/********************************************************************************/
/***** Helper functions definitions *********************************************/
/********************************************************************************/

void throwCriticalError();                              /*Called when a function encountered a criticalError. Terminate the program.*/

void criticalIfNull(void * pointer);                    /*Throw a critical error and stop the application if the given pointer is null*/

void * allocate(int size);                              /*Allocate encapsulate malloc to better handle failing behavior.*/

void * reAllocate(void * var, int newSize);             /*reAllocate encapsulate malloc to better handle failing behavior.*/

void cleanScreen();                                     /*erase everything on the screen but don't refresh the window*/

MLV_Color rgba(int r, int g, int b, int a);             /*MLV_rgba encapsulation for simplier syntax */

int percent(float percent, char direction);             /*return a percentage based on the window size*/
int percentOffset(float percent, char direction, int offset); /*return a percentage based on the window size and add the offset value to the result*/

int mergeInts(int first, int second);	                /*Merge two int into one int. Ints passed as parameters cannot exceed 65535*/

void splitInts(int merged, int *first, int*second);	    /*Split two int merged with the mergedInts function*/

void printConsumption();	                            /*This function print the current consumption of RAM and CPU of the application*/

void resetPlayerGrid(int playerID);		                /*Reset the grid of the given Player */

void resetPlayer(Player * player);		                /*Reset all informations about the given Player*/





/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

/*Create the desired element with the given parameters*/
Button * createBtn(int x, int y, int width, int height, enum btnType type);
Picture * createPicture(int x, int y, char fileURL[]);
Text * createText(int x, int y, int width, int height, char size, char * content);
TextBox * createTextBox(int x, int y, int width, int height, char type, char placeHolder[100]);
NumberBox * createNumberBox(int x, int y, int defaultVal, int minVal, int maxVal);





/********************************************************************************/
/***** Element printing functions ***********************************************/
/********************************************************************************/

void printFrame();                                  	        /*print the currentFrame*/

PrintElement * addToPrint(void * element, enum elType type);    /*Add the given element to the toPrint array*/

void cleanToPrint();									        /*Empty th elist of element to print*/

/*Print the given element at the current state if applicable*/
void printBtn(struct Button * btn, char state);
void printPicture(struct Picture * picture);
void printTextBox(struct TextBox * tB, char state);
void printNumberBox(struct NumberBox * nB, char state);
void printText(struct Text * txt, char state);





/********************************************************************************/
/***** Element free functions ***************************************************/
/********************************************************************************/

/*Properly free the given element*/
void freeBtn(Button * btn);
void freePicture(Picture * pic);
void freeTextBox(TextBox * tB);
void freeNumberBox(NumberBox * nB);
void freeText(Text * txt);