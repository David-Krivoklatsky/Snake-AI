#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SnakeAI");
    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        shape.setPosition(50 + rand() % 601, 50 + rand() % 601);
        window.draw(shape);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        window.display();
    }

    return 0;
}