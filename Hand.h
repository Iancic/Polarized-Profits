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
	sf::Texture* outTexture;
	sf::Texture* inTexture1;
	sf::Texture* inTexture2;
	sf::Texture* inTexture3;
	sf::Sprite sprite_hand;

	bool hand_type; //if true type is right, if false type is left
	bool retracting = false;
	bool changeTexture = true;

	int timer = 0.1f;
	int maxTime = 60.f; //Lifetime of hand
	int moveSpeed = 1.f;
	int randomCoinPos;

	float distance_x, distance_y;
	float scale = 0.28f;

	Hand(bool type, int windowHeight, int windowWidth);

	void initTexture();

	void initSprite();

	void moveHand(std::vector<Coin>& coins);

	void retractHand();

	void render(sf::RenderWindow& window);
};