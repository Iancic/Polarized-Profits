#include "Button.h"

Button::Button(float sizeX, float sizeY, sf::Color boxcolor, sf::Color textcolor, int textsize)
{

	//Box
	buttonBox.setPosition(pos.x, pos.y);
	buttonBox.setSize(sf::Vector2f(sizeX, sizeY));
	buttonBox.setFillColor(boxcolor);

	//Text
	roboto.loadFromFile("Assets/Fonts/DiloWorld-mLJLv.ttf");
	text.setFont(roboto);
	text.setFillColor(textcolor);
	text.setCharacterSize(textsize);
	text.setOutlineThickness(2.f);
	text.setOutlineColor(sf::Color::Black);
}

void Button::update(std::string phrase)
{
	text.setString(phrase);
}

void Button::render(sf::RenderWindow& window, float posX, float posY)
{
	buttonBox.setPosition(posX, posY);
	window.draw(buttonBox);
	text.setPosition(posX + 100.f, posY + 25.f);
	window.draw(text);
}
