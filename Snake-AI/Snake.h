#pragma once

#include <SFML/Graphics.hpp>

class Snake {
public:
	void setTextures();
	void move(sf::Vector2f);

private:
	std::vector<sf::Vector2f> snake;

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