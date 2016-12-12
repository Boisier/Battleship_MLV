#pragma once

/********************************************************************************/
/***** Main functions definitions ***********************************************/
/********************************************************************************/

// Init the game, set variables to default value
void initGame();

// Display Main menu
void mainMenu();


/********************************************************************************/
/***** Game functions definitions ***********************************************/
/********************************************************************************/

// Show the grid if it's mine or the ennemy's one
void displayGrid (Grid g, bool self);

// The player give the position of his ships and their orientations, 
// call verifyPosition() to see if it's possible
void placeShip();

// Player give a position, 
void play();

// Verify the position if it's already used for the placment of the ship
int verifyPosition();


/********************************************************************************/
/***** Helper functions definitions *********************************************/
/********************************************************************************/


