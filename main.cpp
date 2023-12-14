#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
//Libraries

#include "Magnet.h"
#include "Coin.h"
#include "Pig.h"
#include "Hand.h"
#include "TextUI.h"
#include "CoreScene.h"
//Classes

int main()
{
    //Screen Setup
    int window_height = 800;
    int window_width = 800;
    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Polarized Profits");

    //Delta Time Clock
    sf::Clock clock;
    float maxRoundTime = 90.f;
    float currentRoundTime = maxRoundTime;
    float coinSpawnR = 2.f;
    float CurrentCoinSpawnR = 0.f;

    //Frame Rate
    window.setFramerateLimit(60);

    //Game Logic
    float balance = 0.f;

    //Directions For Magnet Movement
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f;

    //Scenes
    CoreScene corescene;

    //Mouse Position
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    //Objects
    std::vector<Coin> coins;
    Magnet magnet(350, 400, 6000);
    Pig pig(500, 500);

    TextUI Balance(sf::Color::Yellow, 35);
    TextUI Timer(sf::Color::Yellow, 25);

    Hand righthand(true);

    //Main Run Loop
    while (window.isOpen())
    {
        //Delta Time
        sf::Time deltaTime = clock.restart();

        //Window Timer. -1 Second 
        currentRoundTime -= deltaTime.asSeconds();

        sf::Event event;

        //Event Poll
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Magnet Movement With WASD, Button Pressed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && magnet.get_pos().x > 0.f)
                dirLeft = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && magnet.get_pos().x < window_width)
                dirRight = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && magnet.get_pos().y > 0.f)
                dirUp = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && magnet.get_pos().y < window_height)
                dirDown = magnet.get_speed();

            //Magnet Movement With WASD, Button Released, reset Values
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                    dirUp = 0.f;

                else if (event.key.code == sf::Keyboard::S)
                    dirDown = 0.f;

                else if (event.key.code == sf::Keyboard::A)
                    dirLeft = 0.f;

                else if (event.key.code == sf::Keyboard::D)
                    dirRight = 0.f;
            }

            //Magnet Movement Restrictions:
            if (magnet.get_pos().x <= 0.f)
                dirLeft = 0.f;
            if (magnet.get_pos().x >= window_width)//TO DO - FOR SPRITE LENGHT
                dirRight = 0.f;
            if (magnet.get_pos().y <= 0.f)
                dirUp = 0.f;
            if (magnet.get_pos().y >= window_height)//TO DO - FOR SPRITE LENGHT
                dirDown = 0.f;

            //Change Polarity
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                magnet.change_state();

            //Spawn Click //ONLY FOR DEBBUGING WATCH OUT AT BUILD
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                coins.push_back(Coin(1, 1, 1.f));
        }

        //Change Window Background
        window.clear(magnet.return_state_color());

        //Store Mouse Position
        mousePosWindow = sf::Mouse::getPosition(window);

        //Spawn Coins
        if (CurrentCoinSpawnR >= coinSpawnR)
        {
            coins.push_back(Coin(1, 1, 1.f));
            CurrentCoinSpawnR = 0.f;
        }
        else
            CurrentCoinSpawnR += deltaTime.asSeconds();

        //Coin Updates: Iterate Through All Coins
        for (int i = 0; i < coins.size(); i++)
        {
            coins[i].update_physics(magnet);
            coins[i].render(window);

            //Collision with Piggy Bank. 
            if (coins[i].sprite.getGlobalBounds().intersects(pig.sprite.getGlobalBounds()))
            {
                balance = balance + coins[i].value;

                //ERASE THE ITEM LAST TO AVOID ERRORS
                coins.erase(coins.begin() + i);
            }

            //Collision with Magnet. 
            else if (coins[i].sprite.getGlobalBounds().intersects(magnet.magnetsprite.getGlobalBounds()))
            {
                balance = balance - coins[i].value;

                //ERASE THE ITEM LAST TO AVOID ERRORS
                coins.erase(coins.begin() + i);
            }
        }

        //Magnet Updates:
        magnet.changePos(dirRight, dirLeft, dirDown, dirUp);
        magnet.render(window);

        //Pig Updates:
        pig.changePos(window, deltaTime);
        pig.render(window);

        //Text Updates:
        Balance.update("euro", false, balance);
        Balance.render(window, 340.f, 700.f);
        Balance.update("seconds", false, currentRoundTime);
        Balance.render(window, 320.f, 750.f);

        //Draw Screen
        window.display();
    }

    return 0;
}
