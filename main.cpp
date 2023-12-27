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

void MainMenu(sf::RenderWindow& window, int windowHeight, int windowWidth, std::vector<int> toErase, std::vector<Coin>& coins, float& CurrentCoinSpawnR, float& coinSpawnR, TextUI& GameTitle1, TextUI& GameTitle2, TextUI& Author, Button& Start, Button& Exit, int emptyText, sf::Time deltaTime)
{
    window.clear(sf::Color::White);

    CurrentCoinSpawnR += deltaTime.asSeconds();

    //Spawn Coins
    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        coins.push_back(Coin(0, 1.5f, 1.f, windowWidth, windowHeight));
        CurrentCoinSpawnR = 0.f;
    }

    //Coin Updates
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i].fall_physics();
        coins[i].render(window);

        //Erase coin if left the screen
        if (coins[i].pos.y > windowHeight)
        {
            toErase.push_back(i);
        }
    }

    for (int i = toErase.size() - 1; i >= 0; i--)
    {
        coins.erase(coins.begin() + toErase[i]);
    }

    //UI Updates
    //Game Title
    GameTitle1.update("Polarized", true, NULL);
    GameTitle1.render(window, windowWidth / 2 - 450.f, 30.f);

    GameTitle2.update("Profits", true, NULL);
    GameTitle2.render(window, windowWidth / 2 - 60.f, 110.f);

    Author.update("Made by Iancic David", true, NULL);
    Author.render(window, windowWidth - 350.f, windowHeight - 50.f);

    //Buttons
    Start.update("Start");
    Start.render(window, windowWidth / 2 - 125.f, 320.f);

    Exit.update("Exit");
    Exit.render(window, windowWidth / 2 - 125.f, 420.f);
}

void Tutorial(sf::RenderWindow& window, Button& Proceed, sf::Sprite& tutorialsprite)
{
    //Tutorial Background
    window.draw(tutorialsprite);

    //UI Updates
    Proceed.update("Proceed");
    Proceed.render(window, 950.f, 600.f);
}

void Level1(sf::RenderWindow& window, int windowHeight, int windowWidth, std::vector<int> toErase, Background background, Transition transition, TextUI& Balance, TextUI& Timer, Magnet& magnet, Hand& leftHand, Hand& rightHand, std::vector<Coin>& coins, Pig& pig, int& balance, float dirLeft, float dirUp, float dirDown, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, float currentRoundTime, sf::Time deltaTime)
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

        //Spawn Silver Coins (30%)
        else if (probability == 7 || probability == 8 || probability == 9)
        {
            coins.push_back(Coin(2, 1.5f, 1.f, windowWidth, windowHeight));
            CurrentCoinSpawnR = 0.f;
        }

        //Spawn Gold Coins (10%)
        else if (probability == 10)
        {
            coins.push_back(Coin(3, 1.5f, 1.f, windowWidth, windowHeight));
            CurrentCoinSpawnR = 0.f;
        }
    }

    //Coin Updates
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i].update_physics(magnet);
        coins[i].render(window);

        //Collision with Piggy Bank 
        if (coins[i].sprite.getGlobalBounds().intersects(pig.sprite.getGlobalBounds()))
        {
            balance = balance + coins[i].value;
            toErase.push_back(i);
        }

        //Collision with Magnet
        else if (coins[i].sprite.getGlobalBounds().intersects(magnet.magnetsprite.getGlobalBounds()))
        {
            balance = balance - coins[i].value;
            toErase.push_back(i);
        }

        //Collision with Left Hand
        else if (coins[i].sprite.getGlobalBounds().intersects(leftHand.sprite_hand.getGlobalBounds()))
        {
            leftHand.retracting = true;
            balance = balance - 1;

            toErase.push_back(i);
        }

        //Collision with Right Hand
        else if (coins[i].sprite.getGlobalBounds().intersects(rightHand.sprite_hand.getGlobalBounds()))
        {
            rightHand.retracting = true;
            balance = balance - 1;

            toErase.push_back(i);
        }

        //Erase coin if left the screen
        if (coins[i].pos.y > windowHeight + 50.f)
        {
            balance = balance - coins[i].value;
            toErase.push_back(i);
        }
    }

    for (int i = toErase.size() - 1; i >= 0; i--)
    {
        coins.erase(coins.begin() + toErase[i]);
    }

    //Movement Restrictions For Player
    if (magnet.get_pos().x <= 0.f + magnet.magnetsprite.getTexture()->getSize().x / 2 * magnet.scale)
        dirLeft = 0.f;

    if (magnet.get_pos().x >= windowWidth - magnet.magnetsprite.getTexture()->getSize().x / 2 * magnet.scale)
        dirRight = 0.f;

    if (magnet.get_pos().y <= 0.f + magnet.magnetsprite.getTexture()->getSize().y / 2 * magnet.scale)
        dirUp = 0.f;

    if (magnet.get_pos().y >= windowHeight - magnet.magnetsprite.getTexture()->getSize().y / 2 * magnet.scale)
        dirDown = 0.f;

    //Objects Updates
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

    //UI Updates
    Balance.update("euro", false, balance);
    Balance.render(window, windowWidth / 2 - 55.f, windowHeight - 50.f);

    Timer.update("seconds", false, currentRoundTime);
    Timer.render(window, windowWidth / 2 - 125.f, 0.f);
}

void Level2(sf::RenderWindow& window, int windowHeight, int windowWidth, Magnet& wallet, TextUI Score, std::vector<int> toErase, std::vector<Coin>& coins, float dirLeft, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, int& balance, int& finalBalance, int& coinCounter, sf::Time deltaTime)
{
    window.clear(sf::Color::White);

    CurrentCoinSpawnR += deltaTime.asSeconds();

    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        if (coinCounter < balance)
        {
            coins.push_back(Coin(1, 1.5f, 1.f, windowWidth, windowHeight));
            coinCounter = coinCounter + 1;
            CurrentCoinSpawnR = 0.f;
        }
    }

    //Coin Updates
    for (int i = 0; i < coins.size(); i++)
    {
        coins[i].fall_physics();
        coins[i].render(window);

        //Collision with Wallet
        if (coins[i].sprite.getGlobalBounds().intersects(wallet.magnetsprite.getGlobalBounds()))
        {
            finalBalance += 1;
            toErase.push_back(i);
        }

        //Erase coin if left the screen
        if (coins[i].pos.y > windowHeight + 50.f)
        {
            toErase.push_back(i);
        }
    }

    for (int i = toErase.size() - 1; i >= 0; i--)
    {
        coins.erase(coins.begin() + toErase[i]);
    }

    //Movement Restrictions For Player
    if (wallet.get_pos().x <= 0.f + wallet.magnetsprite.getTexture()->getSize().x / 2 * wallet.scale)
        dirLeft = 0.f;

    if (wallet.get_pos().x >= windowWidth - wallet.magnetsprite.getTexture()->getSize().x / 2 * wallet.scale)
        dirRight = 0.f;

    //Objects Updates
    wallet.changeHorizontal(dirRight, dirLeft);
    wallet.render(window);

    //UI Updates
    Score.update("Wallet", false, finalBalance);
    Score.render(window, windowWidth / 2 - 55.f, windowHeight - 100.f);
}

void Outro(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);
}

int main()
{
    int windowHeight = 720;
    int windowWidth = 1280;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Polarized Profits");

    sf::Image icon;
    icon.loadFromFile("Assets/Sprites/Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
     
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);

    sf::Clock clock;
    sf::Time deltaTime;

    //Game Logic
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f; //Directions For Magnet Movement
    std::vector<int> toErase;
   
    //Level 1
    float maxRoundTime = 11.f; //TESTING PURPOSES
    //float maxRoundTime = 91.f; //Level 1 ROUND TIME
    float currentRoundTime = maxRoundTime;
    float polarityPressed = false; //Check for Polarity Input
    int balance = 0; //Coin Balance During Level 1

    //Level 2
    int finalBalance = 0; //Final Score
    int coinCounter = 0; //Final counter after collecting the coins
    int hitpoints = 3; //Hitpoints Level 2

    //Scene Management
    enum scenes{MainMenuScene, TutorialScene, Level1Scene, Level2Scene, OutroScene};
    scenes currentscene = MainMenuScene;

    //Main Menu
    std::vector<Coin> mainMenuCoins;
    float coinSpawnRMenu = 0.4f; //Spawnrate For Coins Main Menu

    TextUI GameTitle1(sf::Color::Red, 130);
    TextUI GameTitle2(sf::Color::Blue, 140);
    TextUI Author(sf::Color::White, 30);

    Button Proceed(200.f, 80.f, sf::Color::Blue, sf::Color::White, 35);
    Button Start(200.f, 80.f, sf::Color::Blue, sf::Color::White, 35);
    Button Exit(200.f, 80.f, sf::Color::Red, sf::Color::White, 35);

    //Tutorial
    sf::Texture* tutorial;
    sf::Sprite tutorialsprite;

    tutorial = new sf::Texture;
    tutorial->loadFromFile("Assets/Sprites/Tutorial.png");
    tutorialsprite.setTexture(*tutorial);

    //Level1 Objects
    std::vector<Coin> coins;

    float coinSpawnR1 = 0.7f; //Spawnrate For Coins Level 1
    float CurrentCoinSpawnR = 0.f;

    Background background(0.f, 0.f);
    TextUI Balance(sf::Color::White, 45);
    TextUI Timer(sf::Color::White, 50);
    Transition transition(0.f, 0.f);

    Magnet magnet(600, 500, 5.f, false);
    Pig pig(600, 300);
    Hand leftHand(false, windowHeight, windowWidth);
    Hand rightHand(true, windowHeight, windowWidth);

    //Level2 Objects
    TextUI Score(sf::Color::Yellow, 65);
    Magnet wallet(600, 550, 6.5f, true);

    std::vector<Coin> pigCoins;
    float coinSpawnR2 = 0.8f; //Spawnrate For Coins Level 2


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
                dirLeft = 1.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                dirRight = 1.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                dirUp = 1.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                dirDown = 1.f;

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
                MainMenu(window, windowHeight, windowWidth, toErase, mainMenuCoins, CurrentCoinSpawnR, coinSpawnRMenu, GameTitle1, GameTitle2, Author, Start, Exit, NULL, deltaTime);
                break;
            case 1:
                Tutorial(window, Proceed, tutorialsprite);
                break;
            case 2:
                Level1(window, windowHeight, windowWidth, toErase, background, transition, Balance, Timer, magnet, leftHand, rightHand, coins, pig, balance, dirLeft, dirUp, dirDown, dirRight, CurrentCoinSpawnR, coinSpawnR1, currentRoundTime, deltaTime);
                break;
            case 3:
                Level2(window, windowHeight, windowWidth, wallet, Score, toErase, pigCoins, dirLeft, dirRight, CurrentCoinSpawnR ,coinSpawnR2, balance, finalBalance, coinCounter, deltaTime);
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