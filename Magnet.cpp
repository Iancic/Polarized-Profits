#include "Magnet.h"

Magnet::Magnet(float pos_x, float pos_y, float moveSpeed, bool isWallet)
{
	this->magnetSpeed = moveSpeed;
	wallet = isWallet;

	initTexture();
	initSprite();

	pos.x = pos_x;
	pos.y = pos_y;
}

void Magnet::initTexture()
{
		wallettexture = new sf::Texture;
		wallettexture->loadFromFile("Assets/Sprites/Entities/Wallet.png");

		magnettextureBlue = new sf::Texture;
		magnettextureBlue->loadFromFile("Assets/Sprites/Entities/BlueMagnet.png");

		magnettextureRed = new sf::Texture;
		magnettextureRed->loadFromFile("Assets/Sprites/Entities/RedMagnet.png");
}

void Magnet::initSprite()
{
	//If The Magnet Is Wallet Type
	if (wallet == true)
	{
		magnetsprite.setTexture(*wallettexture);
		magnetsprite.setScale(walletScale, walletScale);
		magnetsprite.setOrigin(magnetsprite.getTexture()->getSize().x / 2, magnetsprite.getTexture()->getSize().y / 2);
	}

	//If The Magnet is Blue Red Type
	else
	{
		magnetsprite.setTexture(*magnettextureRed);
		magnetsprite.setScale(scale, scale);
		magnetsprite.setOrigin(magnetsprite.getTexture()->getSize().x / 2, magnetsprite.getTexture()->getSize().y / 2);

		radiusEffect.setRadius(radius);
		radiusEffect.setFillColor(sf::Color::Transparent);
		radiusEffect.setOutlineThickness(1.5f);
		radiusEffect.setOutlineColor(sf::Color::White);
		radiusEffect.setOrigin(radius, radius);
	}
}

void Magnet::render(sf::RenderWindow& window)
{
	radiusEffect.setPosition(pos);
	window.draw(radiusEffect);

	magnetsprite.setPosition(pos);
	window.draw(magnetsprite);
}

void Magnet::changePos(float dirRight, float dirLeft, float dirDown, float dirUp)
{
	pos.x += dirRight * magnetSpeed;
	pos.x -= dirLeft * magnetSpeed;
	pos.y += dirDown * magnetSpeed;
	pos.y -= dirUp * magnetSpeed;
}

void Magnet::changeHorizontal(float dirRight, float dirLeft)
{
	pos.x += dirRight * magnetSpeed;
	pos.x -= dirLeft * magnetSpeed;
}

sf::Vector2f Magnet::get_pos()
{
	return pos;
}

float Magnet::get_speed()
{
	return magnetSpeed;
}

void Magnet::change_state()
{
	if (state == true)
	{
		state = false;
		magnetsprite.setTexture(*magnettextureBlue);
	}
	else if (state == false)
	{
		state = true;
		magnetsprite.setTexture(*magnettextureRed);
	}
}

bool Magnet::get_state()
{
	return state;
}