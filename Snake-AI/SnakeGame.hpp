#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "DrawObjects.hpp"
#include "Globals.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"

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

    sf::Vector2f find_empty_cell();

public:
    bool restartGame = false;

private:
    sf::RenderWindow window;
    sf::Event event;

    Snake snake;
    Food food;
    Menu menu;

    std::vector<std::unique_ptr<Snake>> ai_snakes;

    sf::Text fpsText;
    sf::Font fps_font;

    bool gameOver = false;
    int fpsCounter = 0;
    float fps = 60;

    std::chrono::high_resolution_clock::time_point lastTime, now;

    std::vector<std::unique_ptr<DrawObject>> draw_objects;
};