#pragma once
#include <SFML/Graphics.hpp>

#include "TextUI.h"

class Button
{

public:

	sf::Vector2f pos;
	sf::Text text;
	sf::Font roboto;
	sf::RectangleShape buttonBox;

	float boxLenght;
	float boxHeight;

	Button(float sizeX, float sizeY, sf::Color boxcolor, sf::Color textcolor, int textsize);

	void update(std::string phrase);

	void render(sf::RenderWindow& window, float posX, float posY);
};
