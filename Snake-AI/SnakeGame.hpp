#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "DrawObjects.hpp"
#include "Globals.hpp"
#include "Snake.hpp"
#include "Food.hpp"

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();
    void retryMenu();

private:
    void setRetryText();
    void handleInput();
    void retryInput();
    void update();
    void render();

public:
    bool restartGame = false;

private:
    sf::RenderWindow window;

    Snake snake;
    Food food;

    bool gameOver = false;
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
};