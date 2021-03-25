#include "Tui.h"

using namespace std;

function<void(void)> Tui :: onwinch;

void Tui :: addtimer (timer_fn fun, int interval)
{
	timer.first = fun;
	timer.second = interval;
}

void Tui :: setonkey(key_fn fun)
{
	keys.push_back(fun);
}


void Tui :: runloop()
{
	struct pollfd fds = {0, POLL_IN, 0};
	int interval = timer.second;
	running = true;
	int flag = 1;
	while(running)
	{
		int poll_return = poll(&fds, 1, flag * interval);
		flag = 1;
		if (poll_return == 0)
		{
			timer.first();
		}
		else
		{
			flag = 0;
			char buf = getchar();
			//read(0, &buf, 1);
			for (auto fun : keys)
			{
				fun(buf);
			}
		}
	}
}

void Tui :: quit()
{
	running = false;
}

void clean_screen()
{
	printf("\e[2J"); //clean sreen
};

void Tui :: winch(int n)
{
	onwinch();
};

pair<int, int> Tui :: get_screen_size() const
{
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	return make_pair(screen_size.ws_row, screen_size.ws_col);
}

void Tui :: draw_frame()
{
	clean_screen();
	printf("\e[47m"); //set white background

	if (get_screen_size().first < 5 or get_screen_size().second < 3)
	{
		printf("\e[0m"); //set normal background
		printf("Screen size too small\n");
		kill(getpid(), 9);
	}

	//draw frame
	printf("\e[0;0H"); //set cursor to the top left
	for (int i = 0; i < get_screen_size().second; i++)
	{
		printf(" ");
	}
	for (int i = 0; i < get_screen_size().first - 4; i++)
	{
		printf("\n");
		printf(" ");
		for (int j = 0; j < get_screen_size().second - 1 ; j++)
		{
			printf("\e[C"); //cursor shift
		}
		printf(" ");
	}
	printf("\n");
	for(int i = 0; i < get_screen_size().second; i++)
	{
		printf(" ");
	}
	printf("\n");

	
	printf("\e[0m"); //set normal background
}

void Tui :: draw_cell(pair<int, int> coordinates, int collor) const
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[%dm", collor); //set cell background
	printf(" ");
	printf("\e[0m"); //set normal background

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
};

void Tui :: clean_cell(pair<int, int> coordinates) const
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[0m"); //set normal background
	printf(" ");

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
}

Tui :: Tui()
{
//	setbuf(stdout, NULL);

	struct termios term;
	tcgetattr(0, &term);
	_termios = term;
	cfmakeraw(&term);
	tcsetattr(0, TCSAFLUSH, &term);

	draw_frame();
	onwinch = bind(&Tui :: draw_frame, this);
	signal(SIGWINCH, &Tui :: winch);
};

Tui :: ~Tui()
{
	tcsetattr(0, TCSAFLUSH, &_termios);
};

