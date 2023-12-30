#include "Button.h"

Button::Button(float sizeX, float sizeY, sf::Color boxcolor, sf::Color textcolor, int textsize)
{
	buttonLenght = sizeX;
	buttonHeight = sizeY;

	//Sprite
	buttonTexture = new sf::Texture;
	hoverTexture = new sf::Texture;
	buttonTexture->loadFromFile("Assets/Sprites/RedButton.png");
	hoverTexture->loadFromFile("Assets/Sprites/BlueButton.png");

	buttonSprite.setTexture(*buttonTexture);
	buttonSprite.setScale(sf::Vector2f(sizeX, sizeY));
	buttonSprite.setOrigin(buttonSprite.getTexture()->getSize().x / 2, buttonSprite.getTexture()->getSize().y / 2);

	//Text
	roboto.loadFromFile("Assets/Fonts/DiloWorld-mLJLv.ttf");
	text.setFont(roboto);
	text.setFillColor(textcolor);
	text.setCharacterSize(textsize);
	text.setOutlineThickness(2.f);
	text.setOutlineColor(sf::Color::Black);
}

void Button::update(sf::RenderWindow& window, sf::Vector2i mousePosWindow, std::string phrase)
{
	if (buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
	{
		buttonSprite.setTexture(*hoverTexture);
	}
	else 
		buttonSprite.setTexture(*buttonTexture);

	text.setString(phrase);
}

void Button::render(sf::RenderWindow& window, float posX, float posY)
{
	buttonSprite.setPosition(posX, posY);
	window.draw(buttonSprite);

	//Align the Text In The Middle. Box Position + Box Lenght/Height divided by 2 = Middle of the Box + middle of the Text. 
	text.setPosition(posX + buttonLenght / 2 - text.getLocalBounds().width / 2, posY + buttonHeight / 2 - text.getLocalBounds().height / 2);
	window.draw(text);
}
