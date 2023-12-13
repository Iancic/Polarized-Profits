#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TextUI 
{

public:

	sf::Font roboto;
	sf::Text text;

	std::string concat;

	//Constructor
	TextUI(sf::Color textcolor, int size)
	{
		roboto.loadFromFile("Assets/Fonts/Preahvihear-Regular.ttf");
		text.setFont(roboto);
		text.setFillColor(textcolor);
		text.setCharacterSize(size);
	}

	void update(std::string phrase, bool simple, int value)
	{
		if (simple)
			text.setString(phrase);
		else
		{
			concat = std::to_string(value) + " " + phrase;
			text.setString(concat);
		}
	}

	void render(sf::RenderWindow& window, float posX, float posY)
	{
		text.setPosition(posX, posY);
		window.draw(text);
	}
};
