#include "Pig.h"

Pig::Pig(float pos_x, float pos_y)
{
	pos.x = pos_x;
	pos.y = pos_y;

	initTexture();
	initSprite();
}

void Pig::initTexture()
{
	pigtexture = new sf::Texture;
	pigtexture->loadFromFile("Assets/Sprites/Pig.png");
}

void Pig::initSprite()
{
	sprite.setTexture(*pigtexture);
	sprite.setScale(scale, scale);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y * 0.5f / 2);
}

void Pig::changePos(sf::RenderWindow& window, sf::Time counter)
{
	if (timer >= maxTime)
	{
		timer = 0.f;

		//Set The Bounds scale
		float boundsScale = 0.25f;
		float minMargin = 0.f + boundsScale;
		float maxMargin = 1.f - boundsScale;

		//Based On Window Size calculate percentages.
		//Minnimum Offset
		float offsetX = window.getSize().x * minMargin;
		float offsetY = window.getSize().y * minMargin;

		//Maxim  Offset
		float rangeX = window.getSize().x * maxMargin;
		float rangeY = window.getSize().y * maxMargin;

		//First it generates one from 0 -> Max% then adds Min.
		pos.x = offsetX + static_cast<float>(rand() % static_cast<int>(rangeX - offsetX));
		pos.y = offsetY + static_cast<float>(rand() % static_cast<int>(rangeY - offsetY));
	}
	else
	{
		timer += counter.asSeconds();
	}
}

void Pig::render(sf::RenderWindow& window)
{
	window.draw(sprite);
	sprite.setPosition(pos);
}