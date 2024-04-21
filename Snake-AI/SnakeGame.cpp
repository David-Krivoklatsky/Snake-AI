#include <iostream>
#include <ctime>

#include "Globals.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"


SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake AI")
{

    window.setFramerateLimit(FPS_LIMIT);

    //load fonts
    if (!font_fps.loadFromFile("font.ttf")) {
        isError = true;
        Errors.push_back("Error loading font.ttf");
    }
    if (!font_papyrus.loadFromFile("papyrus.ttf")) {
        isError = true;
        Errors.push_back("Error loading papyrus.ttf");
    }


    //generate head of snake
    Snake snake(sf::Vector2f(PIXEL_SIZE / 2 * BLOCK_SIZE, PIXEL_SIZE / 2 * BLOCK_SIZE));
    snake.setTextures(); //food and snakes

    food_pos = generateFood(); //generate first food

    srand(time(0));

    fpsText.setFont(font_fps);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));


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
        if (event.type == sf::Event::Closed) //zavretie okna
            window.close();

        //Handle LEFT, RIGHT, UP, DOWN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (lastChangedX != BLOCK_SIZE))
        {
            changeX = -BLOCK_SIZE;
            changeY = 0;
        std::cout << "Input = Left\n";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (lastChangedX != -BLOCK_SIZE))
        {
            changeX = BLOCK_SIZE;
            changeY = 0;
            std::cout << "Input = Right\n";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (lastChangedY != BLOCK_SIZE))
        {
            changeX = 0;
            changeY = -BLOCK_SIZE;
            std::cout << "Input = Up\n";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (lastChangedY != -BLOCK_SIZE))
        {
            changeX = 0;
            changeY = BLOCK_SIZE;
            std::cout << "Input = Down\n";
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

bool SnakeGame::legalMove() {
    if (snake[0].x < 0 && snake[0].x >= WINDOW_SIZE && snake[0].y < 0 && snake[0].y >= WINDOW_SIZE) {
        return false;
    }
    
    for (int i = 1; i < snake.size(); i++) {
        if (snake[0] == snake[i]) {
            return false;
        }
    }

    return true;
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

        snake.move();
        gameOver = !legalMove();


        //last move
        snake.lastChangedX = snake.changeX;
        snake.lastChangedY = snake.changeY;
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

    drawFood();


    window.draw(fpsText);
    window.draw(endOfGame);
    window.draw(retry);
    window.draw(restart);

    window.display();
    //std::cout << "Render done\n";
}