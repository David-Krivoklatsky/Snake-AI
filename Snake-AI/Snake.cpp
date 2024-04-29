#include "Snake.hpp"
#include "Globals.hpp"

#include <iostream>

Snake::Snake() {
    positions.push_back(find_empty_cell());
    move();
}

Snake::Snake(const sf::Vector2f& pos) {
    positions.push_back(pos);
    move();
}

bool Snake::move() {
    //inserts new pos to positions depending on the direction it is moving
    positions.insert(positions.begin(), sf::Vector2f(positions[0].x + changeX, positions[0].y + changeY));

    bool legal = true;

    if (positions[0].x < 0 || positions[0].x >= WINDOW_SIZE || positions[0].y < 0 || positions[0].y >= WINDOW_SIZE) {
        legal = false;
    }

    for (int i = 1; i < positions.size() - 1; i++) {
        if (positions[0] == positions[i]) {
            legal = false;
        }
    }
    return legal;
}

bool Snake::eats(const sf::Vector2f& jedlo)
{
    if (positions[0] == jedlo) {
        return true;
    }
    else {
        positions.pop_back();
        return false;
    }
}

void Snake::setTextures() {
    std::string folder = "Snake_texture";

    if (!tail_left.loadFromFile(folder + "/tail_left.png")) {
        //isError = true;
    }
    else {
        tailLeft.setTexture(tail_left);
    }

    if (!tail_right.loadFromFile(folder + "/tail_right.png")) {
        //isError = true;
    }
    else {
        tailRight.setTexture(tail_right);
    }

    if (!tail_down.loadFromFile(folder + "/tail_down.png")) {
        //isError = true;
    }
    else {
        tailDown.setTexture(tail_down);
    }

    if (!tail_up.loadFromFile(folder + "/tail_up.png")) {
        //isError = true;
    }
    else {
        tailUp.setTexture(tail_up);
    }

    if (!horizontal.loadFromFile(folder + "/body_horizontal.png")) {
        //isError = true;
    }
    else {
        horiz.setTexture(horizontal);
    }

    if (!vertical.loadFromFile(folder + "/body_vertical.png")) {
        //isError = true;
    }
    else {
        vertic.setTexture(vertical);
    }

    if (!topright.loadFromFile(folder + "/body_topright.png")) {
        //isError = true;
    }
    else {
        topRight.setTexture(topright);
    }

    if (!topleft.loadFromFile(folder + "/body_topleft.png")) {
        //isError = true;
    }
    else {
        topLeft.setTexture(topleft);
    }

    if (!bottomleft.loadFromFile(folder + "/body_bottomleft.png")) {
        //isError = true;
    }
    else {
        bottomLeft.setTexture(bottomleft);
    }

    if (!bottomright.loadFromFile(folder + "/body_bottomright.png")) {
        //isError = true;
    }
    else {
        bottomRight.setTexture(bottomright);
    }

    if (!head_left.loadFromFile(folder + "/head_left.png")) {
        //isError = true;
    }
    else {
        headLeft.setTexture(head_left);
    }

    if (!head_right.loadFromFile(folder + "/head_right.png")) {
        //isError = true;
    }
    else {
        headRight.setTexture(head_right);
    }

    if (!head_down.loadFromFile(folder + "/head_down.png")) {
        //isError = true;
    }
    else {
        headDown.setTexture(head_down);
    }

    if (!head_up.loadFromFile(folder + "/head_up.png")) {
        //isError = true;
    }
    else {
        headUp.setTexture(head_up);
    }
}

void Snake::draw(sf::RenderWindow& window) {
    if (lastChangedX == -BLOCK_SIZE) { //head
        headLeft.setPosition(positions[0]);
        window.draw(headLeft);
    }
    else if (lastChangedX == BLOCK_SIZE) {
        headRight.setPosition(positions[0]);
        window.draw(headRight);
    }
    else if (lastChangedY == -BLOCK_SIZE) {
        headUp.setPosition(positions[0]);
        window.draw(headUp);
    }
    else if (lastChangedY == BLOCK_SIZE) {
        headDown.setPosition(positions[0]);
        window.draw(headDown);
    }

    if (positions.size() > 1) { //tail
        if (positions[positions.size() - 2].x == positions[positions.size() - 1].x && positions[positions.size() - 2].y > positions[positions.size() - 1].y) {
            tailUp.setPosition(positions[positions.size() - 1]);
            window.draw(tailUp);
        }
        else if (positions[positions.size() - 2].x == positions[positions.size() - 1].x && positions[positions.size() - 2].y < positions[positions.size() - 1].y) {
            tailDown.setPosition(positions[positions.size() - 1]);
            window.draw(tailDown);
        }
        else if (positions[positions.size() - 2].x < positions[positions.size() - 1].x && positions[positions.size() - 2].y == positions[positions.size() - 1].y) {
            tailRight.setPosition(positions[positions.size() - 1]);
            window.draw(tailRight);
        }
        else if (positions[positions.size() - 2].x > positions[positions.size() - 1].x && positions[positions.size() - 2].y == positions[positions.size() - 1].y) {
            tailLeft.setPosition(positions[positions.size() - 1]);
            window.draw(tailLeft);
        }
    }

    if (positions.size() > 2) { // if snakes length is bigger then 2 it has middle snake part (chest or smth like that) (everything except tail and head)
        for (int i = 1; i < positions.size() - 1; i++) {
            if (positions[i + 1].x == positions[i - 1].x && positions[i + 1].y != positions[i - 1].y) {
                vertic.setPosition(positions[i]);
                window.draw(vertic);
            }
            else if (positions[i + 1].x != positions[i - 1].x && positions[i + 1].y == positions[i - 1].y) {
                horiz.setPosition(positions[i]);
                window.draw(horiz);
            }
            else if ((positions[i - 1].x > positions[i].x && positions[i + 1].y > positions[i].y) || (positions[i + 1].x > positions[i].x && positions[i - 1].y > positions[i].y)) {
                bottomRight.setPosition(positions[i]);
                window.draw(bottomRight);
            }
            else if ((positions[i - 1].x < positions[i].x && positions[i + 1].y < positions[i].y) || (positions[i + 1].x < positions[i].x && positions[i - 1].y < positions[i].y)) {
                topLeft.setPosition(positions[i]);
                window.draw(topLeft);
            }
            else if ((positions[i - 1].x < positions[i].x && positions[i + 1].y > positions[i].y) || (positions[i + 1].x < positions[i].x && positions[i - 1].y > positions[i].y)) {
                bottomLeft.setPosition(positions[i]);
                window.draw(bottomLeft);
            }
            else if ((positions[i - 1].x > positions[i].x && positions[i + 1].y < positions[i].y) || (positions[i + 1].x > positions[i].x && positions[i - 1].y < positions[i].y)) {
                topRight.setPosition(positions[i]);
                window.draw(topRight);
            }
        }
    }
}

std::vector<sf::Vector2f> Snake::get_positions()
{
    return positions;
}

void Snake::set_direction(int x, int y)
{
    changeX = x;
    changeY = y;
}

void Snake::set_old_direction()
{
    lastChangedX = changeX;
    lastChangedY = changeY;
}

Direction Snake::get_direction()
{
    if (lastChangedY < 0) return Up;
    if (lastChangedY > 0) return Down;
    if (lastChangedX < 0) return Left;
    if (lastChangedX > 0) return Right;
}

void Snake::reset(const sf::Vector2f& pos)
{
    positions.clear();
    
    changeX = 0, changeY = -BLOCK_SIZE, lastChangedX = 0, lastChangedY = 0;

    positions.push_back(pos);
    move();
}

void AI_Snake::set_random_direction()
{
    Direction new_dir;
    do {
        new_dir = static_cast<Direction>(std::rand() % 4 + 1);
    } while (new_dir == get_direction());

    switch (new_dir) {
    case Up:
        changeX = 0;
        changeY = -BLOCK_SIZE;
        break;
    case Down:
        changeX = 0;
        changeY = BLOCK_SIZE;
        break;
    case Left:
        changeX = -BLOCK_SIZE;
        changeY = 0;
        break;
    case Right:
        changeX = BLOCK_SIZE;
        changeY = 0;
        break;
    }
}

AI_Snake::AI_Snake(const sf::Vector2f& pos) {
    positions.push_back(pos);
    move();
}