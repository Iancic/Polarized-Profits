#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#include "Coin.h"

class Hand
{

public:

	sf::Vector2f pos;

	sf::Texture* handtexture;
	sf::Sprite sprite_hand;

	sf::Texture* handtexture_failure;
	sf::Sprite sprite_failure;

	sf::Texture* handtexture_succes;
	sf::Sprite sprite_succes;

	bool hand_type; //if true type is right, if false type is left
	bool targetCoin = false;

	int timer = 0.1f;
	int maxTime = 60.f; //Lifetime of hand
	int moveSpeed = 1.f;
	int randomCoinPos;

	float distance_x, distance_y;

	Hand(bool type); //if true type is right, if false type is left

	void initTexture();

	void initSprite();

	void moveHand(std::vector<Coin>& coins);

	void render(sf::RenderWindow& window);
};