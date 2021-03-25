#include "Tui.h"
#include "Game.h"

#include <iostream>

#define RABBIT 41
#define SNAKE 42
#define SNAKE_HEAD 43

using namespace std;

int main()
{
	setbuf(stdout, NULL);
	//Make_model

	View *paint = new Tui;
	Game *game = new Game(paint);

	//Get list of rabbits and draw it
	for(pair<int, int> it : game -> get_rabbits())
	{
		paint -> draw_cell(it, RABBIT);
	}

	//Get snake coordinates and draw it
	for(pair<int, int> it : game -> get_snake())
	{
		paint -> draw_cell(it, (it != game -> get_snake().front()) * SNAKE + (it == game -> get_snake().front()) * SNAKE_HEAD);
	}

	paint -> runloop();

	delete game;
	delete paint;
	return 0;
	//чекаем, дали ли нам ключ для графической библиотеки
	//if ("")
	//{
	//	jui v;
	//}
	//else
	//{
	//	tui v;
	//}
}
