#pragma once

#include <SFML/Graphics.hpp>
#include "DrawObjects.hpp"

enum Direction {
	Up = 0,
	Left = 1,
	Down = 2,
	Right = 3,

	Unknown = 4
};

class Snake : public DrawObject {
public:
	Snake(const sf::Vector2f&);
    virtual void draw(sf::RenderWindow&) override;

	std::vector<sf::Vector2f> get_positions();

	void setTextures(sf::Color);
	void setTextures(std::string);

	bool move();
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