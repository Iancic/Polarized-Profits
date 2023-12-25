#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Magnet.h"
#include "Coin.h"
#include "Pig.h"
#include "Hand.h"
#include "TextUI.h"
#include "Button.h"
#include "Background.h"
#include "Transition.h"

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

void Tutorial(sf::RenderWindow& window, Button& Proceed)
{
    //Tutorial Background
    sf::Texture* tutorial;
    sf::Sprite tutorialsprite;

    tutorial = new sf::Texture;
    tutorial->loadFromFile("Assets/Sprites/Tutorial.png");
    tutorialsprite.setTexture(*tutorial);

    window.draw(tutorialsprite);

    //Button
    Proceed.update("Proceed");
    Proceed.render(window, 950.f, 600.f);
}

void Level1(sf::RenderWindow& window, int windowHeight, int windowWidth, Background background, Transition transition, TextUI& Balance, TextUI& Timer, Magnet& magnet, Hand& leftHand, Hand& rightHand, std::vector<Coin>& coins, Pig& pig, float& balance, float dirLeft, float dirUp, float dirDown, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, float currentRoundTime, sf::Time deltaTime)
{
    background.render(window);

    CurrentCoinSpawnR += deltaTime.asSeconds();

    //Spawn Coins
    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        int probability = 1 + (rand() % 10);

        //Spawn Copper Coins (60%)
        if (probability <= 6)
        {
            coins.push_back(Coin(1, 1.5f, 1.f, windowWidth, windowHeight));
            CurrentCoinSpawnR = 0.f;
        }

        //Spawn Copper Coins (30%)
        else if (probability == 7 || probability == 8 || probability == 9)
        {
            coins.push_back(Coin(2, 1.5f, 1.f, windowWidth, windowHeight));
            CurrentCoinSpawnR = 0.f;
        }

        //Spawn Copper Coins (10%)
        else if (probability == 10)
        {
            coins.push_back(Coin(3, 1.5f, 1.f, windowWidth, windowHeight));
            CurrentCoinSpawnR = 0.f;
        }
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

        //Collision with Left Hand
        else if (coins[i].sprite.getGlobalBounds().intersects(leftHand.sprite_hand.getGlobalBounds()))
        {
            leftHand.retracting = true;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        //Collision with Right Hand
        else if (coins[i].sprite.getGlobalBounds().intersects(rightHand.sprite_hand.getGlobalBounds()))
        {
            rightHand.retracting = true;
            balance = balance - 1;

            coins.erase(coins.begin() + i);
        }

        //Erase coin if left the screen
        if (coins[i].pos.y > windowHeight + 50.f)
        {
            balance = balance - coins[i].value;
            coins.erase(coins.begin() + i);
        }
    }

    //Objects Updates:
    magnet.changePos(dirRight, dirLeft, dirDown, dirUp);
    magnet.render(window);

    pig.changePos(window, deltaTime);
    pig.render(window);

    if (leftHand.retracting == false)
        leftHand.moveHand(coins);
    else
        leftHand.retractHand();
    leftHand.render(window);

    if (rightHand.retracting == false)
        rightHand.moveHand(coins);
    else 
        rightHand.retractHand();
    rightHand.render(window);

    //UI Updates:
    Balance.update("euro", false, balance);
    Balance.render(window, windowWidth / 2 - 55.f, windowHeight - 50.f);
    Timer.update("seconds", false, currentRoundTime);
    Timer.render(window, windowWidth / 2 - 125.f, 0.f);

    //transition.update();
    //transition.render(window);
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

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Polarized Profits");

    //How often does update run
    window.setFramerateLimit(60);

    window.setVerticalSyncEnabled(false);

    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    //Delta Time Clock
    sf::Clock clock;
    sf::Time deltaTime;

    //Game Logic
    float polarityPressed = false; //Check for Polarity Input

    float balance = 0.f; //Balance

    //Scene Management
    enum scenes{MainMenuScene, TutorialScene, Level1Scene, Level2Scene, OutroScene};
    scenes currentscene = MainMenuScene;

    //Main Menu
    TextUI GameTitle1(sf::Color::Red, 75);
    TextUI GameTitle2(sf::Color::Blue, 75);
    TextUI Author(sf::Color::Red, 25);


    Button Proceed(300.f, 100.f, sf::Color::Blue, sf::Color::White, 35);
    Button Start(300.f, 100.f, sf::Color::Blue, sf::Color::White, 35);
    Button Exit(300.f, 100.f, sf::Color::Red, sf::Color::White, 35);

    //Level1
    float maxRoundTime = 61.f; //Level 1 Round Time
    float currentRoundTime = maxRoundTime;

    float coinSpawnR = 0.7f; //Spawnrate For Coins
    float CurrentCoinSpawnR = 0.f;

    //Directions For Magnet Movement
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f;

    Background background(0.f, 0.f);
    TextUI Balance(sf::Color::White, 45);
    TextUI Timer(sf::Color::White, 50);
    Transition transition(0.f, 0.f);

    std::vector<Coin> coins;
    Magnet magnet(600, 500);
    Pig pig(600, 300);
    Hand leftHand(false, windowHeight, windowWidth);
    Hand rightHand(true, windowHeight, windowWidth);

    while (window.isOpen())
    {
        mousePosWindow = sf::Mouse::getPosition(window);

        //Delta Time
        deltaTime = clock.restart();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Change Magnet Polarity
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && polarityPressed == false)
            {
                magnet.change_state();
                background.change_state(magnet.get_state());
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
                if (currentscene == 0)
                {
                    if (Start.buttonBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                        currentscene = TutorialScene;
                    if (Exit.buttonBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                        window.close();
                }
                if (currentscene == 1)
                {
                    if (Proceed.buttonBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                        currentscene = Level1Scene;
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

        //Level 1 Timer
        if (currentscene == 2)
        {
            currentRoundTime -= deltaTime.asSeconds();
            if (currentRoundTime <= 0.f)
                currentscene = Level2Scene;
        }

        //Scene Manager 
        switch (currentscene) {
            case 0:
                MainMenu(window, GameTitle1, GameTitle2, Author, Start, Exit, NULL);
                break;
            case 1:
                Tutorial(window, Proceed);
                break;
            case 2:
                Level1(window, windowHeight, windowWidth, background, transition, Balance, Timer, magnet, leftHand, rightHand, coins, pig, balance, dirLeft, dirUp, dirDown, dirRight, CurrentCoinSpawnR, coinSpawnR, currentRoundTime, deltaTime);
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