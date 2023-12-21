#include "Coin.h"

Coin::Coin(float vel_x, float vel_y, float coinValue, int windowWidth, int windowHeight)
{
	initTexture();
	initSprite();

	float boundsScale = 0.2f;

	float minMargin = 0.f + boundsScale;
	float maxMargin = 1.f - boundsScale;

	float offsetX = windowWidth * minMargin;
	float rangeX = windowWidth * maxMargin;

	pos.x = offsetX + static_cast<float>(rand() % static_cast<int>(rangeX - offsetX));
	pos.y = -50.f;

	vel.x = vel_x;
	vel.y = vel_y;

	value = coinValue;
}

void Coin::initTexture()
{
	cointexture = new sf::Texture;
	cointexture->loadFromFile("Assets/Sprites/Coin_V2.png");
}

void Coin::initSprite()
{
	sprite.setTexture(*cointexture);
	sprite.setScale(scale, scale);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}

void Coin::render(sf::RenderWindow& window)
{
	sprite.setPosition(pos);
	window.draw(sprite);
}

//Movement Interaction With The Magnet
void Coin::update_physics(Magnet& s)
{
	//Lenght between Magnet and Coin on X and Y.
	float distance_x = s.get_pos().x - pos.x;
	float distance_y = s.get_pos().y - pos.y;

	//Pythagoras
	float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	if (distance < 250.f)
	{
		//Divide each component (triangle lenght) by the distance inverse (normalization).

		float inverse_distance = 1.f / distance;

		float normalized_x = inverse_distance * distance_x;
		float normalized_y = inverse_distance * distance_y;

		vel.x += normalized_x;
		vel.y += normalized_y;

		//+velocity when in attraction polarity
		if (s.get_state() == true)
		{
			pos.x += vel.x;
			pos.y += vel.y;
			vel.y = 0;
		}

		//-velocity when in denial polarity
		else if (s.get_state() == false)
		{
			pos.y -= vel.y;
			vel.x = 0;
			vel.y = 0;
		}
	}

	else
	{
		//If Coin Is Not Attracted Then It just falls.
		vel.y += fallSpeed;
		pos.y += vel.y;
	}
}

sf::Vector2f Coin::get_pos()
{
	return pos;
}