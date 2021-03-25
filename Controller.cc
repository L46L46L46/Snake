#include "Controller.h"
#include "Game.h"
#include "View.h"

//interval -= event_time


void Controller :: control(int key)
{
	switch(key)
	{
		case 'A':
			snake -> set_direct(UP);
			break;
		case 'B':
			snake -> set_direct(DOWN);
			break;
		case 'C':
			snake -> set_direct(RIGHT);
			break;
		case 'D':
			snake -> set_direct(LEFT);
			break;
		default:
			kill(getpid(), 9);
	}
}

Controller :: Controller(Snake* s_snake, View* v_view)
{
	snake = s_snake;
	view = v_view;

	view -> setonkey(bind(&Controller :: control, this, _1));
}

Controller :: ~Controller()
{
}

