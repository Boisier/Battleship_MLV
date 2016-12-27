#include <stdio.h>
#include <stdlib.h>  
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

void printFrame()                               /*Iterate through the gameObj and display all elements.*/
{
    int nbrToPrint = gameObj->nbrToPrint;
    int i;
    PrintElement el;

    cleanScreen();                              /*First we clean the screen*/

    for(i = 0; i < nbrToPrint; i++)             /*We iterate over all the element to print*/
    {
        el = gameObj->toPrint[i];               /*get the element*/


        if(el.type == 'b')                      /*Then print it with the apropriate function*/
            printBtn(el.element, el.state);
        else if(el.type == 'p')
            printPicture(el.element);
        else if(el.type == 'i')
            printTextBox(el.element, el.state);
    }

    MLV_actualise_window();                     /*finaly we actualise the window();*/
    /*MLV_wait_milliseconds(15);*/
}

PrintElement * addToPrint(void * element, char type)
{
    int newSize;
    PrintElement * newEl;

    criticalIfNull(element);                    /*We make sure no NULL pointer get's in the loop*/

    newSize = (gameObj->nbrToPrint + 1) * sizeof(PrintElement); /*New size of the toPrint array*/

    if(gameObj->nbrToPrint == 0)
        gameObj->toPrint = allocate(newSize);       /*increase size of the toPrint array*/
    else
        gameObj->toPrint = reAllocate(gameObj->toPrint, newSize); 

    newEl = allocate(sizeof(PrintElement));          /*new printElement to add*/
    newEl->element = element;                                       /*assign given element*/
    newEl->type = type;                                             /*assign given element type*/
    newEl->state = 'i';
    newEl->canFade = false;

    gameObj->toPrint[gameObj->nbrToPrint] = *newEl;                 /*Insert newly created printElement in the array toPrint*/
    gameObj->nbrToPrint++;                                          /*Increment the nbr of element*/

    free(newEl);

    return &gameObj->toPrint[gameObj->nbrToPrint-1];                /*And return the newly created element so it can be edited*/
}

void cleanToPrint()                                                 /*Empty the list of element to print*/
{
    if(gameObj->nbrToPrint != 0)
    {
       free(gameObj->toPrint);                                         /*Free the memory used by the printElements, but do not free the elements. Other functions might still need them.*/
      gameObj->toPrint = NULL;
      gameObj->nbrToPrint = 0;                                        /*Reset the number of elements to print*/
    }
}





void printBtn(struct Button * btn, char state)  /*Print a given button at the current state*/
{
    MLV_Color backColor;                        /*Variables who change depdning of the state of the button*/
    MLV_Color textColor;
    MLV_Image * image;

    if(btn->type == 'g')                        /*Is the button a graphical one?*/
    {                                           /*Yes, let's select the image to show based on the state*/
        if(state == 'h' || state == 'f')
            image = btn->hoverImage;            /*Hover state*/
        else if(state == 'a')
            image = btn->activeImage;           /*Active state*/
        else
            image = btn->idleImage;             /*Idle state*/
        
        if(image != NULL)
            MLV_draw_image(image, btn->x, btn->y);  /*print the button*/
    }
    else                                        /*Is the button a plain color one?*/
    {
        if(state == 'h' || state == 'f')                        /*Set hover state properties*/
        {        
            backColor = btn->hoverBackColor;
            textColor = btn->hoverTextColor;
        }
        else if(state == 'a')                   /*Set active state properties*/
        {   
            backColor = btn->activeBackColor;
            textColor = btn->activeTextColor;
        }
        else                                    /*Set idle state properties*/
        {
            backColor = btn->idleBackColor;
            textColor = btn->idleTextColor;
        }
        
        MLV_draw_text_box_with_font(                      /*print button*/
            btn->x, btn->y, 
            btn->width, btn->height, 
            btn->text, 
            gameObj->inputFont,
            12, 
            rgba(0, 0, 0, 0), textColor, backColor,
            MLV_TEXT_CENTER,
            MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    }
}


void printPicture(struct Picture * pict)        /*Print a given picture element on the screen */
{
    MLV_draw_image(pict->image, pict->x, pict->y);
}

void printTextBox(struct TextBox * tB, char state)          /*Print given textBox on the screen*/
{
    char textToPrint[101];
    MLV_Color textColor;

    if(tB->type == 'g')                        /*Pint the image or the color depending if it's a graphical or plain color text Box*/
        MLV_draw_image(tB->backImage, tB->x+tB->imgOffsetX, tB->y+tB->imgOffsetY);
    else                                        
        MLV_draw_filled_rectangle(tB->x, tB->y, tB->width, tB->height, tB->backColor);

    if(strlen(tB->content) == 0)    /*No content, we print the placeholder*/
    {
        textColor = tB->placeHolderColor;       /*Set placeholder color as text color*/
        strcpy(textToPrint, tB->placeHolder);   /*set place holder as text to show*/
    }
    else
    {
        textColor = tB->textColor;              /*Set standard color as text color*/
        strcpy(textToPrint, tB->content);       /*Set text box content as text to show*/
    }

    if(clock() - tB->lastCursorSwitch > 500000) /*How long since last cursor tick?*/
    {
        tB->lastCursorSwitch = clock();         /*long enough*/

        if(tB->cursorShown)
            tB->cursorShown = false;            /*Hide the cursor*/
        else
            tB->cursorShown = true;             /*show the cursor*/
    }

    if(state == 'f' && tB->cursorShown)         /*Shall we display the cursor?*/
        strcat(textToPrint, "|");               /*Let's display the cursor*/

    /*Finaly, draw the input box text*/
    MLV_draw_text_box_with_font(tB->x, tB->y, tB->width, tB->height, textToPrint, gameObj->inputFont, 9, rgba(0, 0, 0, 0), textColor, rgba(0, 0, 0, 0), MLV_TEXT_LEFT, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER); /*Finaly, let's write the content*/
}