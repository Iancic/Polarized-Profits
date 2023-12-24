#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Magnet
{

public:


	sf::Texture* magnettextureBlue;
	sf::Texture* magnettextureRed;
	sf::Sprite magnetsprite;
	sf::CircleShape radiusEffect;

	sf::Vector2f pos;

	float scale = 0.18f;
	float movespeed = 4.f;
	float radius = 200.f;

	bool state = true; //True Means - Polarity (Attraction) & False Mean + Polarity

	Magnet(float pos_x, float pos_y);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void changePos(float dirRight, float dirLeft, float dirDown, float dirUp);

	void change_state();

	float get_speed();

	bool get_state();

	sf::Vector2f get_pos();
};