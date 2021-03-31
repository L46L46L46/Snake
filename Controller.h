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
		Controller(Game* _game, View* _view, const char* _keys = "ADBC");
		void letter_control(int key);
		~Controller();
	private:
		const char* keys;
		Game* game;
		Snake* snake;
		View* view;
};
