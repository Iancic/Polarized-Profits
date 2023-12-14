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
	TextUI(sf::Color textcolor, int size);

	void update(std::string phrase, bool simple, int value);

	void render(sf::RenderWindow& window, float posX, float posY);
};
