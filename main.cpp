#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
//Libraries

#include "Magnet.h"
#include "Coin.h"
//Classes

int main()
{
    //Screen Setup
    int window_height = 800;
    int window_width = 800;
    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Polarized Profits");

    //Frame Rate
    window.setFramerateLimit(60);

    //Directions For Magnet Movement
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f;

    //Mouse Position
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    //Objects
    std::vector<Coin> coins;
    Magnet magnet(350, 400, 12000);

    //Main Run Loop
    while (window.isOpen())
    {
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

            //Change Polarity
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                magnet.change_state();

            //Spawn Click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                coins.push_back(Coin(mousePosWindow.x, mousePosWindow.y, 1, 1));
        }

        //Change Window Background
        window.clear(magnet.return_state_color());

        //Store Mouse Position
        mousePosWindow = sf::Mouse::getPosition(window);

        //Coin Updates: Iterate Through All Coins
        for (auto& e : coins)
        {
            e.update_physics(magnet);
            e.render(window);
        }

        //Magnet Updates:
        magnet.render(window);
        magnet.changePos(dirRight, dirLeft, dirDown, dirUp);
#
        //Magnet Movement Restrictions:
        if (magnet.get_pos().x <= 0.f)
            dirLeft = 0.f;
        if (magnet.get_pos().x >= window_width) //TO DO - FOR SPRITE LENGHT
            dirRight = 0.f;
        if (magnet.get_pos().y <= 0.f)
            dirUp = 0.f;
        if (magnet.get_pos().y >= window_height)//TO DO - FOR SPRITE LENGHT
            dirDown = 0.f;

        //Draw Screen
        window.display();
    }

    return 0;
}
