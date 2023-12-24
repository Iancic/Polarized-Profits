#include "TextUI.h"

TextUI::TextUI(sf::Color textcolor, int size)
{
	roboto.loadFromFile("Assets/Fonts/DiloWorld-mLJLv.ttf");
	text.setFont(roboto);
	text.setFillColor(textcolor);
	text.setCharacterSize(size);
	text.setOutlineThickness(2.f);
	text.setOutlineColor(sf::Color::Black);
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

