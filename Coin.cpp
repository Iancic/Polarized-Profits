#include "Coin.h"

Coin::Coin(int type, float vel_x, float vel_y, int windowWidth, int windowHeight)
{
	coinType = type;
	vel.x = vel_x;
	vel.y = vel_y;

	//Coin Value By Type
	if (coinType == 0 || coinType == 2)
		value = 3;

	else if (coinType == 1)
		value = 1;

	else if (coinType == 3)
		value = 5;

	initTexture();
	initSprite();
	spawnCoin(windowWidth, windowHeight);
}

void Coin::initTexture()
{
	coinCopper = new sf::Texture;
	coinCopper->loadFromFile("Assets/Sprites/Coins/CopperCoin.png");

	coinSilver = new sf::Texture;
	coinSilver->loadFromFile("Assets/Sprites/Coins/SilverCoin.png");

	coinGold = new sf::Texture;
	coinGold->loadFromFile("Assets/Sprites/Coins/GoldCoin.png");
}

void Coin::initSprite()
{
	if (coinType == 0 || coinType == 2)
		sprite.setTexture(*coinSilver);

	else if (coinType == 1)
		sprite.setTexture(*coinCopper);

	else if (coinType == 3)
		sprite.setTexture(*coinGold);

	sprite.setScale(scale, scale);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}

void Coin::render(sf::RenderWindow& window)
{
	sprite.setPosition(pos);
	window.draw(sprite);
}

void::Coin::spawnCoin(int windowWidth, int windowHeight)
{
	//Coin Spawn Based On Box Offset
	float boundsScale = 0.18f;

	float minMargin = 0.f + boundsScale;
	float maxMargin = 1.f - boundsScale;

	float offsetX = windowWidth * minMargin;
	float rangeX = windowWidth * maxMargin;

	pos.x = offsetX + static_cast<float>(rand() % static_cast<int>(rangeX - offsetX));
	pos.y = -200.f;
}

void Coin::updatePhysics(Magnet& s)
{
	//Distance
	float distance_x = s.get_pos().x - pos.x;
	float distance_y = s.get_pos().y - pos.y;
	float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	if (distance < 300.f)
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
			pos.x += vel.x * 1.3f;
			pos.y += vel.y * 1.3f;
			vel.y = 0;
		}

		//-velocity when in denial polarity
		else if (s.get_state() == false)
		{
			pos.y -= vel.y * 1.5f;
			vel.x = 0;
			vel.y = 0;
		}
	}

	else
		fallPhysics();
}

void Coin::fallPhysics()
{
	vel.y += fallSpeed;
	pos.y += vel.y * 2.f;
}