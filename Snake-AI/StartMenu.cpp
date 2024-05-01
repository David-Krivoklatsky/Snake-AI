#include "StartMenu.hpp"

StartMenu::StartMenu() {

	choiceOfGameMod_button.setFillColor(sf::Color::White);
	choiceOfGameMod_button.setSize(sf::Vector2f(200, 50));
	choiceOfGameMod_button.setOrigin(choiceOfGameMod_button.getLocalBounds().width / 2, choiceOfGameMod_button.getLocalBounds().height / 2);
	choiceOfGameMod_button.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);
}

void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(choiceOfGameMod_button);
}

bool StartMenu::click(const sf::RenderWindow& window)
{
	return choiceOfGameMod_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}