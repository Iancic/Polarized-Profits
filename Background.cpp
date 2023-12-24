#include "Background.h"

Background::Background(float pos_x, float pos_y)
{
	initTexture();
	initSprite();

	pos.x = pos_x;
	pos.y = pos_y;
}

void Background::initTexture()
{
	backgroundBlue = new sf::Texture;
	backgroundBlue->loadFromFile("Assets/Sprites/BlueBackground.png");

	backgroundRed = new sf::Texture;
	backgroundRed->loadFromFile("Assets/Sprites/RedBackground.png");
}

void Background::initSprite()
{
	backgroundSprite.setTexture(*backgroundRed);
}

void Background::change_state(bool state)
{
	if (state == true)
	{
		state = false;
		backgroundSprite.setTexture(*backgroundRed);
	}
	else if (state == false)
	{
		state = true;
		backgroundSprite.setTexture(*backgroundBlue);
	}
}

void Background::render(sf::RenderWindow& window)
{
	backgroundSprite.setPosition(pos);
	window.draw(backgroundSprite);
}
