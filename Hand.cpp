#include "Hand.h"

//Constructor
Hand::Hand(bool type) //if true type is right, if false type is left
{
	hand_type = type;
	initTexture();
	initSprite();

	pos.y = static_cast<float>(rand() % static_cast<int>(800.f));
	pos.x = 800.f;
}

//Initial Texture Settings
void Hand::initTexture()
{
	handtexture = new sf::Texture;
	if (hand_type)
		handtexture->loadFromFile("");
}

//Initial Sprite Settings
void Hand::initSprite()
{
	sprite_hand.setTexture(*handtexture);
	sprite_hand.setScale(0.3f, 0.3f);
	sprite_hand.setOrigin(sprite_hand.getTexture()->getSize().x / 2, sprite_hand.getTexture()->getSize().y * 0.5f / 2);
}

//Render Hand
void Hand::render(sf::RenderWindow& window)
{
	window.draw(sprite_hand);
	sprite_hand.setPosition(pos);
}