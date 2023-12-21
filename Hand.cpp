#include "Hand.h"

Hand::Hand(bool type, int windowHeight, int windowWidth)
{
	hand_type = type;

	if (hand_type)
	{
		pos.y = windowHeight / 2;
		pos.x = windowWidth + 200.f;
	}
	else
	{
		pos.y = windowHeight / 2;
		pos.x = -200.f;
	}

	initTexture();
	initSprite();
}

void Hand::initTexture()
{
	handtexture = new sf::Texture;
	if (hand_type)
		handtexture->loadFromFile("Assets/Sprites/Right_Hand.png");
	else
		handtexture->loadFromFile("Assets/Sprites/Left_Hand.png");
}

void Hand::initSprite()
{
	sprite_hand.setTexture(*handtexture);
	sprite_hand.setScale(1.f, 1.f);

	if (hand_type)
		sprite_hand.setOrigin(0.f, sprite_hand.getTexture()->getSize().y / 2);
	else 
		sprite_hand.setOrigin(sprite_hand.getTexture()->getSize().x, sprite_hand.getTexture()->getSize().y / 2);
}

void Hand::moveHand(std::vector<Coin>& coins)
{
	if (coins.empty())
		return;

	float distance_x = coins[0].pos.x - pos.x;
	float distance_y = coins[0].pos.y - pos.y;

	if (std::abs(distance_x) > moveSpeed || std::abs(distance_y) > moveSpeed) {
		if (distance_x > 0.f)
			pos.x += moveSpeed;
		else if (distance_x < 0.f)
			pos.x -= moveSpeed;

		if (distance_y > 0.f)
			pos.y += moveSpeed;
		else if (distance_y < 0.f)
			pos.y -= moveSpeed;
	}
}

void Hand::render(sf::RenderWindow& window)
{
	sprite_hand.setPosition(pos);
	window.draw(sprite_hand);
}