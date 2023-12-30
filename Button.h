#pragma once
#include <SFML/Graphics.hpp>

#include "TextUI.h"

class Button
{

public:

	sf::Vector2f pos;
	sf::Text text;
	sf::Font roboto;
	sf::Texture* buttonTexture;
	sf::Texture* hoverTexture;
	sf::Sprite buttonSprite;

	float buttonLenght;
	float buttonHeight;

	Button(float sizeX, float sizeY, sf::Color boxcolor, sf::Color textcolor, int textsize);

	void initTexture();

	void initSprite(float sizeX, float sizeY);

	void initText(sf::Color textcolor, int textsize);

	void update(sf::RenderWindow& window, sf::Vector2i mousePosWindow, std::string phrase);

	void render(sf::RenderWindow& window, float posX, float posY);
};
