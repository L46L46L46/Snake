#include "Game.h"

using namespace std;



pair<int, int> Game :: get_vector()
{
	pair<int, int> rabbit_vector = coordinates_rabbits[0];
	return rabbit_vector;
}

Game :: Game()
{
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	int hight = screen_size.ws_row - 4;
	int wight = screen_size.ws_col - 2;


	srand(time(NULL));

	int x = 1 + rand() % wight;
	int y = 1 + rand() % hight;

	coordinates_rabbits.push_back (make_pair(x, y));
};

Rabbit :: Rabbit(std :: pair<int, int> coordinates)
{
//	coordinates_rabbits.push_back(coordinates);
}

Game :: ~Game()
{
};

Rabbit :: ~Rabbit()
{
};
