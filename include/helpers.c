#include <stdio.h>
#include <stdlib.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

void throwCriticalError()                   //Clean the program then terminate it
{
    MLV_free_window();                      //Free all MLV data that may be present

    printf("A critical error occured and the program had to stop.\n");  //Throw error message
     exit(0);                               //End the program
}

void * allocate(int size)                   //malloc encapsulation with failing behavior handling
{
    void * var = malloc(size);              //Allocate asked memory

    if(var == NULL)                         //Did the allocation worked ?
        throwCriticalError();               //No, critical error
    
    return var;                             //Yes, return newly allocated pointer
}

void * reAllocate(void * var, int newSize)  //realloc encapsulation with failing behavior handling
{
    var = realloc(var, newSize);            //realloc asked memory to the given pointer

    if(var == NULL)                         //Did the allocation worked ?
        throwCriticalError();               //No, critical error

    return var;                             //Yes, return the pointer
}

void cleanScreen(struct GameObj * gameObj)  //Roll back the screen to it's default state
{
     MLV_draw_filled_rectangle(0, 0, gameObj->wWidth, gameObj->wHeight, MLV_COLOR_BLACK);   //Replace the entire image with a black rectangle
}

MLV_Color rgba(int r, int g, int b, int a)  //Encapsulate MLV_rgba into rgba in order to simplify the command
{
    return MLV_rgba(r, g, b, a);
}