//Main includes
#include <stdio.h>
#include <MLV/MLV_all.h>

//Include own headers
#include "headers/structs.h"
#include "headers/functions.h"

int main(int argc, char *argv[])
{
	gameObj = initGame();
	mainMenu(gameObj);

	MLV_wait_seconds(10);
	return 0;
}