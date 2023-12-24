#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Transition
{

public:

	sf::Vector2f pos;
	sf::RectangleShape box;
	
	float size;
	float scale = 1.f;

	Transition(float posX, float posY);

	void initSprite();

	void render(sf::RenderWindow& window);

	void update();
};