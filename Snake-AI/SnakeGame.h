#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>



constexpr int WINDOW_SIZE = 800;
constexpr int PIXEL_SIZE = 20;
constexpr int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE;
constexpr int FPS_LIMIT = 60;
constexpr float SNAKE_SPEED = 7.f;

class DrawObject {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    ~DrawObject() = default;
};

class Grid : public DrawObject {
public:
    Grid(int size) : block(sf::Vector2f(size, size)) {}

    virtual void draw(sf::RenderWindow& window) override {
        for (int i = 0; i < PIXEL_SIZE; i++) {
            for (int j = 0; j < PIXEL_SIZE; j++) {
                block.setPosition(sf::Vector2f(BLOCK_SIZE * j, BLOCK_SIZE * i));

                sf::Color primary(60, 60, 60);
                sf::Color secondary(120, 120, 120);
                block.setFillColor(((i + j) % 2) ? primary : secondary);

                window.draw(block);
            }
        }
    }
private:
    sf::RectangleShape block;

};

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();
    void retryMenu();

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

public:
    bool restartGame = false;

private:
    sf::RenderWindow window;
    std::vector<sf::Vector2f> snake;
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

    std::vector<std::unique_ptr<DrawObject>> objects;

    std::vector<std::string> Errors;

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
};