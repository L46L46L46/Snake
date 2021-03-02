#pragma once

//#include <stdio.h>

class View
{
	public:
	//View();
	~View();

	virtual void clean_screen() = 0;
	virtual void draw_frame() = 0;
	//void run()
	//{
		//wait
	//};
};
