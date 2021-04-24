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
			char buf;
			read(0, &buf, 1);
			if (buf == 'q')
			{
				kill(getpid(), 9);
			}
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
	//
}


void Tui :: draw_cell(const pair<int, int> coordinates, int collor)
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[%dm", collor); //set cell background
	printf(" ");
	printf("\e[0m"); //set normal background

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
};

void Tui :: clean_cell(const pair<int, int> coordinates) const
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[0m"); //set normal background
	printf(" ");

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
}

Tui :: Tui()
{
	struct termios newt, _termios;
	tcgetattr(STDIN_FILENO, &_termios);
	newt = _termios;
	newt.c_lflag &= ~ICANON;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	clean_screen();
	onwinch = bind(&Tui :: draw_frame, this);
	signal(SIGWINCH, &Tui :: winch);
};

Tui :: ~Tui()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &_termios);
};

