#pragma once

// Init the grid, interface of the game then call the placeShip function
initGame();


// Show the grid if it's mine or the ennemy's one
void showGrid (Grid g, bool self);

// The player give the position of his ships and their orientations, 
// call verifyPosition() to see if it's possible
void placeShip();

// Player give a position, 
void play();

// Verify the position if it's already used for the placment of the ship
int verifyPosition();


