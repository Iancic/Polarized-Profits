#include "Coin.h"

Coin::Coin(int type, float vel_x, float vel_y, int windowWidth, int windowHeight)
{
	coinType = type;

	initTexture();
	initSprite();
	spawnCoin(windowWidth, windowHeight);

	vel.x = vel_x;
	vel.y = vel_y;
}

void Coin::initTexture()
{
	blurredCoin = new sf::Texture;
	blurredCoin->loadFromFile("Assets/Sprites/BlurredCoin.png");

	coinCopper = new sf::Texture;
	coinCopper->loadFromFile("Assets/Sprites/CopperCoin.png");

	coinSilver = new sf::Texture;
	coinSilver->loadFromFile("Assets/Sprites/SilverCoin.png");

	coinGold = new sf::Texture;
	coinGold->loadFromFile("Assets/Sprites/GoldCoin.png");
}

void Coin::initSprite()
{
	if (coinType == 0)
	{
		sprite.setTexture(*blurredCoin);
		value = 0;
	}
	if (coinType == 1)
	{
		sprite.setTexture(*coinCopper);
		value = 1;
	}
	else if (coinType == 2)
	{
		sprite.setTexture(*coinSilver);
		value = 2;
	}
	else if (coinType == 3)
	{
		sprite.setTexture(*coinGold);
		value = 3;
	}

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
	//If the coins is not a main menu coin then spawn it with bounds. Else spawn coin on full screen.
	if (coinType != 0)
	{
		float boundsScale = 0.2f;

		float minMargin = 0.f + boundsScale;
		float maxMargin = 1.f - boundsScale;

		float offsetX = windowWidth * minMargin;
		float rangeX = windowWidth * maxMargin;

		pos.x = offsetX + static_cast<float>(rand() % static_cast<int>(rangeX - offsetX));
		pos.y = -200.f;
	}

	else
	{
		pos.x = static_cast<float>(rand() % windowWidth);
		pos.y = 0.f;
	}

}


//Movement Interaction With The Magnet
void Coin::update_physics(Magnet& s)
{
	//Lenght between Magnet and Coin on X and Y.
	float distance_x = s.get_pos().x - pos.x;
	float distance_y = s.get_pos().y - pos.y;

	//Pythagoras
	float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	if (distance < 330.f)
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
			pos.x += vel.x * 3.f;
			pos.y += vel.y * 3.f;
			vel.x = 0;
			vel.y = 0;
		}

		//-velocity when in denial polarity
		else if (s.get_state() == false)
		{
			pos.y -= vel.y * 1.8f;
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

void Coin::fall_physics()
{
	vel.y += fallSpeed;
	pos.y += vel.y * 1.4f;
}

sf::Vector2f Coin::get_pos()
{
	return pos;
}