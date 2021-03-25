#pragma once

#include "Game.h"
#include "View.h"
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Game;


class View;

class Controller
{
	public:
		Controller(Game* _game, View* _view, const char* _keys = "ABCD");
		//void arrow_control(char buf);
		void letter_control(char key);
		~Controller();
		//void Tick();
	private:
		const char* keys;
		Game* game;
		Snake* snake;
		View* view;
};
