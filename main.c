//Main includes
#include <stdio.h>
#include <MLV/MLV_all.h>

//Include own headers
#include "headers/structs.h"
#include "headers/functions.h"

int main(int argc, char *argv[])
{
	//Game has been lauched;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );
	//
	// Affiche "Bonjour !" a l'écran 
	//
	MLV_draw_text(
			10, 120, 
			"Bonjour !",
			MLV_COLOR_MAGENTA
	);
	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();
	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );
	//
	// Ferme la fenêtre
	//
	MLV_free_window();
	return 0;

	return 0;
 }