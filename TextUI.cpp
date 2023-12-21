#include "TextUI.h"

TextUI::TextUI(sf::Color textcolor, int size)
{
	roboto.loadFromFile("Assets/Fonts/NTR-Regular.ttf");
	text.setFont(roboto);
	text.setFillColor(textcolor);
	text.setCharacterSize(size);
}

void TextUI::update(std::string phrase, bool simple, int value)
{
	if (simple)
		text.setString(phrase);
	else
	{
		concat = std::to_string(value) + " " + phrase;
		text.setString(concat);
	}
}

void TextUI::render(sf::RenderWindow& window, float posX, float posY)
{
	text.setPosition(posX, posY);
	window.draw(text);
}

