/*Main includes*/
#include <stdio.h>
#include <MLV/MLV_all.h>

/*Include Battlesheep headers*/
#include "headers/structs.h"
#include "headers/functions.h"

int main(int argc, char *argv[])
{
    	/*The main is only used to call the initialization of the game and launch the mainMenu().
	 *The rest of the actions ar mainly performed in the file mainFunctions.c 
	 */

	/*Start Game*/
	initGame();
	mainMenu();
	
	/*End Game*/
	quitGame();
	
    return 0;
}
