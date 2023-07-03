#include "menu.h".
using namespace sf;
menu::menu(int width, int hight)
{
	font.loadFromFile("Resources/Fonts/scrubland.regular.ttf");

	menuu[0].setFont(font);
	menuu[0].setCharacterSize(90);
	menuu[0].setFillColor(Color(200, 200, 255, 255));
	menuu[0].setPosition(Vector2f((width / 4) - 25, (hight / max_num) - 100));
	menuu[0].setString("Play");
	menuu[0].setOutlineColor(Color::Black);
	menuu[0].setOutlineThickness(2);

	menuu[1].setFont(font);
	menuu[1].setFillColor(Color::White);
	menuu[1].setCharacterSize(90);
	menuu[1].setPosition(Vector2f((width / 4) - 125, (hight / max_num) + 40));
	menuu[1].setString("Instructions");

	menuu[2].setFont(font);
	menuu[2].setFillColor(Color::White);
	menuu[2].setCharacterSize(90);
	menuu[2].setPosition(Vector2f((width / 4) - 35, (hight / max_num) + 180));
	menuu[2].setString("Credits");

	menuu[3].setFont(font);
	menuu[3].setFillColor(Color::White);
	menuu[3].setCharacterSize(90);
	menuu[3].setPosition(Vector2f((width / 4) - 35, (hight / max_num) + 320));
	menuu[3].setString("Exit");

	selecteditem = 0;
}
void menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < max_num; i++)
	{
		window.draw(menuu[i]);
	}
}
void menu::moveup()
{
	if (selecteditem - 1 >= -1)
	{
		menuu[selecteditem].setFillColor(Color::White);
		menuu[selecteditem].setOutlineThickness(0);
		selecteditem--;
		if (selecteditem == -1)
		{
			selecteditem = 3;

		}
		menuu[selecteditem].setFillColor(Color(200, 200, 255, 255));
		menuu[selecteditem].setOutlineColor(Color::Black);
		menuu[selecteditem].setOutlineThickness(2);
	}
}
void menu::movedown()
{
	if (selecteditem + 1 <= 4)
	{
		menuu[selecteditem].setFillColor(Color::White);
		menuu[selecteditem].setOutlineThickness(0);
		selecteditem++;
		if (selecteditem == 4)
		{
			selecteditem = 0
				;
		}
		menuu[selecteditem].setFillColor(Color(200, 200, 255, 255));
		menuu[selecteditem].setOutlineColor(Color::Black);
		menuu[selecteditem].setOutlineThickness(2);
	}

}
void menu::pausemoveup()
{
	if (selecteditem - 1 >= -1)
	{
		menuu[selecteditem].setFillColor(Color::White);
		menuu[selecteditem].setOutlineThickness(0);
		selecteditem--;
		if (selecteditem == -1)
		{
			selecteditem = 2;

		}
		menuu[selecteditem].setFillColor(Color(200, 200, 255, 255));
		menuu[selecteditem].setOutlineColor(Color::Black);
		menuu[selecteditem].setOutlineThickness(2);
	}


}
void menu::pausemovedown()
{
	if (selecteditem + 1 <= 3)
	{
		menuu[selecteditem].setFillColor(Color::White);
		menuu[selecteditem].setOutlineThickness(0);
		selecteditem++;
		if (selecteditem == 3)
		{
			selecteditem = 0
				;
		}
		menuu[selecteditem].setFillColor(Color(200, 200, 255, 255));
		menuu[selecteditem].setOutlineColor(Color::Black);
		menuu[selecteditem].setOutlineThickness(2);
	}

}