#pragma once

#include "Game.h"
#include "View.h"
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Game;
//class Snake;
//class Rabbit;
class View;

class Controller
{
	public:
		Controller(Snake* s_snake, View* view);
		void control(int buf);
		~Controller();
		//void Tick();
	private:
		Snake* snake;
		View* view;
};
