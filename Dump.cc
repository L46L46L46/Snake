#include "Dump.h"

//#define ON_CLOCK_ARROW 1

int Dump :: distance(pair<int, int> a, pair<int, int> b)
{
	return fabs(a.first - b.first) + fabs(a.second - b.second);
}

Rabbit& Dump :: get_near_rabbit()
{
	Rabbit& near = game -> get_rabbit_list().front();

	for (Rabbit& rabbit : game -> get_rabbit_list())
	{
		int distant = distance(snake -> get_snake_head(), game -> get_rabbit_coordinates(rabbit));
		if (distant != 0 && distant < distance(snake -> get_snake_head(), game -> get_rabbit_coordinates(near)))
		{
			near = rabbit;
		}
	}
	return near;
}

void Dump :: controller()
{
	pair<int, int> head = snake -> get_snake_head();

//Eat rabbit
	if (head.second == target.second && snake -> get_direct() == DOWN)
	{
		snake -> set_direct(RIGHT);
	}
	else
	if(head.second == target.second && snake -> get_direct() == UP)
	{
		snake -> set_direct(LEFT);
	}
	else
	if (head.first == target.first && snake -> get_direct() == RIGHT)
	{
		snake -> set_direct(UP);
	}
	else
	if (head.first == target.first && snake -> get_direct() == LEFT)
	{
		snake -> set_direct(DOWN);
	}

	if (game -> get_obstacles(make_pair(head.first, head.second + 1)) == 1 && snake -> get_direct() == DOWN)
	{
		snake -> set_direct(RIGHT);
	}
	if (game -> get_obstacles(make_pair(head.first, head.second - 1)) == 1 && snake -> get_direct() == UP)
	{
		snake -> set_direct(LEFT);
	}
	if (game -> get_obstacles(make_pair(head.first + 1, head.second)) == 1 && snake -> get_direct() == RIGHT)
	{
		snake -> set_direct(UP);
	}
	if (game -> get_obstacles(make_pair(head.first - 1, head.second)) == 1 && snake -> get_direct() == LEFT)
	{
		snake -> set_direct(DOWN);
	}

	game -> update_snake();
	check_shell_is_rabbit();
}

void Dump :: check_shell_is_rabbit()
{
	for (list<Rabbit>::iterator rabbit = game -> get_rabbit_list().begin(); rabbit != game -> get_rabbit_list().end(); )
	{
		if (snake -> get_snake_head() == game -> get_rabbit_coordinates(*rabbit))
		{
			game -> remove_rabbit(rabbit);
			if (snake -> get_snake_head() == target)
			{
				make_target();
			}
		}
	}
}

void Dump :: make_target()
{
	target = game -> get_rabbit_coordinates(get_near_rabbit());
}

Dump :: Dump(Game* _game, View* _view)
{
	game = _game;
	view = _view;

	snake = &game -> make_snake();
	target = game -> get_rabbit_coordinates(get_near_rabbit());
	view -> draw_cell(target, 46);
	view -> addtimer(bind(&Dump :: controller, this), 150);
}

Dump :: ~Dump()
{
}
