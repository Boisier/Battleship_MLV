//Main includes
#include <stdio.h>
#include <MLV/MLV_all.h>

//Include own headers
#include "headers/structs.h"
#include "headers/functions.h"

int main(int argc, char *argv[])
{
	//Game has been lauched;

	GameObj gameObj = initGame();

	gameObj.currTurn = 0;
	printf("%d\n", gameObj.currTurn);
	printf("success\n");

	return 0;
 }