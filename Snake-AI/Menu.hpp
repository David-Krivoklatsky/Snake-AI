#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"

#include <SFML/Graphics.hpp>

class Menu : public DrawObject{
public:
	Menu();

	virtual void draw(sf::RenderWindow&) override;

	bool click(const sf::RenderWindow&);

private:
	sf::Font papyrus;

	sf::Text endOfGame;
	sf::Text restart;
	sf::RectangleShape retry;
};