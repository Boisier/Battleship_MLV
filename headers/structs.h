#pragma once

#define bool int
#define true 1
#define false 0

typedef struct Player
{

} Player;

typedef struct Cell
{
    char type;              //Type of the cell (e -> empty, s -> ship);
    bool hit;               //Has the cell been hit or not? (true or false)
}Cell;

typedef struct Grid
{
    int size;               //Size of the grid
    Cell *cells;            //Celles of the grid
    Ship *ships             //Ships on the grid
} Grid;

typedef struct Ship
{
    int size;               //Size of the ship (1, 2, 3, 4 or 5)
    char direction;         //vertical or horizontal (v or h)
    int posX;               //X position of the ship on the grid
    int posY;               //Y position of the ship on the grid
    bool hits[5];           //Details which cell of the ship has been hit;

} Ship;