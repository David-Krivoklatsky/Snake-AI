#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int WINDOW_SIZE = 800;
int PIXEL_SIZE = 20;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");

    int block_size = WINDOW_SIZE / PIXEL_SIZE;
    sf::RectangleShape block(sf::Vector2f(block_size, block_size));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < PIXEL_SIZE; i++) {
            for (int j = 0; j < PIXEL_SIZE; j++) {
                block.setPosition(sf::Vector2f(block_size * j, block_size * i));
                block.setFillColor(((i + j) % 2) ? sf::Color::Cyan : sf::Color::Blue);
                window.draw(block);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        window.display();
    }

    return 0;
}