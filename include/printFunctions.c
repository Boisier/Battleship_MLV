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
        if(gameObj->toPrint[i].display)
        {
            el = gameObj->toPrint[i];           /*get the element*/


            switch(el.type)
            {          /*Then print it with the apropriate function*/
                 case BUTTON: printBtn(el.element.btn, el.state); break;
                case PICTURE: printPicture(el.element.pict); break;
                case TEXTBOX: printTextBox(el.element.tB, el.state); break;
                case NUMBERBOX: printNumberBox(el.element.nB, el.state); break;
                case TEXT: printText(el.element.txt, el.state); break;
            }
        }
    }

    MLV_actualise_window();                     /*finaly we actualise the window();*/
    /*MLV_wait_milliseconds(15);*/
}

PrintElement * addToPrint(void * element, enum elType type)
{
    int newSize;
    PrintElement newEl;

    criticalIfNull(element);                    /*We make sure no NULL pointer get's in the loop*/


    /*newEl = allocate(sizeof(PrintElement));    */     /*new printElement to add*/
    
    newEl.type = type;                             /*assign given element type*/
    
    switch(type)          
    {
         case BUTTON: newEl.element.btn = element; break;
        case PICTURE: newEl.element.pict = element; break;
        case TEXTBOX: newEl.element.tB = element; break;
        case NUMBERBOX: 
            newEl.element.nB = element; 
            addToPrint(newEl.element.nB->plusBtn, BUTTON);
            addToPrint(newEl.element.nB->lessBtn, BUTTON);
        break;
        case TEXT: newEl.element.txt = element; break;
    }

    newEl.display = true;                          /*Set the element as being displayed*/                   

    if(type == TEXTBOX)
        newEl.state = BLUR;
    else
        newEl.state = IDLE;
    
    newEl.canFade = false;

    newSize = (gameObj->nbrToPrint + 1) * sizeof(PrintElement); /*New size of the toPrint array*/

    if(gameObj->nbrToPrint == 0)
        gameObj->toPrint = allocate(newSize);       /*increase size of the toPrint array*/
    else
        gameObj->toPrint = reAllocate(gameObj->toPrint, newSize); 

    gameObj->toPrint[gameObj->nbrToPrint] = newEl;                 /*Insert newly created printElement in the array toPrint*/
    gameObj->nbrToPrint++;                                          /*Increment the nbr of element*/

    return &gameObj->toPrint[gameObj->nbrToPrint-1];                /*And return the newly created element so it can be edited*/
}

void cleanToPrint()                                                 /*Empty the list of element to print*/
{
    int i;

    if(gameObj->nbrToPrint != 0)
    {
        for(i = 0; i < gameObj->nbrToPrint; i++)
        {
            switch(gameObj->toPrint[i].type)          /*Then print it with the apropriate function*/
            {
                case BUTTON: freeBtn(gameObj->toPrint[i].element.btn); break;
                case PICTURE: freePicture(gameObj->toPrint[i].element.pict); break;
                case TEXTBOX: freeTextBox(gameObj->toPrint[i].element.tB); break;
                case NUMBERBOX: freeNumberBox(gameObj->toPrint[i].element.nB); break;
                case TEXT: freeText(gameObj->toPrint[i].element.txt); break;
            }
        }

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

    if(btn->type == BTN_GRAPHIC)                        /*Is the button a graphical one?*/
    {                                           /*Yes, let's select the image to show based on the state*/
        if(btn->canToggle)
        {
            if(state == HOVER && !btn->checked)
                image = btn->hoverImage;            /*Hover state*/
            else if(state == ACTIVE || btn->checked)
                image = btn->activeImage;           /*Active state*/
            else if(!btn->checked)
                image = btn->idleImage;             /*Idle state*/
        }
        else
        {
            if(state == HOVER || state == FORCEHOVER)
                image = btn->hoverImage;            /*Hover state*/
            else if(state == ACTIVE)
                image = btn->activeImage;           /*Active state*/
            else
                image = btn->idleImage;             /*Idle state*/
        }
        
        if(image != NULL)
            MLV_draw_image(image, btn->x, btn->y);  /*print the button*/
    }
    else                                        /*Is the button a plain color one?*/
    {
        if(state == HOVER || state == FORCEHOVER)                        /*Set hover state properties*/
        {        
            backColor = btn->hoverBackColor;
            textColor = btn->hoverTextColor;
        }
        else if(state == ACTIVE)                   /*Set active state properties*/
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
    char textToPrint[102];
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

    if(state == FOCUS && tB->cursorShown)         /*Shall we display the cursor?*/
        strcat(textToPrint, "|");               /*Let's display the cursor*/

    /*Finaly, draw the input box text*/
    MLV_draw_text_box_with_font(tB->x, tB->y, tB->width, tB->height, textToPrint, gameObj->inputFont, 9, rgba(0, 0, 0, 0), textColor, rgba(0, 0, 0, 0), MLV_TEXT_LEFT, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER); /*Finaly, let's write the content*/
}

void printNumberBox(struct NumberBox * nB, char state)
{
    char str[10];

    sprintf(str, "%d", nB->value);

    MLV_draw_image(nB->backImage, nB->x+45, nB->y);
    MLV_draw_text_box_with_font(nB->x+44, nB->y+1, 79, 39, str, gameObj->inputFont, 9, rgba(0, 0, 0, 0), MLV_COLOR_WHITE, rgba(0, 0, 0, 0), MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER); /*Finaly, let's write the content*/
}


void printText(struct Text * txt, char state)          /*Print given Text elemnt on the screen*/
{
    MLV_Font * font;

    if(txt->size == 's')
        font = gameObj->inputFont;
    else if(txt->size == 'm')
        font = gameObj->waitFont;
    else 
        font = gameObj->bigFont;

    MLV_draw_text_box_with_font(txt->x, txt->y, txt->width, txt->height, txt->content, font, 9, rgba(0, 0, 0, 0), gameObj->defaultInputColor, rgba(0, 0, 0, 0), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}