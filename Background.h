#pragma once
#include <SFML/Graphics.hpp>

class Background 
{

public:

	sf::Texture* backgroundBlue;
	sf::Texture* backgroundRed;
	sf::Sprite backgroundSprite;

	sf::Vector2f pos;

	Background(float pos_x, float pos_y);

	void initTexture();

	void initSprite();

	void change_state(bool state);

	void render(sf::RenderWindow& window);

};