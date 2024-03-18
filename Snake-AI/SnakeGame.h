#pragma once

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();

private:
    void drawGrid();
    void drawSnake();
    void drawFood();
    sf::Vector2f generateFood();
    bool isGameOver();
    void handleInput();
    void update();
    void render();

    sf::RenderWindow window;
    sf::RectangleShape block;
    std::vector<sf::Vector2f> snake;
    sf::Sprite food;
    sf::Texture jablko;
    sf::Vector2f food_pos;
    int changeX, changeY, lastChangedX, lastChangedY;
    bool gameOver;
    bool isError;
    int fpsCounter;
    sf::Font font;
    sf::Text fpsText;
    sf::Text endOfGame;
    sf::Text restart;
    sf::RectangleShape retry;
    std::chrono::high_resolution_clock::time_point lastTime, now;
    float fps;

    const int WINDOW_SIZE = 800;
    const int PIXEL_SIZE = 20;
    const int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE;
    const int FPS_LIMIT = 60;
    const float SNAKE_SPEED = 7.f;
};

#endif // SNAKE_GAME_H
