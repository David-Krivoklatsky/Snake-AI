#include "Food.hpp"
#include "Globals.hpp"

Food::Food(const sf::Vector2f& foodPos) {

    //set food textures
    if (!jablko.loadFromFile("jablcko.png")) {
        //isError = true;
        //Errors.push_back("Error loading jablcko.png");
        sprite.setColor(sf::Color::Red);
    }
    else {
        sprite.setTexture(jablko); //set texture only if it loaded
    }

	generateFood(foodPos);
}

void Food::generateFood(const sf::Vector2f& pos) {
    position = pos;
}

sf::Vector2f Food::get_position()
{
    return position;
}

void Food::draw(sf::RenderWindow& window)
{
    sprite.setPosition(position);
    window.draw(sprite);
}
