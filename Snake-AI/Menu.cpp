#include "Menu.hpp"

Menu::Menu()
{
    if (!papyrus.loadFromFile("papyrus.ttf")) {
        //isError = true;
        //Errors.push_back("Error loading papyrus.ttf");
    }

    endOfGame.setFont(papyrus);
    endOfGame.setString("Game Over");
    endOfGame.setFillColor(sf::Color::Red);
    endOfGame.setStyle(sf::Text::Bold);
    endOfGame.setCharacterSize(70);
    endOfGame.setOrigin(endOfGame.getLocalBounds().width / 2, endOfGame.getLocalBounds().height / 2);
    endOfGame.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f - 100);

    retry.setFillColor(sf::Color::White);
    retry.setSize(sf::Vector2f(200, 50));
    retry.setOrigin(retry.getLocalBounds().width / 2, retry.getLocalBounds().height / 2);
    retry.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);

    restart.setFont(papyrus);
    restart.setString("Try Again");
    restart.setFillColor(sf::Color::Black);
    restart.setStyle(sf::Text::Bold);
    restart.setOrigin(restart.getLocalBounds().width / 2, restart.getLocalBounds().height / 2);
    restart.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(endOfGame);
    window.draw(retry);
    window.draw(restart);
}

bool Menu::click(const sf::RenderWindow& window)
{
    return retry.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
