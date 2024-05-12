#pragma once

#include <SFML/Graphics.hpp>
#include "DrawObjects.hpp"
#include "NeuralNetwork.hpp"
#include "Food.hpp"

class Snake : public DrawObject {
public:
	Snake(const sf::Vector2f&);
    virtual void draw(sf::RenderWindow&) override;

	std::vector<sf::Vector2f> get_positions();

	void setTextures(sf::Color);
	void setTextures(std::string);

	void move();
	bool legal_move();
	bool eats(const sf::Vector2f&);

	void reset(const sf::Vector2f&);

	int get_score();

	Direction get_direction();
	void set_direction(Direction);
	void set_old_direction();
	void set_random_direction();

private:
	std::vector<sf::Vector2f> positions;

	Direction current_dir;
	Direction last_dir;

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

class AI_Snake : public Snake {
public:
	AI_Snake(const sf::Vector2f&, const std::vector<int>& layers);

	void set_direction_from_ai(const std::vector<double>&);
	Direction set_direction_of_food(std::unique_ptr<AI_Snake>, sf::Vector2f, Direction);

	NeuralNetwork ai;
};