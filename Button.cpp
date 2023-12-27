#include "Button.h"

Button::Button(float sizeX, float sizeY, sf::Color boxcolor, sf::Color textcolor, int textsize)
{
	boxLenght = sizeX;
	boxHeight = sizeY;

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

	//Align the Text In The Middle. Box Position + Box Lenght/Height divided by 2 = Middle of the Box + middle of the Text. 
	text.setPosition(posX + boxLenght / 2 - text.getLocalBounds().width / 2, posY + boxHeight / 2 - text.getLocalBounds().height / 2);
	window.draw(text);
}
