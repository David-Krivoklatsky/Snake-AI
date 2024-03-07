#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int WINDOW_SIZE = 800; //width and height
int PIXEL_SIZE = 20; //size of the grid, number of rows and columns
int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE; //size of each grid pixel

void drawGrid(sf::RenderWindow& window, sf::RectangleShape& block) {
    for (int i = 0; i < PIXEL_SIZE; i++) {
        for (int j = 0; j < PIXEL_SIZE; j++) {
            block.setPosition(sf::Vector2f(BLOCK_SIZE * j, BLOCK_SIZE * i));

            sf::Color primary(60, 60, 60);
            sf::Color secondary(120, 120, 120);
            block.setFillColor(((i + j) % 2) ? primary : secondary);

            window.draw(block);
        }
    }
}

void drawSnake(sf::RenderWindow& window, sf::RectangleShape& block, const std::vector<sf::Vector2f>& snake) {
    block.setFillColor(sf::Color::Green);
    
    for (const sf::Vector2f pos : snake) {
        block.setPosition(pos);
        window.draw(block);
    }
}

sf::Vector2f generateFood(const std::vector<sf::Vector2f>& snake) {
    sf::Vector2f foodPos;

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

void drawFood(sf::RenderWindow& window, sf::RectangleShape& block, const sf::Vector2f& food)
{
    block.setFillColor(sf::Color::Red);

    block.setPosition(food);
    window.draw(block);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");
    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

    std::vector<sf::Vector2f> snake;
    snake.push_back(sf::Vector2f(rand() % PIXEL_SIZE * BLOCK_SIZE, rand() % PIXEL_SIZE * BLOCK_SIZE));

    sf::Vector2f nextPos(0, 0); //set next snake position
    int changeX = 0, changeY = 0;

    sf::Vector2f food = generateFood(snake);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Handle LEFT, RIGHT, UP, DOWN
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                changeX = -BLOCK_SIZE;
                changeY = 0;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                changeX = +BLOCK_SIZE;
                changeY = 0;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                changeX = 0;
                changeY = -BLOCK_SIZE;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                changeX = 0;
                changeY = BLOCK_SIZE;
            }

        }

        //move snake
        nextPos = sf::Vector2f(snake[0].x + changeX, snake[0].y + changeY);
        snake.insert(snake.begin(), nextPos);

        if (food != snake[0]) {
            snake.pop_back();
        }
        else {
            food = generateFood(snake);
        }

        window.clear();

        drawGrid(window, block);
        drawSnake(window, block, snake);
        drawFood(window, block, food);

        //sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        window.display();
    }

    return 0;
}