/*Main includes*/
#include <stdio.h>
#include <MLV/MLV_all.h>

/*Include own headers*/
#include "headers/structs.h"
#include "headers/functions.h"

int main(int argc, char *argv[])
{
	/*Start Game*/
	gameObj = initGame();
	mainMenu();
	
	/*End Game*/
	quitGame();
	
	return 0;
}