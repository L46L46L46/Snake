#include "View.h"
#include "Game.h"
#include "Controller.h"


#include <iostream>

#define WALL 47
#define RABBIT 41
#define SNAKE 42
#define SNAKE_HEAD 43

using namespace std;

int main()
{
	setbuf(stdout, NULL);
	//Make_model

	View* paint = View :: get("Gui");

	Game* game = new Game(paint);

	for (pair<int, int> it : game -> get_wall())
	{
		paint -> draw_cell(it, WALL);
	}
	//Get list of rabbits and draw it
	for (Rabbit& rabbit : game -> get_rabbit_list())
	{
		paint -> draw_cell(game -> get_rabbit_coordinates(rabbit), RABBIT);
	}

	Controller* h1 = Controller :: get(game, paint/*, "Dump"*/);
	//Human h2(game, paint, "wasd");

	//Get snake coordinates and draw it
	for (Snake& snake : game -> get_snake_list())
	{
		for(pair<int, int> it : game -> get_snake_coordinates(snake))
		{
			paint -> draw_cell(it, (it != game -> get_snake_coordinates(snake).front()) * SNAKE + (it == game -> get_snake_coordinates(snake).front()) * SNAKE_HEAD);
		}
	}

	paint -> runloop();

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
