#include "Tui.h"
//#include "Gui.h"
#include "Game.h"

#include <iostream>
//#include <stdio.h>
using namespace std;

int main()
{

	//ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	//this -> setFixedSize(screen_size.ws_row, screen_size.ws_col);
	
	//Make_model

	Tui *p = new Tui;
	
	//p -> draw_rabbit(make_pair(40, 20));

	Game *g = new Game;

	p -> draw_rabbit(g -> get_vector());

	int n;
	cin >> n;
	//p -> draw();
	
	delete g;
	delete p;
	return n;
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
