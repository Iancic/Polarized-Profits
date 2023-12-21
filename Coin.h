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

	float scale = 0.14f;
	float fallSpeed = 0.005f;
	float value;

	Coin(float vel_x, float vel_y, float coinValue, int windowWidth, int windowHeight);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void update_physics(Magnet& s);

	sf::Vector2f get_pos();
};