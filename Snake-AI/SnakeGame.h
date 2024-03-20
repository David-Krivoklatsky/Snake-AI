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
    void retryMenu();
    bool restartGame;

private:
    void setTextures();
    void setRetryText();
    void drawGrid();
    void drawSnake();
    void drawFood();
    sf::Vector2f generateFood();
    void moveSnake(const sf::Vector2f&);
    bool legalMove();
    void handleInput();
    void retryInput();
    void update();
    void render();

    sf::RenderWindow window;
    sf::RectangleShape block;
    std::vector<sf::Vector2f> snake;
    sf::Vector2f food_pos;
    int changeX, changeY, lastChangedX, lastChangedY;
    bool gameOver;
    bool isError;
    int fpsCounter;
    sf::Font font_fps;
    sf::Font font_papyrus;
    sf::Text fpsText;
    sf::Text endOfGame;
    sf::Text restart;
    sf::RectangleShape retry;
    std::chrono::high_resolution_clock::time_point lastTime, now;
    float fps;

    sf::Texture jablko;
    sf::Texture tail_left;
    sf::Texture tail_right;
    sf::Texture tail_down;
    sf::Texture tail_up;
    sf::Texture horizontal;
    sf::Texture vertical;
    sf::Texture topright;
    sf::Texture topleft;
    sf::Texture bottomleft;
    sf::Texture bottomright;
    sf::Texture head_left;
    sf::Texture head_right;
    sf::Texture head_down;
    sf::Texture head_up;

    sf::Sprite food;
    sf::Sprite tailLeft;
    sf::Sprite tailRight;
    sf::Sprite tailDown;
    sf::Sprite tailUp;
    sf::Sprite horiz;
    sf::Sprite vertic;
    sf::Sprite topRight;
    sf::Sprite topLeft;
    sf::Sprite bottomLeft;
    sf::Sprite bottomRight;
    sf::Sprite headLeft;
    sf::Sprite headRight;
    sf::Sprite headDown;
    sf::Sprite headUp;

    const int WINDOW_SIZE = 800;
    const int PIXEL_SIZE = 20;
    const int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE;
    const int FPS_LIMIT = 60;
    const float SNAKE_SPEED = 7.f;
};

#endif
