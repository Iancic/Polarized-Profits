#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Hand
{

public:

	sf::Vector2f pos;
	bool hand_type; //if true type is right, if false type is left

	sf::Texture* handtexture;
	sf::Sprite sprite_hand;
	sf::Texture* handtexture_failure;
	sf::Sprite sprite_failure;
	sf::Texture* handtexture_succes;
	sf::Sprite sprite_succes;

	//Constructor
	Hand(bool type); //if true type is right, if false type is left

	//Initial Texture Settings
	void initTexture();

	//Initial Sprite Settings
	void initSprite();

	//Render Hand
	void render(sf::RenderWindow& window);
};