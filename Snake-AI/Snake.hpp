#pragma once

#include <SFML/Graphics.hpp>

#include "DrawObjects.hpp"

class Snake : public DrawObject {
	Snake(const sf::Vector2f&);
public:
	void setTextures();
	void move();

    virtual void draw(sf::RenderWindow& window) override;

	std::vector<sf::Vector2f> get_positions();

private:
	std::vector<sf::Vector2f> positions;

public:
	int changeX = 0, changeY = 0, lastChangedX = 0, lastChangedY = 0;

private:
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