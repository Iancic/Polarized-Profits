# include "Transition.h"

Transition::Transition(int windowHeight, int windowWidth)
{
	pos.x = 0.f;
	pos.y = 0.f;

	sizeX = windowWidth;
	sizeY = windowHeight;

	initSprite();
}

void Transition::initSprite()
{
	box.setSize(sf::Vector2f(sizeX, sizeY));
	box.setPosition(pos);
	box.setFillColor(sf::Color(0, 0, 0, 255));
}

void Transition::fadeIn(sf::Time deltaTime)
{
	if (isFadeOut == false)
	{
		if (alpha <= 240.f)
			alpha -= fadeSpeedFinal * deltaTime.asSeconds();
		else if (alpha > 240.f)
			alpha -= fadeSpeedStart * deltaTime.asSeconds();
		if (alpha <= 0.f)
		{
			alpha = 0.f;
		}
	}
}

void Transition::fadeOut(sf::Time deltaTime)
{
	if (isFadeOut == true)
	{
		alpha += fadeSpeedFinal * deltaTime.asSeconds();
		if (alpha >= 255.f)
		{
			if (currentscene == 0)
			{
				currentscene = TutorialScene;
			}
			else if (currentscene == 1)
			{
				currentscene = Level1Scene;
			}
			else if (currentscene == 2)
			{
				currentscene = Level2Scene;
			}

			isFadeOut = false;
			alpha = 255.f;
		}
	}
}

void Transition::render(sf::RenderWindow& window)
{
	box.setFillColor(sf::Color(0, 0, 0, alpha));
	window.draw(box);
}
