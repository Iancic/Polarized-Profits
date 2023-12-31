#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Magnet.h"
#include "Coin.h"
#include "Pig.h"
#include "Hand.h"
#include "TextUI.h"
#include "Button.h"
#include "Background.h"
#include "Transition.h"

void MainMenu(sf::RenderWindow& window, int windowHeight, int windowWidth, std::vector<int> toErase, std::vector<Coin>& coins, float& CurrentCoinSpawnR, float& coinSpawnR, TextUI& GameTitle1, TextUI& GameTitle2, TextUI& Author, TextUI& Breda, Button& Start, Button& Exit, int emptyText, Transition& transition, sf::Vector2i mousePosWindow, sf::Sound& Soundtrack, bool& startSong, sf::Time deltaTime)
{
    if (startSong == false)
    {
        startSong = true;
        Soundtrack.play();
    }

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
    Author.render(window, windowWidth - 360.f, windowHeight - 70.f);

    Breda.update("BUAS CMGT PR Intake 2023", true, NULL);
    Breda.render(window, windowWidth - 360.f, windowHeight - 50.f);

    //Buttons
    Start.update(window, mousePosWindow, "Start");
    Start.render(window, windowWidth / 2, 320.f);

    Exit.update(window, mousePosWindow, "Exit");
    Exit.render(window, windowWidth / 2, 420.f);

    //Transition
    transition.fadeIn(deltaTime);
    transition.render(window);
}

void Tutorial(sf::RenderWindow& window, int windowHeight, int windowWidth, Button& Proceed, sf::Sprite& tutorialsprite, Transition& transition, sf::Vector2i mousePosWindow, sf::Time deltaTime)
{
    //Tutorial Background
    window.draw(tutorialsprite);

    //UI Updates
    Proceed.update(window, mousePosWindow, "Proceed");
    Proceed.render(window, windowWidth / 2, 320.f);

    //Transition
    transition.fadeIn(deltaTime);
    transition.render(window);
}

void Level1(sf::RenderWindow& window, int windowHeight, int windowWidth, std::vector<int> toErase, Background background, Transition& transition, TextUI& Balance, TextUI& Timer, Magnet& magnet, Hand& leftHand, Hand& rightHand, std::vector<Coin>& coins, Pig& pig, int& balance, float dirLeft, float dirUp, float dirDown, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, float currentRoundTime, sf::Time deltaTime, bool& reload, sf::Sound& CoinInHandSound, sf::Sound& CoinCollectSound)
{
    background.render(window);

    CurrentCoinSpawnR += deltaTime.asSeconds();

    //Reset Game After Restart Button
    if (reload == true)
    {
        for (int i = 0; i < coins.size(); i++)
        {
            toErase.push_back(i);
        }

        //Reset Game Logic
        balance = 0.f;

        //Reset Entities Positions
        rightHand.retracting = true;
        leftHand.retracting = true;
        magnet.placePos(600.f, 500.f);
        pig.placePos(600.f, 300.f);

        reload = false;
    }

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

    if (!coins.empty())
    {
        //Coin Updates
        for (int i = 0; i < coins.size(); i++)
        {
            coins[i].update_physics(magnet);
            coins[i].render(window);

            //Collision with Piggy Bank 
            if (coins[i].sprite.getGlobalBounds().intersects(pig.sprite.getGlobalBounds()))
            {
                CoinCollectSound.play();
                balance = balance + coins[i].value;
                toErase.push_back(i);
            }

            //Collision with Magnet
            else if (coins[i].sprite.getGlobalBounds().intersects(magnet.magnetsprite.getGlobalBounds()))
            {
                CoinInHandSound.play();
                balance = balance - 1;
                toErase.push_back(i);
            }

            //Collision with Left Hand
            else if (coins[i].sprite.getGlobalBounds().intersects(leftHand.sprite_hand.getGlobalBounds()) && leftHand.retracting == false)
            {
                CoinInHandSound.play();
                leftHand.retracting = true;
                balance = balance - coins[i].value;
                toErase.push_back(i);
            }

            //Collision with Right Hand
            else if (coins[i].sprite.getGlobalBounds().intersects(rightHand.sprite_hand.getGlobalBounds()) && rightHand.retracting == false)
            {
                CoinInHandSound.play();
                rightHand.retracting = true;
                balance = balance - coins[i].value;
                toErase.push_back(i);
            }

            //Erase coin if left the screen
            if (coins[i].pos.y > windowHeight + 50.f)
            {
                balance = balance - coins[i].value;
                toErase.push_back(i);
            }
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
    leftHand.magnetPhysics(magnet);
    leftHand.render(window);

    if (rightHand.retracting == false)
        rightHand.moveHand(coins);
    else 
        rightHand.retractHand();
    rightHand.magnetPhysics(magnet);
    rightHand.render(window);

    //UI Updates
    Balance.update("euro", false, balance);
    Balance.render(window, windowWidth / 2 - 55.f, windowHeight - 50.f);

    Timer.update("seconds", false, currentRoundTime);
    Timer.render(window, windowWidth / 2 - 125.f, 0.f);

    //Transition
    transition.fadeIn(deltaTime);
    transition.render(window);
}

void Level2(sf::RenderWindow& window, int windowHeight, int windowWidth, Magnet& wallet, sf::Sprite& background, TextUI Score, TextUI& Balance, std::vector<int> toErase, std::vector<Coin>& coins, float dirLeft, float dirRight, float& CurrentCoinSpawnR, float& coinSpawnR, int& balance, int& finalBalance, int& coinCounter, Transition& transition, bool hasStartedFall, bool& gameFinished, sf::Time deltaTime, sf::Sound& CoinInHandSound, sf::Sound& CoinCollectSound)
{
    window.draw(background);

    CurrentCoinSpawnR += deltaTime.asSeconds();

    if (CurrentCoinSpawnR >= coinSpawnR)
    {
        if (coinCounter < balance)
        {
            coins.push_back(Coin(1, 2.2f, 1.f, windowWidth, windowHeight));
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
            CoinCollectSound.play();
            finalBalance += 1;
            toErase.push_back(i);
        }

        //Erase coin if left the screen
        if (coins[i].pos.y > windowHeight + 120.f)
        {
            toErase.push_back(i);
        }
    }

    for (int i = toErase.size() - 1; i >= 0; i--)
    {
        coins.erase(coins.begin() + toErase[i]);
        hasStartedFall = true;
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
    Score.update("Out Of:", false, finalBalance);
    Score.render(window, windowWidth / 2 - 100.f, windowHeight - 120.f);

    Balance.update("Euro", false, balance);
    Balance.render(window, windowWidth / 2 - 100.f, windowHeight - 50.f);

    if (coins.size() == 0.f && hasStartedFall == true) //Check for avoiding running fade out at start.
    {
        gameFinished = true;
    }

    //Transition
    transition.fadeIn(deltaTime);
    transition.render(window);
}

void Outro(sf::RenderWindow& window, int windowHeight, int windowWidth, int finalBalance, TextUI& GameOver, TextUI& FinalScore, Button& Restart, Button& Exit, Transition& transition, sf::Vector2i mousePosWindow, sf::Time deltaTime)
{
    window.clear(sf::Color::White);

    GameOver.update("Game Over", true, NULL);
    GameOver.render(window, windowWidth / 2 - 450.f, 30.f);

    FinalScore.update("Coins Collected", false, finalBalance);
    FinalScore.render(window, windowWidth / 2 - 60.f, 110.f);

    //Buttons
    Restart.update(window, mousePosWindow, "Restart");
    Restart.render(window, windowWidth / 2, 320.f);

    Exit.update(window, mousePosWindow, "Exit");
    Exit.render(window, windowWidth / 2, 420.f);

    //Transition
    transition.fadeIn(deltaTime);
    transition.render(window);
}

int main()
{
    //Window & General Game Settings
    int windowHeight = 720;
    int windowWidth = 1280;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Polarized Profits");

    sf::Image icon;
    icon.loadFromFile("Assets/Sprites/UI/Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
     
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Clock clock;
    sf::Time deltaTime;

    //SFX
    sf::SoundBuffer MenuSoundtrack;
    MenuSoundtrack.loadFromFile("Assets/SFX/Soundtracks/MenuSoundtrack.wav");
    sf::Sound MenuSoundtrackSound;
    MenuSoundtrackSound.setBuffer(MenuSoundtrack);

    sf::SoundBuffer ButtonPress;
    ButtonPress.loadFromFile("Assets/SFX/Sounds/ButtonPress.wav");
    sf::Sound ButtonPressSound;
    ButtonPressSound.setBuffer(ButtonPress);

    sf::SoundBuffer CoinCollect;
    CoinCollect.loadFromFile("Assets/SFX/Sounds/CoinCollect.wav");
    sf::Sound CoinCollectSound;
    CoinCollectSound.setBuffer(CoinCollect);

    sf::SoundBuffer CoinInHand;
    CoinInHand.loadFromFile("Assets/SFX/Sounds/CoinInHand.wav");
    sf::Sound CoinInHandSound;
    CoinInHandSound.setBuffer(CoinInHand);

    //Game Logic
    float dirLeft = 0.f, dirRight = 0.f, dirUp = 0.f, dirDown = 0.f; //Directions For Magnet Movement
    bool gameFinished = false;
    std::vector<int> toErase;
    bool startSong = false;
   
    //Level 1
    float maxRoundTime = 61.f;
    float currentRoundTime = maxRoundTime;
    float polarityPressed = false;
    int balance = 0;
    bool reload = false;

    //Level 2
    int finalBalance = 0;
    int coinCounter = 0;
    bool hasStartedFall = false; //Check for Fade Out Level 2

    //Main Menu
    std::vector<Coin> mainMenuCoins;
    float coinSpawnRMenu = 0.15f; //Spawnrate For Coins Main Menu

    TextUI GameTitle1(sf::Color(199, 52, 52, 255), 130);
    TextUI GameTitle2(sf::Color(61, 62, 210, 255), 140);
    TextUI Author(sf::Color::White, 22);
    TextUI Breda(sf::Color::White, 22);

    Button Start(0.26f, 0.21f, sf::Color::Blue, sf::Color::White, 35);
    Button Exit(0.26f, 0.21f, sf::Color::Red, sf::Color::White, 35);

    //Tutorial
    sf::Texture* tutorial;
    sf::Sprite tutorialsprite;

    tutorial = new sf::Texture;
    tutorial->loadFromFile("Assets/Sprites/Backgrounds/Tutorial.png");
    tutorialsprite.setTexture(*tutorial);

    Button Proceed(0.26f, 0.21f, sf::Color::Blue, sf::Color::White, 35);

    //Level1
    std::vector<Coin> coins;

    float coinSpawnR1 = 0.6f; //Spawnrate For Coins
    float CurrentCoinSpawnR = 0.f;

    Background background(0.f, 0.f);
    TextUI Balance(sf::Color::White, 45);
    TextUI Timer(sf::Color::White, 50);
    Transition transition(windowHeight, windowWidth);

    Magnet magnet(600, 500, 5.f, false);
    Pig pig(600, 300);
    Hand leftHand(false, windowHeight, windowWidth);
    Hand rightHand(true, windowHeight, windowWidth);

    //Level2
    sf::Texture* Level2Background;
    sf::Sprite Level2BackgroundSprite;

    Level2Background = new sf::Texture;
    Level2Background->loadFromFile("Assets/Sprites/Backgrounds/Level2Background.png");
    Level2BackgroundSprite.setTexture(*Level2Background);

    TextUI Score(sf::Color::Yellow, 65);
    Magnet wallet(600, 550, 8.f, true);

    std::vector<Coin> pigCoins;
    float coinSpawnR2 = 0.8f; //Spawnrate For Coins

    //Outro
    TextUI GameOver(sf::Color(199, 52, 52, 255), 80);
    TextUI FinalScore(sf::Color(61, 62, 210, 255), 80);
    Button Restart(0.26f, 0.21f, sf::Color::Blue, sf::Color::White, 35);


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
                //Main Menu Buttons
                if (transition.currentscene == 0)
                {
                    if (Start.buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                    {
                        ButtonPressSound.play();
                        transition.isFadeOut = true;
                    }

                    if (Exit.buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                    {
                        ButtonPressSound.play();
                        window.close();
                    }
                }

                //Tutorial Screen Buttons
                else if (transition.currentscene == 1)
                {
                    if (Proceed.buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                    {
                        ButtonPressSound.play();
                        transition.isFadeOut = true;
                    }
                }

                //End Screen Buttons
                else if (transition.currentscene == 4)
                {
                    if (Restart.buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                    {
                        gameFinished = false;
                        reload = true;
                        currentRoundTime = 61.f;
                        ButtonPressSound.play();
                        transition.isFadeOut = true;
                    }

                    if (Exit.buttonSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePosWindow)))
                    {
                        ButtonPressSound.play();
                        window.close();
                    }
                }
            }
        } 

        //Level 1 Timer
        if (transition.currentscene == 2)
        {
            currentRoundTime -= deltaTime.asSeconds();
            if (currentRoundTime <= 0.f)
            {
                if (balance > 0.f) //Go To Level 2
                    transition.isFadeOut = true;

                else //Lose Scenario On Level 1
                    gameFinished = true;
            }
        }

        //Finish Game Conditions
        if (gameFinished == true && transition.currentscene != 4)
        {
            if (transition.currentscene == 2)
                transition.isFadeOut = true; //From Level 1 To Outro

            else if (transition.currentscene == 3)
                transition.isFadeOut = true; //From Level 2 To Outro
        }

        //Scene Manager 
        transition.fadeOut(deltaTime);

        switch (transition.currentscene) {
            case 0:
                MainMenu(window, windowHeight, windowWidth, toErase, mainMenuCoins, CurrentCoinSpawnR, coinSpawnRMenu, GameTitle1, GameTitle2, Author, Breda, Start, Exit, NULL, transition, mousePosWindow, MenuSoundtrackSound, startSong, deltaTime);
                break;
            case 1:
                Tutorial(window, windowHeight, windowWidth, Proceed, tutorialsprite, transition, mousePosWindow, deltaTime);
                break;
            case 2:
                Level1(window, windowHeight, windowWidth, toErase, background, transition, Balance, Timer, magnet, leftHand, rightHand, coins, pig, balance, dirLeft, dirUp, dirDown, dirRight, CurrentCoinSpawnR, coinSpawnR1, currentRoundTime, deltaTime, reload, CoinInHandSound, CoinCollectSound);
                break;
            case 3:
                Level2(window, windowHeight, windowWidth, wallet, Level2BackgroundSprite, Score, Balance, toErase, pigCoins, dirLeft, dirRight, CurrentCoinSpawnR ,coinSpawnR2, balance, finalBalance, coinCounter, transition, hasStartedFall, gameFinished, deltaTime, CoinInHandSound, CoinCollectSound);
                break;
            case 4:
                Outro(window, windowHeight, windowWidth, finalBalance, GameOver, FinalScore, Restart, Exit, transition, mousePosWindow, deltaTime);
                break;
            default:
                break;
        }
         
        window.display();
    }

    return 0;
}