#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int WINDOW_SIZE = 800; //width and height
int PIXEL_SIZE = 20; //size of the grid, number of rows and columns
int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE; //size of each grid pixel
bool waiting;

struct changePos {
    int X = 0;
    int Y = 0;
};
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
    //head of the snake has different color
    block.setFillColor(sf::Color::Yellow);
    block.setPosition(snake[0]);
    window.draw(block);
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

void posChange(changePos& change, sf::Event& event) {  // <<<<------ ---------------------------------

    //Handle LEFT, RIGHT, UP, DOWN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (change.X != BLOCK_SIZE))
    {
        change.X = -BLOCK_SIZE;
        change.Y = 0;
        return;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (change.X != -BLOCK_SIZE))
    {
        change.X = BLOCK_SIZE;
        change.Y = 0;
        return;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (change.Y != BLOCK_SIZE))
    {
        change.X = 0;
        change.Y = -BLOCK_SIZE;
        return;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (change.Y != -BLOCK_SIZE))
    {
        change.X = 0;
        change.Y = BLOCK_SIZE;
        return;
    }
}

void processEvents(sf::RenderWindow& window, bool& waiting, changePos& change) {
    sf::Event event;

    while (window.pollEvent(event) && waiting) {
        if (event.type == sf::Event::Closed)
            window.close();

        posChange(change, event); // Handle LEFT, RIGHT, UP, DOWN
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");
    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

    std::vector<sf::Vector2f> snake;
    snake.push_back(sf::Vector2f(rand() % PIXEL_SIZE * BLOCK_SIZE, rand() % PIXEL_SIZE * BLOCK_SIZE));

    sf::Vector2f nextPos(0, 0); //set next snake position
    changePos change; //koeficients of changing position to the left or right, up or down

    sf::Vector2f food = generateFood(snake);

    while (window.isOpen())
    {
        waiting = true;
        sf::Event event;

        std::thread handling(processEvents, window, waiting, change);
        //processEvents(window, waiting, change);

        //move snake
        nextPos = sf::Vector2f(snake[0].x + change.X, snake[0].y + change.Y);
        snake.insert(snake.begin(), nextPos);

        if (food == snake[0]) {
            food = generateFood(snake);
        }
        else {
            snake.pop_back();
        }

        window.clear();

        drawGrid(window, block);
        drawSnake(window, block, snake);
        drawFood(window, block, food);

        //sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        waiting = false;
        handling.join();

        window.display();
    }

    return 0;
}