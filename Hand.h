#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Hand
{

public:

	sf::Vector2f pos;

	sf::Texture* handtexture;
	sf::Sprite sprite;

	//Constructor
	Hand(float pos_x, float pos_y)
	{
		initTexture();
		initSprite();

		pos.x = pos_x;
		pos.y = pos_y;
	}

	//Initial Texture Settings
	void initTexture()
	{
		handtexture = new sf::Texture;
		handtexture->loadFromFile("");
	}

	//Initial Sprite Settings
	void initSprite()
	{
		sprite.setTexture(*handtexture);
		sprite.setScale(0.3f, 0.3f);
		sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y * 0.5f / 2);
	}

	//Render Hand
	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
		sprite.setPosition(pos);
	}

};