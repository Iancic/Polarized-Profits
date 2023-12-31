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
	inTexture1 = new sf::Texture;
	inTexture2 = new sf::Texture;
	inTexture3 = new sf::Texture;

	if (hand_type)
	{
		inTexture1->loadFromFile("Assets/Sprites/Hands/in_01d.png");
		inTexture2->loadFromFile("Assets/Sprites/Hands/in_02d.png");
		inTexture3->loadFromFile("Assets/Sprites/Hands/in_03d.png");
	}
	else
	{
		inTexture1->loadFromFile("Assets/Sprites/Hands/in_01s.png");
		inTexture2->loadFromFile("Assets/Sprites/Hands/in_02s.png");
		inTexture3->loadFromFile("Assets/Sprites/Hands/in_03s.png");
	}

	outTexture = new sf::Texture;
	if (hand_type)
	{
		outTexture->loadFromFile("Assets/Sprites/Hands/out_01d.png");
	}
	else
	{
		outTexture->loadFromFile("Assets/Sprites/Hands/out_01s.png");
	}
}

void Hand::initSprite()
{
	sprite_hand.setTexture(*inTexture1);
	sprite_hand.setScale(scale, scale);

	if (hand_type)
		sprite_hand.setOrigin(0.f, sprite_hand.getTexture()->getSize().y / 2);
	else 
		sprite_hand.setOrigin(sprite_hand.getTexture()->getSize().x, sprite_hand.getTexture()->getSize().y / 2);
}

void Hand::magnetPhysics(Magnet& s)
{
	float distance_x = s.get_pos().x - pos.x;

	if (distance_x < 500.f)
	{
		if (s.get_state() == false)
		{
			if (hand_type)
				pos.x += retractSpeed;
			else 
				pos.x -= retractSpeed;
		}
	}
}

void Hand::moveHand(std::vector<Coin>& coins)
{
	if (changeTexture == true)
	{
		int random = (rand() % 3) + 1;

		if (random == 1)
			sprite_hand.setTexture(*inTexture1);
		else if (random == 2)
			sprite_hand.setTexture(*inTexture2);
		else if (random == 3)
			sprite_hand.setTexture(*inTexture3);

		changeTexture = false;
	}

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

void Hand::retractHand()
{
	changeTexture = true;

	sprite_hand.setTexture(*outTexture);

	if (hand_type == false)
		pos.x -= retractSpeed;
	else if (hand_type == true)
		pos.x += retractSpeed;

	if (hand_type == false && pos.x < -50.f)
		retracting = false;
	if (hand_type == true && pos.x > 1300.f)
		retracting = false;
}

void Hand::render(sf::RenderWindow& window)
{
	sprite_hand.setPosition(pos);
	window.draw(sprite_hand);
}