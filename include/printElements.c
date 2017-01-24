#include <stdio.h>
#include <stdlib.h>  
#include <time.h> 
#include <MLV/MLV_all.h>
#include "../headers/structs.h"
#include "../headers/functions.h"

/*PrintFrame loop over the toPrint array stored in the gameObj
 *It print all the shown element on the screen in their order in the toPrint array
 */
void printFrame()
{
    int nbrToPrint = gameObj->nbrToPrint;
    int i;
    PrintElement el;
    
    /*First we clean the screen*/
    cleanScreen();                              
    
    /*Iterate over all the element of the toPrint array*/
    for(i = 0; i < nbrToPrint; i++)             
    {
        if(gameObj->toPrint[i].display)
        {
            el = gameObj->toPrint[i];
            
            /*Then print it with the apropriate function*/
            switch(el.type)
            {
                case BUTTON: printBtn(el.element.btn, el.state); break;
                case PICTURE: printPicture(el.element.pict); break;
                case TEXTBOX: printTextBox(el.element.tB, el.state); break;
                case NUMBERBOX: printNumberBox(el.element.nB, el.state); break;
                case TEXT: printText(el.element.txt, el.state); break;
            }
        }
    }
    
    /*finaly we actualise the window*/
    MLV_actualise_window();                     
}


/*addToPrint() add the given element to the toPrint array
 */
PrintElement * addToPrint(void * element, enum elType type)
{
    int newSize;
    PrintElement newEl;
    
    /*We make sure no NULL pointer get's in the loop*/
    criticalIfNull(element);                    
    
    newEl.type = type;                             
    
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

    newEl.display = true;                                             
    newEl.canFade = false;

    if(type == TEXTBOX)
        newEl.state = BLUR;
    else
        newEl.state = IDLE;
    
    /*Resize of the toPrint array*/
    newSize = (gameObj->nbrToPrint + 1) * sizeof(PrintElement);

    if(gameObj->nbrToPrint == 0)
        gameObj->toPrint = allocate(newSize);
    else
        gameObj->toPrint = reAllocate(gameObj->toPrint, newSize); 

    /*Insert newly created printElement in the toPrint array*/
    gameObj->toPrint[gameObj->nbrToPrint] = newEl;                 
    gameObj->nbrToPrint++;
    
    /*Return the newly created element so it can be edited*/
    return &gameObj->toPrint[gameObj->nbrToPrint-1];                
}


/*cleanPrint() empty the toPrint array
 */
void cleanToPrint()
{
    int i;

    if(gameObj->nbrToPrint != 0)
    {
        for(i = 0; i < gameObj->nbrToPrint; i++)
        {
            /*Free the element with the appropriate function*/
            switch(gameObj->toPrint[i].type)          
            {
                case BUTTON: freeBtn(gameObj->toPrint[i].element.btn); break;
                case PICTURE: freePicture(gameObj->toPrint[i].element.pict); break;
                case TEXTBOX: freeTextBox(gameObj->toPrint[i].element.tB); break;
                case NUMBERBOX: freeNumberBox(gameObj->toPrint[i].element.nB); break;
                case TEXT: freeText(gameObj->toPrint[i].element.txt); break;
            }
        }

        free(gameObj->toPrint); 
        
        gameObj->toPrint = NULL;
        gameObj->nbrToPrint = 0;                                     
    }
}






/********************************************************************************/
/***** Functions to create the elements *****************************************/
/********************************************************************************/

Button * createBtn(int x, int y, int width, int height, enum btnType type)  /*Create a Btn and assign specified values*/
{
    Button * btn = allocate(sizeof(Button));    /*Create an empty button*/
    btn->x = x;                                 /*Set X position of the button*/
    btn->y = y;                                 /*Set Y position of the button*/
    btn->width = width;                         /*Set width of the button*/
    btn->height = height;                       /*Set height of the button*/
    btn->type = type;                           /*Set type of the button*/
    btn->simpleCallback = true;
    btn->callback = 0;                          /*Set callback as NULL */
    btn->hoverCallback = NULL;                  /*Set hoverCallback as NULL */
    btn->activeCallbackArgument = NULL;
    btn->activeCallback = NULL;
    btn->canToggle = false;
    btn->checked = false;

    if(type == BTN_GRAPHIC)                             /*If the button is a graphic one*/
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

Text * createText(int x, int y, int width, int height, char size, char * content)    /*Create an Image element and return it*/
{
    Text * txt = allocate(sizeof(Text));                  /*create the element*/
    txt->x = x;                                                 /*Set X position*/
    txt->y = y;                                                 /*Set Y position*/
    txt->width = width;
    txt->height = height;
    txt->size = size;
    strcpy(txt->content, content);

    return txt;                                                 /*Return the newly created element*/
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

NumberBox * createNumberBox(int x, int y, int defaultVal, int minVal, int maxVal)
{
    NumberBox * nB = allocate(sizeof(NumberBox));
    Button * plusBtn, * lessBtn;

    nB->x = x;
    nB->y = y;
    nB->value = defaultVal;
    nB->minValue = minVal;
    nB->maxValue = maxVal;

    nB->backImage = MLV_load_image("images/inputBox_small.png");

    plusBtn = createBtn(x+125, y+2, 44, 36, BTN_GRAPHIC);
    plusBtn->idleImage = MLV_load_image("images/buttons/plusBtn_small_idle.png");
    plusBtn->hoverImage = MLV_load_image("images/buttons/plusBtn_small_hover.png");
    plusBtn->activeImage = MLV_load_image("images/buttons/plusBtn_small_active.png");
    plusBtn->simpleCallback = false;
    plusBtn->activeCallbackArgument = nB;
    plusBtn->activeCallback = incrementNumberBox;

    nB->plusBtn = plusBtn;

    lessBtn = createBtn(x, y+2, 44, 36, BTN_GRAPHIC);
    lessBtn->idleImage = MLV_load_image("images/buttons/lessBtn_small_idle.png");
    lessBtn->hoverImage = MLV_load_image("images/buttons/lessBtn_small_hover.png");
    lessBtn->activeImage = MLV_load_image("images/buttons/lessBtn_small_active.png");
    lessBtn->simpleCallback = false;
    lessBtn->activeCallbackArgument = nB;
    lessBtn->activeCallback = decrementNumberBox;

    nB->lessBtn = lessBtn;

    return nB;
}





/********************************************************************************/
/***** Functions to print the elements ******************************************/
/********************************************************************************/

void printBtn(struct Button * btn, char state)  /*Print a given button at the current state*/
{
    MLV_Color backColor;                        /*Variables who change depdning of the state of the button*/
    MLV_Color textColor;
    MLV_Image * image;

    if(btn->type == BTN_GRAPHIC)                /*Is the button a graphical one?*/
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





/********************************************************************************/
/***** Functions to free the elements  ******************************************/
/********************************************************************************/

void freeBtn(Button * btn)
{
    if(btn->type == BTN_GRAPHIC)
    {
        MLV_free_image(btn->idleImage);
        MLV_free_image(btn->hoverImage);
        MLV_free_image(btn->activeImage);
    }

    free(btn);
}

void freePicture(Picture * pic)
{
    MLV_free_image(pic->image);
    free(pic);
}

void freeTextBox(TextBox * tB)
{
    if(tB->type == 'g')
       MLV_free_image(tB->backImage);
    
    free(tB);
}

void freeNumberBox(NumberBox * nB)
{
    MLV_free_image(nB->backImage);
    free(nB);
}


void freeText(Text * txt)
{
    free(txt);
}