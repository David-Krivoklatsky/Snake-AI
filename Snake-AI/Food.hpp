#pragma once

#include <SFML/Graphics.hpp>

#include "DrawObjects.hpp"

class Food : public DrawObject {
public:
	Food(const sf::Vector2f& foodPos);
	virtual void draw(sf::RenderWindow& window) override;

	void generateFood(const sf::Vector2f&);
	sf::Vector2f get_position();

private:
	sf::Vector2f position;

	sf::Texture jablko;
	sf::Sprite sprite;
};