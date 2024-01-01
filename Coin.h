#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Magnet.h"

class Coin
{

public:

	sf::Vector2f pos;
	sf::Vector2f vel;

	sf::Texture* coinCopper;
	sf::Texture* coinSilver;
	sf::Texture* coinGold;
	sf::Sprite sprite;

	float scale = 0.12f;
	float fallSpeed = 0.005f;

	int value;
	int coinType; // 0 for Main Menu, 1 Cooper, 2 Silver, 3 Gold

	Coin(int type, float vel_x, float vel_y, int windowWidth, int windowHeight);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void spawnCoin(int windowWidth, int windowHeight);

	void updatePhysics(Magnet& s);

	void fallPhysics();
};