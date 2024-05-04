#pragma once

#include <SFML/Graphics.hpp>
#include "DrawObjects.hpp"

enum Direction {
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};

class Snake : public DrawObject {
public:
	Snake(const sf::Vector2f&);
    virtual void draw(sf::RenderWindow& window) override;

	std::vector<sf::Vector2f> get_positions();

	void setTextures(std::string);
	bool move();
	bool eats(const sf::Vector2f&);

	void reset(const sf::Vector2f&);

	Direction get_direction();

	int get_score();

	void set_direction(int, int);
	void set_old_direction();

	void set_random_direction();

private:
	std::vector<sf::Vector2f> positions;

	//had pojde smerom hore natvrdo sorry jako
	int changeX = 0, changeY = -BLOCK_SIZE, lastChangedX = 0, lastChangedY = 0; 

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