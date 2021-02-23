#include "Tui.h"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void Tui :: clean_screen()
{
	printf("\e[2J"); //clean sreen
};

void Tui :: draw_frame()
{
	printf("\e[47m"); //set white background

	//get screen size
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	//this -> setFixedSize(screen_size.ws_row, screen_size.ws_col);
	//ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	int hight = screen_size.ws_row - 4;
	int wight = screen_size.ws_col;

	if (hight < 5 or wight < 3)
	{
		printf("\e[0m"); //set normal background
		printf("Screen size too small\n");
		kill(getpid(), 9);
	}

	//draw frame
	printf("\e[0;0H"); //set cursor to the top left
	for (int i = 0; i < wight; i++)
	{
		printf(" ");
	}
	for (int i = 0; i < hight; i++)
	{
		printf("\n");
		printf(" ");
		for (int j = 0; j < wight - 1; j++)
		{
			printf("\e[C"); //cursor shift
		}
		printf(" ");
	}
	printf("\n");
	for(int i = 0; i < wight; i++)
	{
		printf(" ");
	}
	printf("\n");

	
	printf("\e[0m"); //set normal background
}

Tui :: Tui()
{
	clean_screen();
	draw_frame();
};


Tui :: ~Tui()
{
};

