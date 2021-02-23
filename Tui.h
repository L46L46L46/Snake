#include "View.h"

class Tui:View
{
	//рамочка
	void draw_frame();

	public:
	Tui();
	void clean_screen();
	~Tui();
};
