#pragma once

#include "Direction.hpp"
#include <SFML/Graphics.hpp>
#include "DrawObjects.hpp"
#include "SnakeSkin.hpp"
#include "NeuralNetwork.hpp"
#include "Food.hpp"

class Snake : public DrawObject {
public:
	Snake(const sf::Vector2f&);
    virtual void draw(sf::RenderWindow&) override;

	std::vector<sf::Vector2f> get_positions();

	void setSkin(const SnakeSkin&);

	void copyFrom(const Snake& other);

	void move();
	bool legal_move();
	bool eats(const sf::Vector2f&);

	void reset(const sf::Vector2f&);

	int get_score();

	Direction get_direction();
	Direction get_relative_direction();

	void set_direction(Direction);
	void set_random_direction();
	void set_old_direction();

private:
	std::vector<sf::Vector2f> positions;

	std::unique_ptr<SnakeSkin> skin;

	Direction current_dir;
	Direction last_dir;
};

class AI_Snake : public Snake {
public:
	AI_Snake(const sf::Vector2f&, const std::vector<int>& layers);

	NeuralNetwork ai;
	
	void set_direction_from_ai(const std::vector<double>&);
};

class Noob_Snake : public Snake {
public:
	Noob_Snake(const sf::Vector2f&);

	Direction set_direction_of_food(std::unique_ptr<Noob_Snake>&, std::unique_ptr<Noob_Snake>&, std::unique_ptr<Noob_Snake>&, sf::Vector2f, Direction);

};