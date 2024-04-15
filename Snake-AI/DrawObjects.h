#pragma once

#include "Globals.h"

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

class Snake : public DrawObject {
public:
    Snake(int size) : block(sf::Vector2f(size, size)) {}

    virtual void draw(sf::RenderWindow& window) override {
        if (changeX == -BLOCK_SIZE) { //head
            headLeft.setPosition(snake[0]);
            window.draw(headLeft);
        }
        else if (changeX == BLOCK_SIZE) {
            headRight.setPosition(snake[0]);
            window.draw(headRight);
        }
        else if (changeY == -BLOCK_SIZE) {
            headUp.setPosition(snake[0]);
            window.draw(headUp);
        }
        else if (changeY == BLOCK_SIZE) {
            headDown.setPosition(snake[0]);
            window.draw(headDown);
        }

        if (snake.size() > 1) { //tail
            if (snake[snake.size() - 2].x == snake[snake.size() - 1].x && snake[snake.size() - 2].y > snake[snake.size() - 1].y) {
                tailUp.setPosition(snake[snake.size() - 1]);
                window.draw(tailUp);
            }
            else if (snake[snake.size() - 2].x == snake[snake.size() - 1].x && snake[snake.size() - 2].y < snake[snake.size() - 1].y) {
                tailDown.setPosition(snake[snake.size() - 1]);
                window.draw(tailDown);
            }
            else if (snake[snake.size() - 2].x < snake[snake.size() - 1].x && snake[snake.size() - 2].y == snake[snake.size() - 1].y) {
                tailRight.setPosition(snake[snake.size() - 1]);
                window.draw(tailRight);
            }
            else if (snake[snake.size() - 2].x > snake[snake.size() - 1].x && snake[snake.size() - 2].y == snake[snake.size() - 1].y) {
                tailLeft.setPosition(snake[snake.size() - 1]);
                window.draw(tailLeft);
            }
        }

        if (snake.size() > 2) { // if snakes length is bigger then 2 it has middle snake part (chest or smth like that) (everything except tail and head)
            for (int i = 1; i < snake.size() - 1; i++) {
                if (snake[i + 1].x == snake[i - 1].x && snake[i + 1].y != snake[i - 1].y) {
                    vertic.setPosition(snake[i]);
                    window.draw(vertic);
                }
                else if (snake[i + 1].x != snake[i - 1].x && snake[i + 1].y == snake[i - 1].y) {
                    horiz.setPosition(snake[i]);
                    window.draw(horiz);
                }
                else if ((snake[i - 1].x > snake[i].x && snake[i + 1].y > snake[i].y) || (snake[i + 1].x > snake[i].x && snake[i - 1].y > snake[i].y)) {
                    bottomRight.setPosition(snake[i]);
                    window.draw(bottomRight);
                }
                else if ((snake[i - 1].x < snake[i].x && snake[i + 1].y < snake[i].y) || (snake[i + 1].x < snake[i].x && snake[i - 1].y < snake[i].y)) {
                    topLeft.setPosition(snake[i]);
                    window.draw(topLeft);
                }
                else if ((snake[i - 1].x < snake[i].x && snake[i + 1].y > snake[i].y) || (snake[i + 1].x < snake[i].x && snake[i - 1].y > snake[i].y)) {
                    bottomLeft.setPosition(snake[i]);
                    window.draw(bottomLeft);
                }
                else if ((snake[i - 1].x > snake[i].x && snake[i + 1].y < snake[i].y) || (snake[i + 1].x > snake[i].x && snake[i - 1].y < snake[i].y)) {
                    topRight.setPosition(snake[i]);
                    window.draw(topRight);
                }
            }
        }
    }
};