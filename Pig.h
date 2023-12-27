#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

class Pig
{

public:

	sf::Vector2f pos;

	sf::Texture* pigtexture;
	sf::Sprite sprite;

	float maxTime = 9.f, timer = 0.f;

	float scale = 0.18f;

	Pig(float pos_x, float pos_y);

	void initTexture();

	void initSprite();

	void changePos(sf::RenderWindow& window, sf::Time counter);

	void render(sf::RenderWindow& window);
};