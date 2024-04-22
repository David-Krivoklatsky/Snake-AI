#include "Food.hpp"
#include "Globals.hpp"

Food::Food(const std::vector<sf::Vector2f>& snake) {
	generateFood(snake);

    //set food textures
    if (!jablko.loadFromFile("jablcko.png")) {
        //isError = true;
        //Errors.push_back("Error loading jablcko.png");
        food_sprite.setColor(sf::Color::Red);
    }
    else {
        food_sprite.setTexture(jablko); //set texture only if it loaded
    }
}

void Food::generateFood(const std::vector<sf::Vector2f>& snake) {
    sf::Vector2f foodPos;

    //find valid position
    bool invalidPos;
    do {
        invalidPos = false;

        foodPos.x = rand() % PIXEL_SIZE * BLOCK_SIZE;
        foodPos.y = rand() % PIXEL_SIZE * BLOCK_SIZE;

        for (const sf::Vector2f s : snake) {
            if (foodPos == s) {
                invalidPos = true;
                break;
            }
        }
    } while (invalidPos);

    position = foodPos;
}

sf::Vector2f Food::get_position()
{
    return position;
}

void Food::draw(sf::RenderWindow& window)
{
    food_sprite.setPosition(position);
    window.draw(food_sprite);
}
