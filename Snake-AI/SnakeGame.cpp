#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"

#include "Milan.hpp"


SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake AI")
    , event()
    , snake(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2))
    , food(find_empty_cell())
    , menu()
{

    window.setFramerateLimit(FPS_LIMIT);
    srand(time(0));

    snake.setTextures(sf::Color::Blue); //food and snakes

    if (!general_font.loadFromFile("font.ttf")) {
        //isError = true;
        //Errors.push_back("Error loading font.ttf");
    }

    fpsText.setFont(general_font);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner

    scoreText.setFont(general_font);
    scoreText.setFillColor(sf::Color::White);

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));
    //draw_objects.push_back(std::make_unique<Milan>());

    ai_snakes.push_back(std::make_unique<Snake>(find_empty_cell()));
    ai_snakes.push_back(std::make_unique<Snake>(find_empty_cell()));
    ai_snakes.push_back(std::make_unique<Snake>(find_empty_cell()));
    ai_snakes.push_back(std::make_unique<Snake>(find_empty_cell()));

    for (auto& ai_snake : ai_snakes) {
        ai_snake->setTextures(sf::Color::Yellow);
    }
}

void SnakeGame::run() {

    gameOver = false;
    while (window.isOpen()) {
        //if (isError) std::cout << "-------------------------------\nError\n\n";
        //for (auto& a : Errors) {
        //    std::cout << a << std::endl;
        //}

        while (pause) {
            handleInput();
        }

        handleInput();
        update();
        render();

        if (gameOver) retryMenu();
        gameOver = false;
    }
}

void SnakeGame::retryMenu() {
    restartGame = false;

    snake.reset(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2));

    while (window.isOpen() && !restartGame) {

        retryInput();

        window.clear();
        menu.draw(window);
        window.display();
    }
}

void SnakeGame::handleInput() {
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
                Direction last_dir = snake.get_direction();

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Left && last_dir != Right)
                {
                    snake.set_direction(Left);
                }
                else if (event.key.code == sf::Keyboard::Right && last_dir != Left)
                {
                    snake.set_direction(Right);
                }
                else if (event.key.code == sf::Keyboard::Up && last_dir != Down)
                {
                    snake.set_direction(Up);
                }
                else if (event.key.code == sf::Keyboard::Down && last_dir != Up)
                {
                    snake.set_direction(Down);
                }

				if (event.key.code == sf::Keyboard::P) {
					pause = !pause;
				}
            }

        default:
            //std::cout << "unknown event type\n";
            break;
        }
    }
}

void SnakeGame::retryInput() {
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        //check mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (menu.click(window))
            {
                restartGame = true;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            restartGame = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }
}

void SnakeGame::update() {
    fpsCounter++; //increase frame counter

    if (fpsCounter >= (FPS_LIMIT / SNAKE_SPEED)) {
        fpsCounter = 0;
        
        gameOver = !snake.move();

        if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());

        //last move
        snake.set_old_direction();

        for (auto& ai_snake : ai_snakes) {
            ai_snake->set_random_direction();
            if (!ai_snake->move()) ai_snake->reset(find_empty_cell());
            if (ai_snake->eats(food.get_position())) food.generateFood(find_empty_cell());
            ai_snake->set_old_direction();
        }
    }

    lastTime = now;
    now = std::chrono::high_resolution_clock::now();
    fps = 1.f / std::chrono::duration_cast<std::chrono::duration<float>>(now - lastTime).count();
    
    fpsText.setString(std::to_string(fps));

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

void SnakeGame::render() {
    window.clear();

    for (auto& object : draw_objects)
        object->draw(window);

    for (auto& ai_snake : ai_snakes) {
        ai_snake->draw(window);
    }

    snake.draw(window);
    food.draw(window);

    window.draw(fpsText);
    window.draw(scoreText);

    window.display();
}

sf::Vector2f SnakeGame::find_empty_cell()
{
    sf::Vector2f freePos;

    //find valid position
    bool invalidPos;
    do {
        invalidPos = false;

        freePos.x = rand() % PIXEL_SIZE * BLOCK_SIZE;
        freePos.y = rand() % PIXEL_SIZE * BLOCK_SIZE;

        if (freePos == food.get_position()) invalidPos = true;

        for (const sf::Vector2f s : snake.get_positions()) {
            if (freePos == s) {
                invalidPos = true;
                break;
            }
        }

        for (const auto& ai_snake : ai_snakes) {
            for (const sf::Vector2f s : ai_snake->get_positions()) {
                if (freePos == s) {
                    invalidPos = true;
                    break;
                }
            }
        }

    } while (invalidPos);

    return freePos;
}
