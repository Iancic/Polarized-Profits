#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Magnet
{

public:
	sf::Vector2f pos;
	float movespeed = 6.f;
	float strenght;

	//True Means + Polarity (Attraction) & False Mean - Polarity
	bool state = true; 

	sf::Texture* magnettexture;
	sf::Sprite magnetsprite;

	//Constructor
	Magnet(float pos_x, float pos_y, float strenght);

	//Initial Texture Settings
	void initTexture();

	//Initial Sprite Settings
	void initSprite();

	//Render Magnet
	void render(sf::RenderWindow& window);

	//Function That Gets Called Every Frame And Moves The Magnet On All Axis
	void changePos(float dirRight, float dirLeft, float dirDown, float dirUp);

	//Return Vector2 That Stores Position X & Y
	sf::Vector2f get_pos();

	//Return Float That Stores Strenght
	float get_strenght();

	//Return Float That Stores Speed
	float get_speed();

	//Change state of polarity
	void change_state();

	//Get state of polarity
	bool get_state();

	//Return background color in regards to polarity state
	sf::Color return_state_color();
};