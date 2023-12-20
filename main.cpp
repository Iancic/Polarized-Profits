#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Magnet.h"
#include "Coin.h"
#include "Pig.h"
#include "Hand.h"
#include "TextUI.h"
#include "Button.h"

void MainMenu(sf::RenderWindow& window, TextUI& GameTitle1, TextUI& GameTitle2, TextUI& Author, Button& Start, Button& Exit, int emptyText)
{
    window.clear(sf::Color::White);

    //Text Updates:
    //Game Title
    GameTitle1.update("Polarized", true, NULL);
    GameTitle1.render(window, 100.f, 50.f);
    GameTitle2.update("Profits", true, NULL);
    GameTitle2.render(window, 160.f, 130.f);

    //Author
    Author.update("Made by Iancic David", true, NULL);
    Author.render(window, 460.f, 750.f);

    //Buttons
    Start.update("Start");
    Start.render(window, 200.f, 280.f);
    Exit.update("Exit");
    Exit.render(window, 200.f, 420.f);
}

void Level1(sf::RenderWindow& window, int gameState, TextUI& Balance, TextUI& Timer, Magnet& magnet, Hand& leftHand, Hand& rightHand, std::vector<Coin>& coins, Pig& pig, float& balance, float dirLeft, float dirUp, float dirDown, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, float currentRoundTime, sf::Time deltaTime)
{
    window.clear(magnet.return_state_color());

    //Coin SpawnRate
    CurrentCoinSpawnR += deltaTime.asSeconds();

    //Spawn Coins
    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        coins.push_back(Coin(0.8f, 0.8f, 3.f));
        CurrentCoinSpawnR = 0.f;
    }

    //Coin Updates: Iterate Through All Coins
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i].update_physics(magnet);
        coins[i].render(window);

        //Collision with Piggy Bank. 
        if (coins[i].sprite.getGlobalBounds().intersects(pig.sprite.getGlobalBounds()))
        {
            balance = balance + coins[i].value;
            coins.erase(coins.begin() + i);
        }

        //Collision with Magnet. 
        else if (coins[i].sprite.getGlobalBounds().intersects(magnet.magnetsprite.getGlobalBounds()))
        {
            balance = balance - 2 * coins[i].value;
            coins.erase(coins.begin() + i);
        }

        //Collision with Hand. 
        else if (coins[i].sprite.getGlobalBounds().intersects(leftHand.sprite_hand.getGlobalBounds()))
        {
            //Pushes the hand back after getting the coin
            leftHand.pos.x = -150.f;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        else if (coins[i].sprite.getGlobalBounds().intersects(rightHand.sprite_hand.getGlobalBounds()))
        {
            //Pushes the hand back after getting the coin
            rightHand.pos.x = 950.f;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        //Erase coin if not on screen
        if (coins[i].pos.y > 900.f)
            coins.erase(coins.begin() + i);
    }

    //Objects Updates:
    magnet.changePos(dirRight, dirLeft, dirDown, dirUp);
    magnet.render(window);

    pig.changePos(window, deltaTime);
    pig.render(window);

    leftHand.moveHand(coins);
    leftHand.render(window);

    rightHand.moveHand(coins);
    rightHand.render(window);

    //UI Updates:
    Balance.update("euro", false, balance);
    Balance.render(window, 340.f, 700.f);
    Timer.update("seconds", false, currentRoundTime);
    Timer.render(window, 340.f, 750.f);
}

void Level2()
{

}

void Outro()
{

}

int main()
{
    //Window Settings
    int window_height = 800;
    int window_width = 800;

    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Polarized Profits");

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    //Delta Time Clock
    sf::Clock clock;
    sf::Time deltaTime;

    float maxRoundTime = 61.f; //Level 1 Round Time
    float currentRoundTime = maxRoundTime;

    float coinSpawnR = 1.f; //Spawnrate For Coins
    float CurrentCoinSpawnR = 0.f;

    //Game Logic
    float polarityPressed = false; //Check for Polarity Input

    float balance = 0.f; //Balance
    int gameState = 1; // 1 (Main Menu), 2 (Level 1), 3 (Level 2), 4 (Outro)

    //Directions For Magnet Movement
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f;

    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    //Objects
    //Main Menu
    TextUI GameTitle1(sf::Color::Red, 75);
    TextUI GameTitle2(sf::Color::Blue, 75);
    TextUI Author(sf::Color::Black, 25);

    Button Start(300.f, 100.f, sf::Color::Blue, sf::Color::Black, 35);
    Button Exit(300.f, 100.f, sf::Color::Red, sf::Color::Black, 35);

    //Level1
    TextUI Balance(sf::Color::Yellow, 35);
    TextUI Timer(sf::Color::Yellow, 20);

    std::vector<Coin> coins;
    Magnet magnet(400, 600, 5000);
    Pig pig(400, 400);
    Hand leftHand(false);
    Hand rightHand(true);

    while (window.isOpen())
    {
        mousePosWindow = sf::Mouse::getPosition(window);

        //Level 1 Timer
        if (gameState == 2)
        {
        currentRoundTime -= deltaTime.asSeconds();
        if (currentRoundTime <= 0)
            gameState++;
        }

        //Delta Time
        deltaTime = clock.restart();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Change Magnet Polarity
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && polarityPressed == false && gameState == 2)
            {
                magnet.change_state();
                polarityPressed = true;
            }

            //Magnet Movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                dirLeft = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                dirRight = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                dirUp = magnet.get_speed();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                dirDown = magnet.get_speed();

            //Magnet Movement, Button Released, reset Values
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                    polarityPressed = false;

                if (event.key.code == sf::Keyboard::W)
                    dirUp = 0.f;

                else if (event.key.code == sf::Keyboard::S)
                    dirDown = 0.f;

                else if (event.key.code == sf::Keyboard::A)
                    dirLeft = 0.f;

                else if (event.key.code == sf::Keyboard::D)
                    dirRight = 0.f;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //UI Buttons Functionality
                if (gameState == 1)
                {
                    if (Start.buttonBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                        gameState ++;
                    if (Exit.buttonBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                        window.close();
                }
            }
        }

        //Movement Restrictions
        if (magnet.get_pos().x <= 0.f)
            dirLeft = 0.f;

        if (magnet.get_pos().x >= window_width)
            dirRight = 0.f;

        if (magnet.get_pos().y <= 0.f)
            dirUp = 0.f;

        if (magnet.get_pos().y >= window_height)
            dirDown = 0.f;

        //Scene Manager 
        switch (gameState) {
            case 1:
                MainMenu(window, GameTitle1, GameTitle2, Author, Start, Exit, NULL);
                break;
            case 2:
                Level1(window, gameState, Balance, Timer, magnet, leftHand, rightHand, coins, pig, balance, dirLeft, dirUp, dirDown, dirRight, CurrentCoinSpawnR, coinSpawnR, currentRoundTime, deltaTime);
                break;
            case 3:
                Level2();
                break;
            case 4:
                Outro();
                break;
            default:
                break;
        }
         
        window.display();
    }

    return 0;
}
