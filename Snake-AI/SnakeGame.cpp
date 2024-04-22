#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"
#include "Food.hpp"


SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake AI")
    , snake(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2))
    , food(snake.get_positions())
{

    window.setFramerateLimit(FPS_LIMIT);

    //load fonts
    if (!font_fps.loadFromFile("font.ttf")) {
        //isError = true;
        //Errors.push_back("Error loading font.ttf");
    }
    if (!font_papyrus.loadFromFile("papyrus.ttf")) {
        //isError = true;
        //Errors.push_back("Error loading papyrus.ttf");
    }

    //generate head of snake
    snake.setTextures(); //food and snakes

    srand(time(0));

    fpsText.setFont(font_fps);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));
    //draw_objects.push_back(std::make_unique<Snake>()); // fix this one
}

SnakeGame::~SnakeGame() {
    //nic take
}

void SnakeGame::run() {
    std::cout << "run()\n";

    gameOver = false;
    while (window.isOpen()) {
        //if (isError) std::cout << "-------------------------------\nError\n\n";
        //for (auto& a : Errors) {
        //    std::cout << a << std::endl;
        //}

        handleInput();
        update();
        render();

        if (gameOver) retryMenu();
    }
}

void SnakeGame::retryMenu() {
    setRetryText();
    restartGame = false;

    while (window.isOpen() && !restartGame) {
        retryInput();
        render();
    }
}

void SnakeGame::handleInput() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                window.close();

                break;
            }

            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        window.close();

                        break;
                    }

                    case sf::Keyboard::Left:
                    {
                        snake.set_direction(-BLOCK_SIZE, 0);
                        std::cout << "Input = Left\n";
                        
                        break;
                    }

                    case sf::Keyboard::Right:
                    {
                        snake.set_direction(BLOCK_SIZE, 0);
                        std::cout << "Input = Right\n";

                        break;
                    }

                    case sf::Keyboard::Up:
                    {
                        snake.set_direction(0, -BLOCK_SIZE);
                        std::cout << "Input = Up\n";

                        break;
                    }

                    case sf::Keyboard::Down:
                    {
                        snake.set_direction(0, BLOCK_SIZE);
                        std::cout << "Input = Down\n";

                        break;
                    }
                    default:
                        std::cout << "whats that brother?\n";
                    break;
                }
            }

        default:
            //std::cout << "unknown event type\n";
            break;
        }
    }
}

void SnakeGame::retryInput() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        //check mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (retry.getGlobalBounds().contains(mousePos))
            {
                restartGame = true;
                //std::cout << "Restart" << std::endl;
                //button pressed
            }
        }
    }
}

void SnakeGame::setRetryText() {
    endOfGame.setFont(font_papyrus);
    endOfGame.setString("Game Over");
    endOfGame.setFillColor(sf::Color::Red);
    endOfGame.setStyle(sf::Text::Bold);
    endOfGame.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f);

    retry.setFillColor(sf::Color::White);
    retry.setSize(sf::Vector2f(100, 50));
    retry.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);

    restart.setFont(font_papyrus);
    restart.setString("Try Again");
    restart.setFillColor(sf::Color::Black);
    restart.setStyle(sf::Text::Bold);
    restart.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f - 70);
}

void SnakeGame::update() {
    fpsCounter++; //increase frame counter

    if (fpsCounter >= (FPS_LIMIT / SNAKE_SPEED)) {
        fpsCounter = 0;

        gameOver != snake.move();

        //last move
        snake.set_old_direction();
    }

    lastTime = now;
    now = std::chrono::high_resolution_clock::now();
    fps = 1.f / std::chrono::duration_cast<std::chrono::duration<float>>(now - lastTime).count();
    
    fpsText.setString(std::to_string(fps));
}

void SnakeGame::render() {
    window.clear();

    for (auto& object : draw_objects)
        object->draw(window);

    snake.draw(window);
    food.draw(window);

    window.draw(fpsText);
    window.draw(endOfGame);
    window.draw(retry);
    window.draw(restart);

    window.display();
    //std::cout << "Render done\n";
}