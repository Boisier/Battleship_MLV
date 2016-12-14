#include <stdio.h>
#include <stdlib.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

void printFrame()                               //Iterate through the gameObj and display all elements.
{
    int nbrToPrint = gameObj->nbrToPrint;
    int i;
    printElement el;

    cleanScreen();                              //First we clean the screen

    for(i = 0; i < nbrToPrint; i++)             //We iterate over all the element to print
    {
        el = gameObj->toPrint[i];               //get the element
                                                //Then print it with the apropriate function
        if(el.type == 'b')
            printBtn(el.element, el.state);
        else if(el.type == 'p')
            printPicture(el.element);
    }

    MLV_actualise_window();                     //finaly we actualise the window();
    //MLV_wait_milliseconds(15);
}

printElement * addToPrint(void * element, char type)
{
    criticalIfNull(element);                    //We make sure no NULL pointer get's in the loop

    int newSize = (gameObj->nbrToPrint + 1) * sizeof(printElement); //New size of the toPrint array
    gameObj->toPrint = reAllocate(gameObj->toPrint, newSize);       //increase size of the toPrint array

    printElement * newEl = allocate(sizeof(printElement));                                           //new printElement to add
    newEl->element = element;                                       //assign given element
    newEl->type = type;                                             //assign given element type

    gameObj->toPrint[gameObj->nbrToPrint] = *newEl;                 //Insert newly created printElement in the array toPrint
    gameObj->nbrToPrint++;                                          //Increment the nbr of element

    return &gameObj->toPrint[gameObj->nbrToPrint-1];                                                   //And return the newly created element so it can be edited
}

void cleanToPrint()                                                 //Empty the list of element to print
{
    free(gameObj->toPrint);                                         //Free the memory used by the printElements, but do not free the elements. Other functions might still need them.
    gameObj->nbrToPrint = 0;                                        //Reset the number of elements to print;
}





void printBtn(struct Button * btn, char state)  //Print a given button at the current state
{
    MLV_Color backColor;                        //Variables who change depdning of the state of the button
    MLV_Color textColor;
    MLV_Image * image;

    if(btn->type == 'g')                        //Is the button a graphical one?
    {                                           //Yes, let's select the image to show based on the state
        if(state == 'h')
            image = btn->hoverImage;            //Hover state
        else if(state == 'a')
            image = btn->activeImage;           //Active state
        else
            image = btn->idleImage;             //Idle state
        
        MLV_draw_image(image, btn->x, btn->y);  //print the button
    }
    else                                        //Is the button a plain color one?
    {
        if(state == 'h')                        //Set hover state properties
        {        
            backColor = btn->hoverBackColor;
            textColor = btn->hoverTextColor;
        }
        else if(state == 'a')                   //Set active state properties
        {   
            backColor = btn->activeBackColor;
            textColor = btn->activeTextColor;
        }
        else                                    //Set idle state properties
        {
            backColor = btn->idleBackColor;
            textColor = btn->idleTextColor;
        }
        
        MLV_draw_text_box(                      //print button
            btn->x, btn->y, 
            btn->width, btn->height, 
            btn->text, 
            12, 
            rgba(0, 0, 0, 0), textColor, backColor,
            MLV_TEXT_CENTER,
            MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    }
}


void printPicture(struct Picture * pict)
{
    MLV_draw_image(pict->image, pict->x, pict->y);
}