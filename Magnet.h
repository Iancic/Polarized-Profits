#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Magnet
{

public:
	sf::Vector2f pos;
	float movespeed = 6.f;
	float strenght;

	//True Means + Polarity & False Mean - Polarity
	bool state = true; 

	sf::Texture* magnettexture;
	sf::Sprite magnetsprite;

	//Constructor
	Magnet(float pos_x, float pos_y, float strenght)
	{
		initTexture();
		initSprite();

		pos.x = pos_x;
		pos.y = pos_y;

		this->strenght = strenght;
	}

	//Initial Texture Settings
	void initTexture()
	{
		magnettexture = new sf::Texture;
		magnettexture->loadFromFile("Assets/Sprites/Magnet.png");
	}

	//Initial Sprite Settings
	void initSprite()
	{
		magnetsprite.setTexture(*magnettexture);
		magnetsprite.setScale(0.5f, 0.5f);
		magnetsprite.setOrigin(magnetsprite.getTexture()->getSize().x / 2, magnetsprite.getTexture()->getSize().y * 0.5f / 2);
	}

	//Render Magnet
	void render(sf::RenderWindow& window)
	{
		magnetsprite.setPosition(pos);
		window.draw(magnetsprite);
	}

	//Function That Gets Called Every Frame And Moves The Magnet On All Axis
	void changePos(float dirRight, float dirLeft, float dirDown, float dirUp)
	{
		pos.x += dirRight;
		pos.x -= dirLeft;
		pos.y += dirDown;
		pos.y -= dirUp;
	}

	//Return Vector2 That Stores Position X & Y
	sf::Vector2f get_pos()
	{
		return pos;
	}

	//Return Float That Stores Strenght
	float get_strenght()
	{
		return strenght;
	}

	//Return Float That Stores Speed
	float get_speed()
	{
		return movespeed;
	}

	//Change state of polarity
	void change_state()
	{
		if (state == true)
			state = false;
		else if (state == false)
			state = true;
	}

	//Get state of polarity
	bool get_state()
	{
		return state;
	}

	//Return background color in regards to polarity state
	sf::Color return_state_color()
	{
		if (state == true)
			return sf::Color(232, 42, 42);
		else if (state == false)
			return sf::Color(59, 204, 212);
	}
};