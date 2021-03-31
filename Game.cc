#include "Game.h"
#include "View.h"

#define SNAKE_START_SIZE 7
#define RABBITS_COUNT 10

using namespace std;

pair<int, int> Rabbit :: get_coordinates()
{
	return _coordinates;
}

Rabbit :: Rabbit(pair<int, int> get_coordinates)
{
	_coordinates = get_coordinates;
}

Rabbit :: ~Rabbit()
{
};

void Snake :: set_direct(int derection)
{
	direct = derection;
}

Snake :: Snake(pair<int, int> snake_head, int wight)
{
	if (snake_head.first > wight)
	{
		for (int i = 1; i < SNAKE_START_SIZE; i++)
		{
			_coordinates.push_back (make_pair(snake_head.first + i, snake_head.second));
		}
		direct = LEFT;
	}
	else
	{
		for(int i = 1; i < SNAKE_START_SIZE; i++)
		{
			_coordinates.push_back (make_pair(snake_head.first - i, snake_head.second));
		}
		direct = RIGHT;
	}
};

Snake :: ~Snake()
{
};


pair<int, int> Game :: get_rabbit_coordinates(Rabbit& rabbit)
{
	return rabbit.get_coordinates();
}

list<pair<int, int>> Game :: get_snake_coordinates(Snake& snake)
{
	return snake.get_coordinates();
}


pair<int, int> Game :: make_coordinates()
{
	int x = rand() % (view -> get_screen_size().second - 3) + 3;
	int y = rand() % (view -> get_screen_size().first - 5) + 3;
	return make_pair(x, y);
};

list<Snake> Game :: get_snake_list()
{
	return snakes;
}

list<Rabbit> Game :: get_rabbit_list()
{
	return rabbits;
}

list <pair <int, int>> Snake :: get_coordinates()
{
	return _coordinates;
};

pair<int, int> Snake :: get_snake_head()
{
	return _coordinates.front();
}

int Snake :: get_direct()
{
	return direct;
}

void Game :: update_snake()
{
	for (Snake& snake : snakes)
	{
		pair<int, int> head = snake.get_snake_head();
		switch(snake.get_direct())
		{
			case RIGHT:
				head.first++;
				break;
			case LEFT:
				head.first--;
				break;
			case UP:
				head.second--;
				break;
			case DOWN:
				head.second++;
				break;
		}
		view -> draw_cell(snake.get_snake_head(), SNAKE);
		view -> draw_cell(head, SNAKE_HEAD);
		view -> clean_cell(snake.get_coordinates().back());
		snake.update(head);
	}
}

void Snake :: update (pair<int, int> head)
{
	_coordinates.push_front(head);
	_coordinates.pop_back();
}

Rabbit& Game :: make_rabbit()
{
	pair<int, int> rabbit = make_coordinates();
	rabbits.push_back(rabbit);
	return rabbits.back();
}

Snake& Game :: make_snake()
{
	pair<int, int> snake_head = make_coordinates();
	if (snake_head.first < SNAKE_START_SIZE + 2)
	{
		snake_head.first = SNAKE_START_SIZE + 2;
	}
	if (snake_head.first > view -> get_screen_size().second - SNAKE_START_SIZE - 1)
	{
		snake_head.first = view -> get_screen_size().second - SNAKE_START_SIZE - 1;
	}
	snakes.push_back(Snake (snake_head, view -> get_screen_size().second/2));
	return snakes.back();
}

Game :: Game(View* _view)
{
	view = _view;
	srand(time(NULL));
//make Rabbits
	for (int i = 0; i < RABBITS_COUNT; i++)
	{
		Rabbit& rabbit = make_rabbit();
	}
	//подписаться на таймер
	view -> addtimer(bind(&Game :: update_snake, this), 200);
};


Game :: ~Game()
{
	rabbits.clear();
	snakes.clear();
};
