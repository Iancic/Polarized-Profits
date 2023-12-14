#pragma once
#include <iostream>
//use for input and output in the debug console
#include <vector>
//used for vector lists
#include <ctime>
//random seeds

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//include SFML library

class CoreScene
{

public:
	//Init -> Input -> Update -> Draw
	void Init();
	void HandleInput(sf::RenderWindow& window, sf::Event event);
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
};
