#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

char waitForAction() 		/*Keep application idle until a button callBack is fired. It handle mouse hovering */
{
    int mouseX, mouseY, i, unicode;
    MLV_Event event;
    MLV_Button_state state;
    MLV_Keyboard_button keyPressed;
    char callbackValue = NULL;
    
    do                                                          /*Loop until the user press a btn*/
    {
        if(gameObj->printLogs)
            printConsumption();

        event = MLV_get_event(&keyPressed, NULL, &unicode, NULL, NULL, &mouseX, &mouseY, NULL, &state);    /*Get last event*/
        MLV_flush_event_queue();

        if(event == MLV_MOUSE_MOTION || event == MLV_MOUSE_BUTTON || event == MLV_KEY)  /*Is this a movement of the mouse?*/
        {
            for(i = 0; i < gameObj->nbrToPrint; i++)            /*iterate through all the element to print*/
            {
                if(gameObj->toPrint[i].type == 'b')             /*is this a button ?*/
                {
                    if(isCursorOnBtn(((Button *)gameObj->toPrint[i].element), mouseX, mouseY))  /*Is the cursoron this button?*/
                    {
                        if(event == MLV_MOUSE_BUTTON)/*We do this if the action was a click released*/
                        {
                            gameObj->toPrint[i].state = 'a';
                            if(state == MLV_RELEASED)
                                callbackValue = ((Button *)gameObj->toPrint[i].element)->callback;
                        }
                        else if(event == MLV_MOUSE_MOTION)      /*We do this if the action is just a hover*/
                        {
                            gameObj->toPrint[i].state = 'h';   
                            if(((Button *)gameObj->toPrint[i].element)->hoverCallback != NULL)
                                ((Button *)gameObj->toPrint[i].element)->hoverCallback();
                        }
                    } 
                    else
                    {
                        gameObj->toPrint[i].state = 'i';        /*no, make sure state is idle*/
                    }
                }
                else if(gameObj->toPrint[i].type == 'i')  /*The event is an input box one*/
                {
                    if(event == MLV_MOUSE_BUTTON && state == MLV_RELEASED)
                    {
                        if(isCursorOnInput(((TextBox *)gameObj->toPrint[i].element), mouseX, mouseY))
                        {
                            gameObj->toPrint[i].state = 'f';  /*The user clicked on this inputBox, we give it the focus*/
                        }
                        else
                        {
                            gameObj->toPrint[i].state = 'b';  /*The user didn't clicked on this input box, we make sure it is blured*/
                        }
                    }
                    else if(gameObj->toPrint[i].state == 'f' && event == MLV_KEY && state == MLV_PRESSED)
                    {
                        updateTextBox(i, keyPressed, unicode);  /*The user typed something in the text box, we update it*/
                    }
                }
            }
        }

        printFrame();					/*Update window*/

    } while(callbackValue == '\0');

    return callbackValue;
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

bool isCursorOnInput(TextBox * input, int mouseX, int mouseY)	/*check if cursor is on textBox. Return true if it is, false otherwise*/
{
    int x = input->x + input->imgOffsetX;               /*Get X position of the text box detection area*/
    int y = input->y + input->imgOffsetY;               /*Get Y position of of the text box detection area*/
    int width = input->width - input->imgOffsetX;       /*Get width of the text box detection area*/
    int height = input->height - input->imgOffsetX;     /*Get height of the text box detection area*/

    if(mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    else
        return false;
}

void updateTextBox(int inputPos, MLV_Keyboard_button keyPressed, int unicode)
{
    int contentLength;
    contentLength = strlen(((TextBox *)gameObj->toPrint[inputPos].element)->content);
    
    if(unicode == MLV_KEYBOARD_BACKSPACE)
    {
        if(contentLength > 0)
            ((TextBox *)gameObj->toPrint[inputPos].element)->content[contentLength-1] = '\0';
    }
    else
    {
        if(contentLength < 100)
           strcat(((TextBox *)gameObj->toPrint[inputPos].element)->content, MLV_convert_unicode_to_string(unicode));
    }
}

void quitGame()                         /*This function properly end the game*/
{
    MLV_free_window();                  /*Close the window*/
    exit(0);
}


/********************************************************************************/
/***** Elements creation functions **********************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, char type)  /*Create a Btn and assign specified values*/
{
    Button * btn = allocate(sizeof(Button));    /*Create an empty button*/
    btn->x = x;                                 /*Set X position of the button*/
    btn->y = y;                                 /*Set Y position of the button*/
    btn->width = width;                         /*Set width of the button*/
    btn->height = height;                       /*Set height of the button*/
    btn->type = type;                           /*Set type of the button*/
    btn->callback = '\0';                       /*Set callback as NULL */
    btn->hoverCallback = NULL;                  /*Set hoverCallback as NULL */

    if(type == 'g')                             /*If the button is a graphic one*/
    {
        btn->idleImage = NULL;                  /*Set images as default  */
        btn->hoverImage = NULL;
        btn->activeImage = NULL;
    }
    else                                        /*Otherwise, treat as a plain color button*/
    {
        btn->idleBackColor = MLV_COLOR_BLACK;   /*Set default background color*/
        btn->hoverBackColor = MLV_COLOR_BLACK;
        btn->activeBackColor = MLV_COLOR_BLACK;
        
        btn->idleTextColor = MLV_COLOR_WHITE;   /*Set default text color*/
        btn->hoverTextColor = MLV_COLOR_WHITE;
        btn->activeTextColor = MLV_COLOR_WHITE;
    }

    return btn;
}

Picture * createPicture(int x, int y, char * fileURL)    /*Create an Image element and return it*/
{
    Picture * img = allocate(sizeof(Picture));                  /*create the element*/
    img->x = x;                                                 /*Set X position*/
    img->y = y;                                                 /*Set Y position*/
    img->image = MLV_load_image(fileURL);                       /*Load image*/
    MLV_get_image_size(img->image, &img->width, &img->height);  /*Get image height and width*/

    return img;                                                 /*Return the newly created element*/
}

TextBox * createTextBox(int x, int y, int width, int height, char type, char placeHolder[100])
{
    TextBox * tB = allocate(sizeof(TextBox));
    tB->x = x;
    tB->y = y;
    tB->width = width;
    tB->height = height;
    tB->type = type;
    strcpy(tB->placeHolder, placeHolder);
    tB->content[0] = '\0';

    tB->cursorShown = false;
    tB->lastCursorSwitch = 0;

    tB->textColor = gameObj->defaultInputColor;
    tB->placeHolderColor = gameObj->defaultPlaceHolderColor;

    if(type == 'g')
        tB->backColor = MLV_ALPHA_TRANSPARENT;
    else
        tB->backColor = MLV_COLOR_BLACK;

    tB->backImage = NULL;
    tB->imgOffsetX = 0;
    tB->imgOffsetY = 0;

    return tB;
}