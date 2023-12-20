#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Magnet.h"

class Coin
{

public:

	sf::Vector2f pos;
	sf::Vector2f vel;

	sf::Texture* cointexture;
	sf::Sprite sprite;

	float fallSpeed = 0.02f;
	float value;

	Coin(float vel_x, float vel_y, float coinValue);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void update_physics(Magnet& s);

	sf::Vector2f get_pos();
};