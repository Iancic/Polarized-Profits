#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Transition
{

public:

	sf::Vector2f pos;
	sf::Vector2f currentSize;
	sf::RectangleShape box;

	int alpha = 255;

	float fadeSpeedFinal = 500.f;
	float fadeSpeedStart = 1.f;
	float sizeX;
	float sizeY;

	Transition(int windowHeight, int windowWidth);

	void initSprite();

	void fadeIn(sf::Time deltaTime);

	void fadeOut(sf::Time deltaTime);

	void render(sf::RenderWindow& window);
};