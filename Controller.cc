#include "Controller.h"
#include "Game.h"
#include "View.h"

//interval -= event_time

void Controller :: letter_control(char key)
{
	if (key == keys[0])
	{
		snake -> set_direct(UP);
	}
	else if (key == keys[1])
	{
		snake -> set_direct(LEFT);
	}
	else if (key == keys[2])
	{
		snake -> set_direct(DOWN);
	}
	else if (key == keys[3])
	{
		snake -> set_direct(RIGHT);
	}
}

/*void Controller :: arrow_control(char key)
{
	switch(key)
	{
		//case '[':
		//	read(0, &key, 1);
		//	switch(key)
		//	{
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
		//	}
		//	break;
	}
}*/

Controller :: Controller(Game* _game, View* _view, const char* _keys)
{
	game = _game;
	view = _view;
	keys = _keys;

	snake = &game -> make_snake();
//	view -> setonkey(bind(&Controller :: arrow_control, this, _1));
	view -> setonkey(bind(&Controller :: letter_control, this, _1));
}

Controller :: ~Controller()
{
}

