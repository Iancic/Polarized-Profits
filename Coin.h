#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Magnet.h"

class Coin
{

public:

	sf::Vector2f pos;
	sf::Vector2f vel;

	float fallSpeed = 0.01f;

	sf::Texture* cointexture;
	sf::Sprite sprite;

	float value;

	//Constructor
	Coin(float vel_x, float vel_y, float coinValue);

	//Initial Texture Settings
	void initTexture();

	//Initial Sprite Settings
	void initSprite();

	//Render Coin
	void render(sf::RenderWindow& window);

	//Movement Interaction With The Magnet
	void update_physics(Magnet& s);

	sf::Vector2f get_pos();
};