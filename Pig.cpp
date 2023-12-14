#include "Pig.h"

//Constructor
Pig::Pig(float pos_x, float pos_y)
{
	pos.x = pos_x;
	pos.y = pos_y;

	initTexture();
	initSprite();
}

//Initial Texture Settings
void Pig::initTexture()
{
	pigtexture = new sf::Texture;
	pigtexture->loadFromFile("Assets/Sprites/Pig.png");
}

//Initial Sprite Settings
void Pig::initSprite()
{
	sprite.setTexture(*pigtexture);
	sprite.setScale(0.07f, 0.07f);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y * 0.5f / 2);
}

//Changes The Pig position Based On Timer
void Pig::changePos(sf::RenderWindow& window, sf::Time counter)
{
	if (timer >= maxTime)
	{
		timer = 0.f;

		//Set The Bounds scale
		float boundsScale = 0.20f;
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

//Render Pig
void Pig::render(sf::RenderWindow& window)
{
	window.draw(sprite);
	sprite.setPosition(pos);
}