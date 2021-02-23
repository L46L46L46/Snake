#include "Tui.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{

	//ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	//this -> setFixedSize(screen_size.ws_row, screen_size.ws_col);

	Tui *p = new Tui;

	int n;
	cin >> n;
	//p -> draw();
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
