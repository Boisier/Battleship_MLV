#include <stdio.h>
#include <stdlib.h> 
#include "../headers/structs.h"
#include "../headers/functions.h"

void criticalError()
{
    printf("A critical error occured and the program had to stop.\n");
    exit(0);
}

void * allocate(int size)
{
    void * var = malloc(size);

    if(var == NULL)
        criticalError();
    
    return var;
}

void * reAllocate(void * var, int newSize)
{
    var = realloc(var, newSize);

    if(var == NULL)
        criticalError();

    return var;
}