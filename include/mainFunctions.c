#include <stdio.h>
#include <stdlib.h> 
#include "../headers/structs.h"
#include "../headers/functions.h"

//initGame() generate the gameObj
GameObj * initGame()
{
    GameObj * gameObj = allocate(sizeof(GameObj));  //Define gameObj variable

    gameObj.currTurn = 0;                           //Set current turn as 0

    return gameObj;
}