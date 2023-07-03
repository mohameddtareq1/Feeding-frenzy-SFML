#pragma once
#include "sfml/Graphics.hpp"
#define max_num 4
class menu
{


public:
	menu(int width, int hight);
	void draw(sf::RenderWindow& window);
	void moveup();
	void movedown();
	void pausemoveup();
	void pausemovedown();
	int getselecteditem()
	{
		return selecteditem;
	}
	sf::Text menuu[max_num];
private:

	sf::Font font;

	int selecteditem;




};