#include "Food.hpp"
#include "Globals.hpp"

Food::Food() {
	position = generateFood();

    //set food textures
    if (!jablko.loadFromFile("jablcko.png")) {
        isError = true;
        Errors.push_back("Error loading jablcko.png");
        food_sprite.setColor(sf::Color::Red);
    }
    else {
        food_sprite.setTexture(jablko); //set texture only if it loaded
    }
}

sf::Vector2f Food::generateFood() {
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

    return foodPos;
}

void Food::draw(sf::RenderWindow& window)
{
    food_sprite.setPosition(position);
    window.draw(food_sprite);
}
