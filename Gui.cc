#include "Gui.h"

void Gui :: addtimer(timer_fn fun, int interval)
{
	
	timer.first = fun;
	timer.second = interval;
}

void Gui :: runloop()
{
	while (window.isOpen())
	{
	// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			//"close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					for (auto fun : keys)
					{
						fun('A');
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					for (auto fun : keys)
					{
						fun('B');
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{

					for (auto fun : keys)
					{
						fun('C');
					}
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					for (auto fun : keys)
					{
						fun('D');
					}
				}
			}
		}
        //clear the window with black color
        window.clear(sf::Color::Black);
	//usleep(500);
	timer.first();

	for(auto it = to_print.begin(); it != to_print.end(); ++it)
	{
		sf :: Vector2f targetSize(30.0f, 30.0f);
		sf :: Image pic;
		sf :: Sprite picsprite;
		sf :: Texture pictext;
		//make image
		pic.loadFromFile((*it).first);
		//make texture
		pictext.loadFromImage(pic);
		//make sprite
		picsprite.setTexture(pictext);

		//set normal size
		picsprite.setScale(targetSize.x / picsprite.getLocalBounds().width, targetSize.y / picsprite.getLocalBounds().height);

		picsprite.setPosition(30 * (*it).second.first % get_screen_size().first, 30 * (*it).second.second % get_screen_size().second);
		window.draw(picsprite);
	}
        // draw everything here...

        // end the current frame
        window.display();
    }

}

void Gui :: quit()
{
	//
}

void Gui :: setonkey(key_fn fun)
{
	keys.push_back(fun);
}

void Gui :: draw_frame()
{
	//
}

void Gui :: draw_cell(pair<int, int> coordinates, int color)
{
	switch(color)
	{
		case 41:
			to_print.push_back(make_pair("rabbit.png", coordinates));
			break;
		case 42:
			to_print.push_back (make_pair ("snake.jpg", coordinates));
			break;
		case 43:
			to_print.push_back (make_pair ("snake_head.png", coordinates));
			break;
	}
}
void Gui :: clean_cell(pair<int, int> coordinates)
{

	to_print.remove_if([coordinates](auto it){return it.second == coordinates;});
}

pair<int, int> Gui :: get_screen_size() const
{
	sf::Vector2u size = window.getSize();
	return make_pair(size.x, size.y);
}

Gui :: Gui()
{
	window.create(sf::VideoMode(1000,800),"Snake");
}

Gui :: ~Gui()
{
	//
}


//std::__cxx11::list<std::pair<std::__cxx11::basic_string<char>, std::pair<int, int> > >::const_iterator {aka std::_List_const_iterator<std::pair<std::__cxx11::basic_string<char>, std::pair<int, int> > >}
//std::__cxx11::list<std::pair<std::__cxx11::basic_string<char>, std::pair<int, int> > >::iterator {aka std::_List_iterator<std::pair<std::__cxx11::basic_string<char>, std::pair<int, int> > >}
