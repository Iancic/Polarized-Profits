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
    Author.render(window, 210.f, 220.f);

    //Buttons
    Start.update("Start");
    Start.render(window, 200.f, 280.f);
    Exit.update("Exit");
    Exit.render(window, 200.f, 420.f);
}

void Level1(sf::RenderWindow& window, int windowHeight, int windowWidth, int gameState, TextUI& Balance, TextUI& Timer, Magnet& magnet, Hand& leftHand, Hand& rightHand, std::vector<Coin>& coins, Pig& pig, float& balance, float dirLeft, float dirUp, float dirDown, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, float currentRoundTime, sf::Time deltaTime)
{
    window.clear(magnet.return_state_color());

    //Coin SpawnRate
    CurrentCoinSpawnR += deltaTime.asSeconds();

    //Spawn Coins
    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        coins.push_back(Coin(1.5f, 1.5f, 1.f, windowWidth, windowHeight));
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
            balance = balance - coins[i].value;
            coins.erase(coins.begin() + i);
        }

        //Collision with Hand. 
        else if (coins[i].sprite.getGlobalBounds().intersects(leftHand.sprite_hand.getGlobalBounds()))
        {
            //Pushes the hand back after getting the coin
            leftHand.pos.x = -100.f;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        else if (coins[i].sprite.getGlobalBounds().intersects(rightHand.sprite_hand.getGlobalBounds()))
        {
            //Pushes the hand back after getting the coin
            rightHand.pos.x = windowWidth + 100.f;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        //Erase coin if not on screen
        if (coins[i].pos.y > windowHeight + 50.f)
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
    Balance.render(window, windowWidth / 2 - 55.f, windowHeight - 50.f);
    Timer.update("seconds", false, currentRoundTime);
    Timer.render(window, windowWidth / 2 - 125.f, 0.f);
}

void Level2(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
}

void Outro(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
}

int main()
{
    //Window Settings
    int windowHeight = 720;
    int windowWidth = 1280;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Polarized Profits", sf::Style::Close);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    //Delta Time Clock
    sf::Clock clock;
    sf::Time deltaTime;

    //Game Logic
    float polarityPressed = false; //Check for Polarity Input

    float balance = 0.f; //Balance
    int gameState = 1; // 1 (Main Menu), 2 (Level 1), 3 (Level 2), 4 (Outro)

    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    //Main Menu
    TextUI GameTitle1(sf::Color::Red, 75);
    TextUI GameTitle2(sf::Color::Blue, 75);
    TextUI Author(sf::Color::Black, 25);

    Button Start(300.f, 100.f, sf::Color::Blue, sf::Color::Black, 35);
    Button Exit(300.f, 100.f, sf::Color::Red, sf::Color::Black, 35);

    //Level1
    float maxRoundTime = 61.f; //Level 1 Round Time
    float currentRoundTime = maxRoundTime;

    float coinSpawnR = 0.7f; //Spawnrate For Coins
    float CurrentCoinSpawnR = 0.f;

    //Directions For Magnet Movement
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f;

    TextUI Balance(sf::Color::Yellow, 30);
    TextUI Timer(sf::Color::Yellow, 45);

    std::vector<Coin> coins;
    Magnet magnet(600, 500);
    Pig pig(600, 300);
    Hand leftHand(false, windowHeight, windowWidth);
    Hand rightHand(true, windowHeight, windowWidth);

    while (window.isOpen())
    {
        mousePosWindow = sf::Mouse::getPosition(window);

        //Level 1 Timer
        if (gameState == 2)
        {
        currentRoundTime -= deltaTime.asSeconds();
        if (currentRoundTime <= 0.f)
            gameState = 3;
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

            //Magnet Movement, Button Released, Reset Values
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

        //Movement Restrictions For Player
        if (magnet.get_pos().x <= 0.f)
            dirLeft = 0.f;

        if (magnet.get_pos().x >= windowWidth)
            dirRight = 0.f;

        if (magnet.get_pos().y <= 0.f)
            dirUp = 0.f;

        if (magnet.get_pos().y >= windowHeight)
            dirDown = 0.f;

        //Scene Manager 
        switch (gameState) {
            case 1:
                MainMenu(window, GameTitle1, GameTitle2, Author, Start, Exit, NULL);
                break;
            case 2:
                Level1(window, windowHeight, windowWidth, gameState, Balance, Timer, magnet, leftHand, rightHand, coins, pig, balance, dirLeft, dirUp, dirDown, dirRight, CurrentCoinSpawnR, coinSpawnR, currentRoundTime, deltaTime);
                break;
            case 3:
                Level2(window);
                break;
            case 4:
                Outro(window);
                break;
            default:
                break;
        }
         
        window.display();
    }

    return 0;
}
