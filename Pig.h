#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

class Pig
{

public:

	sf::Vector2f pos;

	//Every 7 seconds the pig changes position
	float maxTime = 7.f, timer = 0.f;

	sf::Texture* pigtexture;
	sf::Sprite sprite;

	//Constructor
	Pig(float pos_x, float pos_y);

	//Initial Texture Settings
	void initTexture();

	//Initial Sprite Settings
	void initSprite();

	//Changes The Pig position Based On Timer
	void changePos(sf::RenderWindow& window, sf::Time counter);

	//Render Pig
	void render(sf::RenderWindow& window);
};