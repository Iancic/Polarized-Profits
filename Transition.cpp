# include "Transition.h"

Transition::Transition(float posX, float posY)
{
	pos.x = posX;
	pos.y = posY;

	size = 100.f;

	initSprite();
}

void Transition::initSprite()
{
	box.setSize(sf::Vector2f(size, size));
	box.setPosition(pos);
	box.setFillColor(sf::Color::Black);
}

void Transition::update()
{
	sf::Vector2f currentSize = box.getSize();
	currentSize += sf::Vector2f(10.f, 10.f);
	box.setSize(currentSize);
}

void Transition::render(sf::RenderWindow& window)
{
	window.draw(box);
}
