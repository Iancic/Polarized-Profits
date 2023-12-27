#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Magnet
{

public:

	sf::Texture* magnettextureBlue;
	sf::Texture* magnettextureRed;
	sf::Texture* wallettexture;
	sf::Sprite magnetsprite;
	sf::CircleShape radiusEffect;

	sf::Vector2f pos;

	float scale = 0.165f;
	float magnetSpeed;
	float radius = 200.f;

	bool state = true; //True Means - Polarity (Attraction) & False Mean + Polarity
	bool wallet = false;

	Magnet(float pos_x, float pos_y, float moveSpeed, bool wallet);

	void initTexture();

	void initSprite();

	void render(sf::RenderWindow& window);

	void changePos(float dirRight, float dirLeft, float dirDown, float dirUp);

	void changeHorizontal(float dirRight, float dirLeft);

	void change_state();

	float get_speed();

	bool get_state();

	sf::Vector2f get_pos();
};