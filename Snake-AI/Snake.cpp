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

// snake2 = snake1
Snake& Snake::operator=(const Snake& other) {
    if (this != &other) {
        positions = other.positions;

        if (other.skin) {
            skin = std::make_unique<SnakeSkin>(*other.skin);
        }
        else {
            skin.reset();
        }

        current_dir = other.current_dir;
        last_dir = other.last_dir;
    }
    return *this;
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

void Snake::setSkin(const SnakeSkin& sskin) {

    skin = std::make_unique<SnakeSkin>(sskin);
}

void Snake::draw(sf::RenderWindow& window) {
    if (last_dir == Left) { //head
        skin->headLeft.setPosition(positions[0]);
        window.draw(skin->headLeft);
    }
    else if (last_dir == Right) {
        skin->headRight.setPosition(positions[0]);
        window.draw(skin->headRight);
    }
    else if (last_dir == Up) {
        skin->headUp.setPosition(positions[0]);
        window.draw(skin->headUp);
    }
    else if (last_dir == Down) {
        skin->headDown.setPosition(positions[0]);
        window.draw(skin->headDown);
    }

    if (positions.size() > 1) { //tail
        if (positions[positions.size() - 2].x == positions[positions.size() - 1].x && positions[positions.size() - 2].y > positions[positions.size() - 1].y) {
            skin->tailUp.setPosition(positions[positions.size() - 1]);
            window.draw(skin->tailUp);
        }
        else if (positions[positions.size() - 2].x == positions[positions.size() - 1].x && positions[positions.size() - 2].y < positions[positions.size() - 1].y) {
            skin->tailDown.setPosition(positions[positions.size() - 1]);
            window.draw(skin->tailDown);
        }
        else if (positions[positions.size() - 2].x < positions[positions.size() - 1].x && positions[positions.size() - 2].y == positions[positions.size() - 1].y) {
            skin->tailRight.setPosition(positions[positions.size() - 1]);
            window.draw(skin->tailRight);
        }
        else if (positions[positions.size() - 2].x > positions[positions.size() - 1].x && positions[positions.size() - 2].y == positions[positions.size() - 1].y) {
            skin->tailLeft.setPosition(positions[positions.size() - 1]);
            window.draw(skin->tailLeft);
        }
    }

    if (positions.size() > 2) { // if snakes length is bigger then 2 it has middle snake part (chest or smth like that) (everything except tail and head)
        for (int i = 1; i < positions.size() - 1; i++) {
            if (positions[i + 1].x == positions[i - 1].x && positions[i + 1].y != positions[i - 1].y) {
                skin->vertic.setPosition(positions[i]);
                window.draw(skin->vertic);
            }
            else if (positions[i + 1].x != positions[i - 1].x && positions[i + 1].y == positions[i - 1].y) {
                skin->horiz.setPosition(positions[i]);
                window.draw(skin->horiz);
            }
            else if ((positions[i - 1].x > positions[i].x && positions[i + 1].y > positions[i].y) || (positions[i + 1].x > positions[i].x && positions[i - 1].y > positions[i].y)) {
                skin->bottomRight.setPosition(positions[i]);
                window.draw(skin->bottomRight);
            }
            else if ((positions[i - 1].x < positions[i].x && positions[i + 1].y < positions[i].y) || (positions[i + 1].x < positions[i].x && positions[i - 1].y < positions[i].y)) {
                skin->topLeft.setPosition(positions[i]);
                window.draw(skin->topLeft);
            }
            else if ((positions[i - 1].x < positions[i].x && positions[i + 1].y > positions[i].y) || (positions[i + 1].x < positions[i].x && positions[i - 1].y > positions[i].y)) {
                skin->bottomLeft.setPosition(positions[i]);
                window.draw(skin->bottomLeft);
            }
            else if ((positions[i - 1].x > positions[i].x && positions[i + 1].y < positions[i].y) || (positions[i + 1].x > positions[i].x && positions[i - 1].y < positions[i].y)) {
                skin->topRight.setPosition(positions[i]);
                window.draw(skin->topRight);
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

}

Noob_Snake::Noob_Snake(const sf::Vector2f& pos)
    : Snake(pos)
{

}

Direction Noob_Snake::set_direction_of_food(std::unique_ptr<Noob_Snake>& position, std::unique_ptr<Noob_Snake>& position1, std::unique_ptr<Noob_Snake>& position2, sf::Vector2f food, Direction old) {//std::vector<sf::Vector2f> positions

    if (position->get_positions()[0].x < food.x) {
		position2->set_direction(Right);
		position2->move();
		if (position2->legal_move()) return Right;
        else if(position->get_positions()[0].y < food.y){
            position->set_direction(Down);
			position->move();
            position1->set_direction(Up);
            position1->move();
            if (position->legal_move()) return Down;
            else if (position1->legal_move()) return Up;
            else return Left;
        }
		else{
			position->set_direction(Up);
			position->move();
			position1->set_direction(Down);
			position1->move();
            if (position->legal_move()) return Up;
            else if (position1->legal_move()) return Down;
            else return Left;
		}
	}
    else if (position->get_positions()[0].x > food.x) {
        position2->set_direction(Left);
        position2->move();
		if (position2->legal_move()) return Left;
		else if (position->get_positions()[0].y < food.y) {
			position->set_direction(Down);
			position->move();
			position1->set_direction(Up);
			position1->move();
			if (position->legal_move()) return Down;
			else if(position1->legal_move()) return Up;
			else return Right;

		}
		else {
			position->set_direction(Up);
			position->move();
			position1->set_direction(Down);
			position1->move();
			if (position->legal_move()) return Up;
			else if(position1->legal_move()) return Down;
			else return Right;
			
		}
	}
    else if (position->get_positions()[0].y < food.y) {
        position2->set_direction(Down);
        position2->move();
        if (position2->legal_move()) return Down;
		else if (position->get_positions()[0].x < food.x) {
			position->set_direction(Right);
			position->move();
			position1->set_direction(Left);
			position1->move();
			if (position->legal_move()) return Right;
            else if(position1->legal_move()) return Left;
			else return Up;
		}
        else{
			position->set_direction(Left);
			position->move();
			position1->set_direction(Right);
			position1->move();
			if (position->legal_move()) return Left;
            else if(position1->legal_move())return Right;
			else return Up;
		}
	}
    else if (position->get_positions()[0].y > food.y) {
        position2->set_direction(Up);
        position2->move();
        if (position2->legal_move()) return Up;
        else if (position->get_positions()[0].x < food.x) {
			position->set_direction(Right);
			position->move();
			position1->set_direction(Left);
			position1->move();
			if (position->legal_move()) return Right;
            else if (position1->legal_move()) return Left;
			else return Down;
        }
        else{
            position->set_direction(Left);
            position->move();
			position1->set_direction(Right);
			position1->move();
            if (position->legal_move()) return Left;
            else if(position1->legal_move()) return Right;
			else return Down;
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