#pragma once

#include <SFML/Graphics.hpp>

#include "DrawObjects.hpp"

class Food : public DrawObject {
public:
	Food();
	sf::Vector2f generateFood();
	virtual void draw(sf::RenderWindow& window) override;
private:
	sf::Vector2f position;

	sf::Texture jablko;
	sf::Sprite food_sprite;
};