#include "Coin.h"

//Constructor
Coin::Coin(float vel_x, float vel_y, float coinValue)
{
	initTexture();
	initSprite();

	float offsetX = 100.f;

	pos.x = offsetX + static_cast<float>(rand() % static_cast<int>(700.f));
	pos.y = -50.f;

	vel.x = vel_x;
	vel.y = vel_y;

	this->value = coinValue;
}

//Initial Texture Settings
void Coin::initTexture()
{
	cointexture = new sf::Texture;
	cointexture->loadFromFile("Assets/Sprites/Coin_V2.png");
}

//Initial Sprite Settings
void Coin::initSprite()
{
	sprite.setTexture(*cointexture);
	sprite.setScale(0.17f, 0.17f);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y * 0.5f / 2);
}

//Render Coin
void Coin::render(sf::RenderWindow& window)
{
	window.draw(sprite);
	sprite.setPosition(pos);
}

//Movement Interaction With The Magnet
void Coin::update_physics(Magnet& s)
{
	//Lenght between Magnet and Coin on X and Y.
	float distance_x = s.get_pos().x - pos.x;
	float distance_y = s.get_pos().y - pos.y;

	//Distance Formula(Pythagoras).
	float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	if (distance < 350.f)
	{

		//Make A Vector Out Of Distance With Normalization
		//Divide each component (triangle lenght) by the distance inverse.

		float inverse_distance = 1.f / distance;

		float normalized_x = inverse_distance * distance_x;
		float normalized_y = inverse_distance * distance_y;

		vel.x += normalized_x;
		vel.y += normalized_y;

		//Apply -velocity when in denial state and +velocity when in attraction state.
		if (s.get_state() == true)
		{
			pos.x += vel.x;
			pos.y += vel.y;
			vel.y = 0;
		}

		//Also check for distance on X when pushing because coins can fall beside you.
		else if (s.get_state() == false)
		{
			pos.y -= vel.y;
			vel.x = 0;
			// Reset Wave Motion On X From Attraction
			vel.y = 0;
		}
	}
	else
	{
		vel.y += fallSpeed;
		pos.y += vel.y;
	}
	//If Coin Is Not Attracted Then It just falls.
}

sf::Vector2f Coin::get_pos()
{
	return pos;
}