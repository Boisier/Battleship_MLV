#pragma once

#define bool int
#define true 1
#define false 0

typedef struct Ship
{
    int size;               //Size of the ship (1, 2, 3, 4 or 5)
    char direction;         //vertical or horizontal (v or h)
    int posX;               //X position of the ship on the grid
    int posY;               //Y position of the ship on the grid
    bool hits[5];           //Details which cell of the ship has been hit;

} Ship;

typedef struct Cell
{
    char type;              //Type of the cell (e -> empty, s -> ship);
    bool hit;               //Has the cell been hit or not? (true or false)
}Cell;

typedef struct Grid
{
    int size;               //Size of the grid
    Cell *cells;            //Cells of the grid
    Ship *ships;            //Ships on the grid
} Grid;

typedef struct Player
{
    char type;              //Type of player, can be either h (human) or c (computer/ai)
    char score;  
    Grid *grid;             //If multiple game are fdone, keep track of scores.
} Player;

typedef struct GameObj      //The gameObj carry all the variables used by the game
{
    Player *player1;        //First player obj
    Player *player2;        //Second player obj
    int currTurn;           //Current player. Can be either 1, 2 or 0 if not in game;  

    int wWidth;             //Width of the window
    int wHeight;            //Height of the window
} GameObj;