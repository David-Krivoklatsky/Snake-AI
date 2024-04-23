#include "Snake.hpp"
#include "Globals.hpp"

Snake::Snake(const sf::Vector2f& pos) {
    positions.push_back(pos);
}

bool Snake::move() {
    //inserts new pos to positions depending on the direction it is moving
    positions.insert(positions.begin(), sf::Vector2f(positions[0].x + changeX, positions[0].y + changeY));

    if (positions[0].x < 0 && positions[0].x >= WINDOW_SIZE && positions[0].y < 0 && positions[0].y >= WINDOW_SIZE) {
        return false;
    }

    for (int i = 1; i < positions.size(); i++) {
        if (positions[0] == positions[i]) {
            return false;
        }
    }

    return true;
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
    if (!tail_left.loadFromFile("Snake_texture/tail_left.png")) {
        //isError = true;
    }
    else {
        tailLeft.setTexture(tail_left);
    }

    if (!tail_right.loadFromFile("Snake_texture/tail_right.png")) {
        //isError = true;
    }
    else {
        tailRight.setTexture(tail_right);
    }

    if (!tail_down.loadFromFile("Snake_texture/tail_down.png")) {
        //isError = true;
    }
    else {
        tailDown.setTexture(tail_down);
    }

    if (!tail_up.loadFromFile("Snake_texture/tail_up.png")) {
        //isError = true;
    }
    else {
        tailUp.setTexture(tail_up);
    }

    if (!horizontal.loadFromFile("Snake_texture/body_horizontal.png")) {
        //isError = true;
    }
    else {
        horiz.setTexture(horizontal);
    }

    if (!vertical.loadFromFile("Snake_texture/body_vertical.png")) {
        //isError = true;
    }
    else {
        vertic.setTexture(vertical);
    }

    if (!topright.loadFromFile("Snake_texture/body_topright.png")) {
        //isError = true;
    }
    else {
        topRight.setTexture(topright);
    }

    if (!topleft.loadFromFile("Snake_texture/body_topleft.png")) {
        //isError = true;
    }
    else {
        topLeft.setTexture(topleft);
    }

    if (!bottomleft.loadFromFile("Snake_texture/body_bottomleft.png")) {
        //isError = true;
    }
    else {
        bottomLeft.setTexture(bottomleft);
    }

    if (!bottomright.loadFromFile("Snake_texture/body_bottomright.png")) {
        //isError = true;
    }
    else {
        bottomRight.setTexture(bottomright);
    }

    if (!head_left.loadFromFile("Snake_texture/head_left.png")) {
        //isError = true;
    }
    else {
        headLeft.setTexture(head_left);
    }

    if (!head_right.loadFromFile("Snake_texture/head_right.png")) {
        //isError = true;
    }
    else {
        headRight.setTexture(head_right);
    }

    if (!head_down.loadFromFile("Snake_texture/head_down.png")) {
        //isError = true;
    }
    else {
        headDown.setTexture(head_down);
    }

    if (!head_up.loadFromFile("Snake_texture/head_up.png")) {
        //isError = true;
    }
    else {
        headUp.setTexture(head_up);
    }
}

void Snake::draw(sf::RenderWindow& window) {
    if (changeX == -BLOCK_SIZE) { //head
        headLeft.setPosition(positions[0]);
        window.draw(headLeft);
    }
    else if (changeX == BLOCK_SIZE) {
        headRight.setPosition(positions[0]);
        window.draw(headRight);
    }
    else if (changeY == -BLOCK_SIZE) {
        headUp.setPosition(positions[0]);
        window.draw(headUp);
    }
    else if (changeY == BLOCK_SIZE) {
        headDown.setPosition(positions[0]);
        window.draw(headDown);
    }

    if (positions.size() > 1) { //tail
        if (positions[positions.size() - 2].x == positions.back().x && positions[positions.size() - 2].y > positions.back().y) {
            tailUp.setPosition(positions.back());
            window.draw(tailUp);
        }
        else if (positions[positions.size() - 2].x == positions.back().x && positions[positions.size() - 2].y < positions.back().y) {
            tailDown.setPosition(positions.back());
            window.draw(tailDown);
        }
        else if (positions[positions.size() - 2].x < positions.back().x && positions[positions.size() - 2].y == positions.back().y) {
            tailRight.setPosition(positions.back());
            window.draw(tailRight);
        }
        else if (positions[positions.size() - 2].x > positions.back().x && positions[positions.size() - 2].y == positions.back().y) {
            tailLeft.setPosition(positions.back());
            window.draw(tailLeft);
        }
    }

    if (positions.size() > 2) { // if positionss length is bigger then 2 it has middle positions part (chest or smth like that) (everything except tail and head)
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