#include "Magnet.h"

Magnet::Magnet(float pos_x, float pos_y)
{
	initTexture();
	initSprite();

	pos.x = pos_x;
	pos.y = pos_y;
}

void Magnet::initTexture()
{
	magnettexture = new sf::Texture;
	magnettexture->loadFromFile("Assets/Sprites/Magnet.png");
}

void Magnet::initSprite()
{
	magnetsprite.setTexture(*magnettexture);
	magnetsprite.setScale(scale, scale);
	magnetsprite.setOrigin(magnetsprite.getTexture()->getSize().x / 2, magnetsprite.getTexture()->getSize().y / 2);

	radiusEffect.setRadius(radius);
	radiusEffect.setFillColor(sf::Color::Transparent);
	radiusEffect.setOutlineThickness(1.5f);
	radiusEffect.setOutlineColor(sf::Color::White);
	radiusEffect.setOrigin(radius, radius);
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
	pos.x += dirRight;
	pos.x -= dirLeft;
	pos.y += dirDown;
	pos.y -= dirUp;
}

sf::Vector2f Magnet::get_pos()
{
	return pos;
}

float Magnet::get_speed()
{
	return movespeed;
}

void Magnet::change_state()
{
	if (state == true)
		state = false;
	else if (state == false)
		state = true;
}

bool Magnet::get_state()
{
	return state;
}

sf::Color Magnet::return_state_color()
{
	if (state == true)
		return sf::Color(232, 42, 42);
	else if (state == false)
		return sf::Color(59, 204, 212);
}