#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

void waitForAction() 		/*Keep application idle until a button callBack is fired. It handle mouse hovering */
{
    int mouseX, mouseY, i;
    MLV_Event event;
    MLV_Button_state cursorState;
    void (*callbackFunction)() = NULL;

    do                                                          /*Loop until the user press a btn*/
    {
        event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mouseX, &mouseY, NULL, &cursorState);    /*Get last event*/
        MLV_flush_event_queue();

        if( event == MLV_MOUSE_MOTION )                         /*Is this a movement of the mouse?*/
        {
            for(i = 0; i < gameObj->nbrToPrint; i++)            /*iterate through all the element to print*/
            {
                if(gameObj->toPrint[i].type == 'b')             /*is this a button ?*/
                {
                    if(isCursorOnBtn(((Button *)gameObj->toPrint[i].element), mouseX, mouseY))  /*Is the cursoron this button?*/
                    {    
                        gameObj->toPrint[i].state = 'h';        /*yes, set state as hover*/
                        /*printf("%d\n", (int)clock());*/
                    }
                    else
                        gameObj->toPrint[i].state = 'i';        /*no, make sure state is idle*/
                }
            }
        }
        else if(event == MLV_MOUSE_BUTTON)                      /*Is this a click of the mouse ?*/
        {
            for(i = 0; i < gameObj->nbrToPrint; i++)            /*iterate through all the element to print*/
            {
                if(gameObj->toPrint[i].type == 'b')             /*Is this a button ?*/
                {
                    if(isCursorOnBtn(((Button *)gameObj->toPrint[i].element), mouseX, mouseY)) /*is the cursor on the Btn?*/
                    {
                        gameObj->toPrint[i].state = 'a';

                        if(((Button *)gameObj->toPrint[i].element)->callback != NULL && cursorState == MLV_RELEASED)   /*Is the callback function defined ?*/
                        {
                            callbackFunction = ((Button *)gameObj->toPrint[i].element)->callback;    /*Yes, set the callback and stop the loop*/
                        }
                    }
                }
            }
        }

        printFrame();					/*Update window*/

    } while(callbackFunction == NULL);

    callbackFunction();
}

bool isCursorOnBtn(Button * Btn, int mouseX, int mouseY)	/*check if cursor is on Button. Return true if it is, false otherwise*/
{
    int x = Btn->x;                     /*Get X position of the button*/
    int y = Btn->y;                     /*Get Y position of of the button*/
    int width = Btn->width;             /*Get width of the button*/
    int height = Btn->height;           /*Get height of the button*/

    if(mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    else
        return false;
}

void quitGame()                         /*This function properly end the game*/
{
    MLV_free_window();                  /*Close the window*/
    MLV_free_all();
}