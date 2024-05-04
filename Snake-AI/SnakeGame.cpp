#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "StartMenu.hpp"

#include "Milan.hpp"


SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake AI")
    , event()
    , snake(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2))
    , food(find_empty_cell())
    , menu()
    , startMenu()
{

    window.setFramerateLimit(FPS_LIMIT);
    srand(time(0));

    startMenu.assignFilenames(textureFiles, startMenu.numberOfSkins);
    snake.setTextures(textureFiles[skinChose]); //food and snakes

    if (!fps_font.loadFromFile("font.ttf")) {
        //isError = true;
        //Errors.push_back("Error loading font.ttf");
    }

    fpsText.setFont(fps_font);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));
    //draw_objects.push_back(std::make_unique<Milan>());

    //ai_snakes.push_back(std::make_unique<Snake>());
    //ai_snakes.push_back(std::make_unique<Snake>());
    //ai_snakes.push_back(std::make_unique<Snake>());

}

void SnakeGame::run() {
    gameOver = false;
    while (window.isOpen()) {
        //if (isError) std::cout << "-------------------------------\nError\n\n";
        //for (auto& a : Errors) {
        //    std::cout << a << std::endl;
        //}
        while (start_menu) {
            startInput();

            window.clear();
            startMenu.draw(window);
            window.display();
        }

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

void SnakeGame::startInput()
{
    while (window.pollEvent(event)) {
        switch (event.type){

        case sf::Event::Closed: {
            window.close();

            break;
        }
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Space) {
                start_menu = false;
            }
        }

        }
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
                    snake.set_direction(-BLOCK_SIZE, 0);
                }
                else if (event.key.code == sf::Keyboard::Right && last_dir != Left)
                {
                    snake.set_direction(BLOCK_SIZE, 0);
                }
                else if (event.key.code == sf::Keyboard::Up && last_dir != Down)
                {
                    snake.set_direction(0, -BLOCK_SIZE);
                }
                else if (event.key.code == sf::Keyboard::Down && last_dir != Up)
                {
                    snake.set_direction(0, BLOCK_SIZE);
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

        if (snake.eats(food.get_position())) {
            food.generateFood(find_empty_cell());
        }

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

    //window.draw(fpsText);

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

        for (const auto& snake : ai_snakes) {
            for (const sf::Vector2f s : snake->get_positions()) {
                if (freePos == s) {
                    invalidPos = true;
                    break;
                }
            }
        }

    } while (invalidPos);

    return freePos;
}
