#pragma once

#include "Globals.hpp"

#include <SFML/Graphics.hpp>

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