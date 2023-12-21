#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Magnet
{

public:


	sf::Texture* magnettexture;
	sf::Sprite magnetsprite;
	sf::CircleShape radiusEffect;

	sf::Vector2f pos;

	float scale = 0.16f;
	float movespeed = 6.f;
	float radius = 200.f;

	bool state = true; //True Means + Polarity (Attraction) & False Mean - Polarity

	Magnet(float pos_x, float pos_y);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void changePos(float dirRight, float dirLeft, float dirDown, float dirUp);

	void change_state();

	float get_speed();

	bool get_state();

	sf::Color return_state_color();

	sf::Vector2f get_pos();
};