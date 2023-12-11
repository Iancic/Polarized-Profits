#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Coin
{

public:

	sf::Vector2f pos;
	sf::Vector2f vel;

	float acceleration_x;
	float acceleration_y;

	sf::Texture* cointexture;
	sf::Sprite sprite;

	//Constructor
	Coin(float pos_x, float pos_y, float vel_x, float vel_y)
	{
		initTexture();
		initSprite();

		pos.x = pos_x;
		pos.y = pos_y;

		vel.x = vel_x;
		vel.y = vel_y;
	}

	//Initial Texture Settings
	void initTexture()
	{
		cointexture = new sf::Texture;
		cointexture -> loadFromFile("Assets/Sprites/Lincoin.png");
	}

	//Initial Sprite Settings
	void initSprite()
	{
		sprite.setTexture(*cointexture);
		sprite.setScale(0.3f, 0.3f);
		sprite.setOrigin(sprite.getTexture()->getSize().x /2 , sprite.getTexture()->getSize().y * 0.5f /2);
	}

	//Render Coin
	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
		sprite.setPosition(pos);
	}

	sf::Vector2f get_pos()
	{
		return pos;
	}

	//Movement Interaction With The Magnet
	void update_physics(Magnet& s)
	{
		//Lenght between Magnet and Coin on X and Y.
		float distance_x = s.get_pos().x - pos.x;
		float distance_y = s.get_pos().y - pos.y;

		//Distance Formula(Pythagoras).
		float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

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
			vel.x = 0;
			vel.y = 0;
		}
		else
		{
			pos.x -= vel.x;
			pos.y -= vel.y;
			vel.x = 0;
			vel.y = 0;
		}
	}
};