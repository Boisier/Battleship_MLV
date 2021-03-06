#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

void throwCriticalError()                   /*Clean the program then terminate it*/
{
    MLV_free_window();                      /*Free all MLV data that may be present*/

    printf("A critical error occured and the program had to stop.\n");  /*Throw error message*/
     exit(0);                               /*End the program*/
}

void criticalIfNull(void * pointer)         /*Throw a critical error and stop the application if the given pointer is null*/
{
    if(pointer == NULL)                     /*Is the given pointer NULL?*/
        throwCriticalError();               /*Yes, then stop all*/
}

void * allocate(int size)                   /*malloc encapsulation with failing behavior handling*/
{
    void * var = malloc(size);              /*Allocate asked memory*/
    criticalIfNull(var);                    /*Did the allocation worked ?*/
    
    return var;                             /*Yes, return newly allocated pointer*/
}

void * reAllocate(void * var, int newSize)  /*realloc encapsulation with failing behavior handling*/
{
    var = realloc(var, newSize);            /*realloc asked memory to the given pointer*/
    criticalIfNull(var);                    /*Did the allocation worked ?*/

    return var;                             /*Yes, return the pointer*/
}

void cleanScreen()                          /*Roll back the screen to it's default state*/
{
    if(gameObj->gameState == 'a')
        MLV_draw_image(gameObj->gameBoard, 0, 0);             /*Replace the entire image with the wooden background*/
    else 
        MLV_draw_image(gameObj->woodBckg, 0, 0);             /*Replace the entire image with the wooden background*/

}

MLV_Color rgba(int r, int g, int b, int a)  /*Encapsulate MLV_rgba into rgba in order to simplify the command*/
{
    return MLV_rgba(r, g, b, a);
}

int percent(float percent, char direction)  /*return a percentage based on the window size*/
{
    if(direction == 'w')
        return (gameObj->wWidth / 100.0) * percent;
    else if(direction == 'h')
        return (gameObj->wHeight / 100.0) * percent;
    else
        return 0;
}

int percentOffset(float p, char direction, int offset) /*return a percentage based on the window size and add the offset value to the result*/
{
    return percent(p, direction) + offset;
}

/*Merge two int into one int*/
int mergeInts(int first, int second)
{
    return ((first+1) << 16) | (second+1);
}

/*Split one int two int*/
void splitInts(int merged, int *first, int*second)
{
    *first = ((merged >> 16) & 0xFFFF)-1;
    *second = (merged & 0xFFFF)-1;
}

/*Reset the grid of the player*/
void resetPlayerGrid(int playerID)
{
    int i, j, boatsNbr = 0;
    Grid * grid = NULL;

    if(playerID == 1)
        grid = &gameObj->player1.grid;
    else
        grid = &gameObj->player2.grid;
    
    for(i = 0; i < gameObj->gridSizeX; i++)
    {
        for(j = 0; j < gameObj->gridSizeY; j++)
        {
            grid->cells[i][j].type = CELL_EMPTY;
            grid->cells[i][j].hit = false;
        }
    }

    free(grid->ships);
    grid->nbrOfShips = 0;

    for(i = 1; i < 6; i++)
        boatsNbr += gameObj->nbrShips[i];

    grid->ships = allocate(sizeof(Ship) * boatsNbr);
}
