#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int WINDOW_SIZE = 800;
int PIXEL_SIZE = 10;
int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");
    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

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
                block.setPosition(sf::Vector2f(BLOCK_SIZE * j, BLOCK_SIZE * i));

                sf::Color primary(60, 60, 60);
                sf::Color secondary(120, 120, 120);
                block.setFillColor(((i + j) % 2) ? primary : secondary);

                window.draw(block);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        window.display();
    }

    return 0;
}