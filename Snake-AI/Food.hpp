#pragma once

#include <SFML/Graphics.hpp>

#include "DrawObjects.hpp"

class Food : public DrawObject {
public:
	Food(const std::vector<sf::Vector2f>&);
	sf::Vector2f generateFood(const std::vector<sf::Vector2f>&);
	virtual void draw(sf::RenderWindow& window) override;
private:
	sf::Vector2f position;

	sf::Texture jablko;
	sf::Sprite food_sprite;
};