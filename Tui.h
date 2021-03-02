#pragma once

#include "View.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include <functional>

using namespace std;

class Tui:View
{
	//рамочка
	void draw_frame();
	void draw();
	//void draw_rubbit(pair<x, y>);

	static function<void(void)> onwinch;
	static void winch(int n);

	public:
	Tui();
	void clean_screen();
	void draw_rabbit(pair <int, int> coordinates);
	~Tui();
};
