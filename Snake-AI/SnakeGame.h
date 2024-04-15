#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "DrawObjects.h"
#include "Globals.h"
#include "Snake.h"

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();
    void retryMenu();

private:
    void setRetryText();
    void drawSnake();
    void drawFood();
    sf::Vector2f generateFood();
    //void moveSnake(const sf::Vector2f&);
    bool legalMove();
    void handleInput();
    void retryInput();
    void update();
    void render();

public:
    bool restartGame = false;

private:
    sf::RenderWindow window;

    sf::Vector2f food_pos;
    int changeX = 0, changeY = 0, lastChangedX, lastChangedY;
    bool gameOver = false;
    bool isError = false;
    int fpsCounter = 0;
    sf::Font font_fps;
    sf::Font font_papyrus;
    sf::Text fpsText;
    sf::Text endOfGame;
    sf::Text restart;
    sf::RectangleShape retry;
    std::chrono::high_resolution_clock::time_point lastTime, now;
    float fps;

    std::vector<std::unique_ptr<DrawObject>> draw_objects;

    std::vector<std::string> Errors;

    sf::Texture jablko;

    sf::Sprite food;
};