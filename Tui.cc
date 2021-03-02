#include "Tui.h"

using namespace std;


function<void(void)> Tui :: onwinch;

void Tui :: clean_screen()
{
	printf("\e[2J"); //clean sreen
};

void Tui :: winch(int n)
{
	onwinch();
};

void Tui :: draw_frame()
{
	clean_screen();
	printf("\e[47m"); //set white background

	//get screen size
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
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
		for (int j = 0; j < wight - 1 ; j++)
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

void Tui :: draw_rabbit(pair<int, int> coordinates)
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[42m"); //set green background
	printf(" ");
	printf("\e[0m"); //set normal background

//get screen size
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	int hight = screen_size.ws_row - 1;

	printf("\e[%d;%dH", hight, 0);
};

Tui :: Tui()
{
	setbuf(stdout, NULL);
	draw_frame();
	onwinch = bind(& Tui :: draw_frame, this);
	signal(SIGWINCH, & Tui :: winch);
};

Tui :: ~Tui()
{
};

