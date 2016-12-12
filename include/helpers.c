#include <stdio.h>
#include <stdlib.h> 
#include "../headers/structs.h"
#include "../headers/functions.h"

void isMemoryOK(void *var)
{
    if(var == NULL)
    {
        printf("Une erreur critique est survenue.\nLe programme va maintenant se fermer.");
        exit(0);
    }
}