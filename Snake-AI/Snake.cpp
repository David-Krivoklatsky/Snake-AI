#include "Snake.hpp"
#include "Globals.hpp"
#include "StartMenu.hpp"

#include <fstream>
#include <iostream>

Snake::Snake(const sf::Vector2f& pos)
    : last_dir(Unknown)
{
    positions.push_back(pos);
    set_random_direction();
    move();
}

void Snake::move() {
    //inserts new pos to positions depending on the direction it is moving
    int changeX = 0, changeY = 0;

    switch (current_dir) {
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

    positions.insert(positions.begin(), sf::Vector2f(positions[0].x + changeX, positions[0].y + changeY));
}

bool Snake::legal_move()
{
    bool legal = true;

    //ci narazil do steny
    if (positions[0].x < 0 || positions[0].x >= WINDOW_SIZE || positions[0].y < 0 || positions[0].y >= WINDOW_SIZE) {
        legal = false;
		//std::cout << "Narazil do steny" << std::endl;
    }

    //ci je idiot a krizuje sa sam so sebou
    for (int i = 1; i < positions.size() - 1; i++) {
        if (positions[0] == positions[i]) {
            legal = false;
			//std::cout << "Narazil do seba" << std::endl;
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

void Snake::setTextures(sf::Color farba) {

    std::string folder;

    if (farba == sf::Color::Yellow) folder = "Snake_texture2";
    else folder = "Snake_texture1";

    setTextures(folder);
}

void Snake::setTextures(std::string folder)
{
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
    if (last_dir == Left) { //head
        headLeft.setPosition(positions[0]);
        window.draw(headLeft);
    }
    else if (last_dir == Right) {
        headRight.setPosition(positions[0]);
        window.draw(headRight);
    }
    else if (last_dir == Up) {
        headUp.setPosition(positions[0]);
        window.draw(headUp);
    }
    else if (last_dir == Down) {
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

void Snake::set_direction(Direction d)
{
    current_dir = d;
}

void Snake::set_old_direction()
{
    last_dir = current_dir;
}

Direction Snake::get_direction()
{
    return last_dir;
}

int Snake::get_score()
{
    return positions.size() - 2; //score is substracted by 2
}

void Snake::reset(const sf::Vector2f& pos)
{
    positions.clear();
    
    positions.push_back(pos);
    set_random_direction();
    move();
}

void Snake::set_random_direction()
{
    Direction new_dir;
    Direction old_dir = get_direction();

    //random generating random num 1 - 4 while it is same as old direction
    do {
        new_dir = static_cast<Direction>(std::rand() % 4);
    } while (new_dir == (old_dir + 2) % 4); //komplikovane napisany opacny smer

    current_dir = new_dir;
}

AI_Snake::AI_Snake(const sf::Vector2f& pos, const std::vector<int>& layers)
    : Snake(pos)
    , ai(layers)
{
    setTextures(sf::Color::Yellow);
}

Direction AI_Snake::set_direction_of_food(std::unique_ptr<AI_Snake>& position, sf::Vector2f food, Direction old) {//std::vector<sf::Vector2f> positions
	if (position->get_positions()[0].x < food.x) {
		if (old != Left) return Right;
        else if(position->get_positions()[0].y < food.y){
            position->set_direction(Down);
            position->move();
			if (position->legal_move()) return Down;
            else {
                position->set_direction(Up);
                position->move();
				if (position->legal_move()) return Up;

            }
        }
		else if (position->get_positions()[0].y > food.y) {
			position->set_direction(Up);
			position->move();
			if (position->legal_move()) return Up;
			else {
				position->set_direction(Down);
				position->move();
				if (position->legal_move()) return Down;
			}
		}
	}
    else if (position->get_positions()[0].x > food.x) {
		if (old != Right) return Left;
		else if (position->get_positions()[0].y < food.y) {
			position->set_direction(Down);
			position->move();
			if (position->legal_move()) return Down;
			else {
				position->set_direction(Up);
				position->move();
				if (position->legal_move()) return Up;

			}
		}
		else if (position->get_positions()[0].y > food.y) {
			position->set_direction(Up);
			position->move();
			if (position->legal_move()) return Up;
			else {
				position->set_direction(Down);
				position->move();
				if (position->legal_move()) return Down;
			}
		}
	}
    else if (position->get_positions()[0].y < food.y) {
        if (old != Up) return Down;
		else if (position->get_positions()[0].x < food.x) {
			position->set_direction(Right);
			position->move();
			if (position->legal_move()) return Right;
            else {
				position->set_direction(Left);
				position->move();
				if (position->legal_move()) return Left;

			}
		}
        else if (position->get_positions()[0].x > food.x) {
			position->set_direction(Left);
			position->move();
			if (position->legal_move()) return Left;
            else {
				position->set_direction(Right);
				position->move();
				if (position->legal_move()) return Right;
			}
		}
	}
    else if (position->get_positions()[0].y > food.y) {
        if (old != Down) return Up;
        else if (position->get_positions()[0].x < food.x) {
			position->set_direction(Right);
			position->move();
			if (position->legal_move()) return Right;
            else {
				position->set_direction(Left);
				position->move();
				if (position->legal_move()) return Left;
            }
        }
        else if (position->get_positions()[0].x > food.x) {
            position->set_direction(Left);
            position->move();
            if (position->legal_move()) return Left;
            else {
                position->set_direction(Right);
                position->move();
                if (position->legal_move()) return Right;
            }
        }
	}
	return old;
}

void AI_Snake::set_direction_from_ai(const std::vector<double>& output)
{
    Direction new_dir = static_cast<Direction>(std::distance(output.begin(), std::max_element(output.begin(), output.end())));

    Direction last_dir = get_direction();
    
	set_direction(static_cast<Direction>((static_cast<int>(new_dir) + static_cast<int>(last_dir) + 3) % 4)); //absolutny smer z relativneho
}