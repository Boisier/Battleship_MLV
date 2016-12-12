#include <stdio.h>
#include <MLV/MLV_all.h>

int main(int argc, char *argv[])
{
	int x = 0;
	int y = 3000;

	printf("largeur : ");
	scanf("%d", &x);
	printf("hauteur : ");
	scanf("%d", &y);

	MLV_create_window( "vdufois - TP8Ex3", "hello world", x, y);

	int i = 0;
	
	for(i = 0; i < x/2; i++)
	{
		MLV_draw_filled_rectangle(i, 0, x/2, y, MLV_COLOR_GREEN);
		
		if(i != 0)
			MLV_draw_filled_rectangle(0, 0, i, y, MLV_COLOR_BLACK);

		MLV_wait_seconds(1);
		MLV_actualise_window();
	}
	
	MLV_wait_seconds(10);
	MLV_free_window();
	return 0;
 }