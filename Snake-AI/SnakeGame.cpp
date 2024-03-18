#include "SnakeGame.h"
#include <Windows.h>
#include <ctime>

SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI")
    , block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE))
    , gameOver(false)
    , isError(false)
    , changeX(0)
    , changeY(0)
    , fpsCounter(0)
{
    window.setFramerateLimit(FPS_LIMIT);

    if (!font.loadFromFile("font.ttf")) {
        isError = true;
    }

    if (!jablko.loadFromFile("jablcko.png")) {
        isError = true;
        food.setColor(sf::Color::Red);
    }
    else {
        food.setTexture(jablko); //set texture only if it loaded
    }

    //generate head of snake
    snake.push_back(sf::Vector2f(PIXEL_SIZE / 2 * BLOCK_SIZE, PIXEL_SIZE / 2 * BLOCK_SIZE));
    food_pos = generateFood(); //generate first food

    srand(time(0));

    fpsText.setFont(font);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner


}

SnakeGame::~SnakeGame() {
    //nic take
}

void SnakeGame::run() {
    while (window.isOpen()) {
        handleInput();
        update();
        render();
    }
}

void SnakeGame::handleInput() {
    sf::Event event;
    if (event.type == sf::Event::Closed) //zavretie okna
        window.close();

    //Handle LEFT, RIGHT, UP, DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (lastChangedX != BLOCK_SIZE))
    {
        changeX = -BLOCK_SIZE;
        changeY = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (lastChangedX != -BLOCK_SIZE))
    {
        changeX = BLOCK_SIZE;
        changeY = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (lastChangedY != BLOCK_SIZE))
    {
        changeX = 0;
        changeY = -BLOCK_SIZE;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (lastChangedY != -BLOCK_SIZE))
    {
        changeX = 0;
        changeY = BLOCK_SIZE;
    }
}

void SnakeGame::drawGrid() {
    // Drawing grid logic
}

void SnakeGame::drawSnake() {
    // Drawing snake logic
}

void SnakeGame::drawFood() {
    // Drawing food logic
}

sf::Vector2f SnakeGame::generateFood() {
    // Generating food logic
}

bool SnakeGame::isGameOver() {
    // Game over condition logic
}

void SnakeGame::update() {
    // Game update logic
}

void SnakeGame::render() {
    window.clear();

    drawGrid();
    drawSnake();
    drawFood();

    window.draw(fpsText);
    window.draw(endOfGame);
    window.draw(retry);
    window.draw(restart);

    window.display();
}
