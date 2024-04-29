#include "Milan.hpp"

Milan::Milan() {
	petrovaFrajerka.setFillColor(sf::Color::Red);
	petrovaFrajerka.setSize(sf::Vector2f(100, 100));
	petrovaFrajerka.setPosition(sf::Vector2f(50, 50));
}

void Milan::draw(sf::RenderWindow& window) {
	window.draw(petrovaFrajerka);
}