#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
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
    criticalIfNull(var);                    //Did the allocation worked ?
    
    return var;                             //Yes, return newly allocated pointer
}

void * reAllocate(void * var, int newSize)  //realloc encapsulation with failing behavior handling
{
    var = realloc(var, newSize);            //realloc asked memory to the given pointer
    criticalIfNull(var);                    //Did the allocation worked ?

    return var;                             //Yes, return the pointer
}

void criticalIfNull(void * pointer)         //Throw a critical error and stop the application if the given pointer is null
{
    if(pointer == NULL)                     //Is the given pointer NULL?
        throwCriticalError();               //Yes, then stop all
}

void cleanScreen()  //Roll back the screen to it's default state
{
    MLV_Image * bckg = MLV_load_image("images/woodenBackground.png");
    MLV_draw_image(bckg, 0, 0);   //Replace the entire image with the wooden background
}

MLV_Color rgba(int r, int g, int b, int a)  //Encapsulate MLV_rgba into rgba in order to simplify the command
{
    return MLV_rgba(r, g, b, a);
}

int percent(float percent, char direction)              //return a percentage based on the window size
{
    if(direction == 'w')
        return (gameObj->wWidth / 100.0) * percent;
    else if(direction == 'h')
        return (gameObj->wHeight / 100.0) * percent;
    else
        return 0;
}

int percentOffset(float p, char direction, int offset) //return a percentage based on the window size and add the offset value to the result
{
    return percent(p, direction) + offset;
}