#pragma once

#include <utility>
#include <vector>

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Game
{
	public:
		Game();
		pair<int, int> get_vector();
		~Game();

	//void rubbit();
	private:
		vector < pair<int, int> > coordinates_rabbits;
};

class Rabbit
{
	public:
		Rabbit(std :: pair<int, int> coordinates);
		~Rabbit();
};

//class Snake
