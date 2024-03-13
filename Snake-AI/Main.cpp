#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int WINDOW_SIZE = 800; //width and height
int PIXEL_SIZE = 20; //size of the grid, number of rows and columns
int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE; //size of each grid pixel

int FPS_LIMIT = 60;
float SNAKE_SPEED = 10.f; // block / sekunda

bool gameOver = false;

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

void drawFood(sf::RenderWindow& window, sf::Image& Jablko, const sf::Vector2f& food)
{
    Jablko.setPixel(food.x, food.y);
    window.draw(Jablko);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");
    window.setFramerateLimit(FPS_LIMIT);
    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

    sf::Image Jablko;
    Jablko.loadFromFile("taninkine - jablko.png");

    sf::Sprite jablcko;
    jablcko.

    std::vector<sf::Vector2f> snake;
    snake.push_back(sf::Vector2f(PIXEL_SIZE / 2 * BLOCK_SIZE, PIXEL_SIZE / 2 * BLOCK_SIZE));

    sf::Vector2f nextPos(0, 0); //set next snake position
    int changeX = 0, changeY = 0; //koeficients of changing position to the left or right, up or down

    sf::Vector2f food = generateFood(snake);

    //time vars for fps count
    std::chrono::high_resolution_clock::time_point last_time, now = std::chrono::high_resolution_clock::now();;
    float fps;

    int fps_counter = 0;

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text fps_text("FPS", font);
    fps_text.setFillColor(sf::Color::White);
    fps_text.setPosition(0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        //handle input
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Handle LEFT, RIGHT, UP, DOWN
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (changeX != BLOCK_SIZE))
            {
                changeX = -BLOCK_SIZE;
                changeY = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (changeX != -BLOCK_SIZE))
            {
                changeX = BLOCK_SIZE;
                changeY = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (changeY != BLOCK_SIZE))
            {
                changeX = 0;
                changeY = -BLOCK_SIZE;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (changeY != -BLOCK_SIZE))
            {
                changeX = 0;
                changeY = BLOCK_SIZE;
            }

        }

        //speed of snake adjusted by moving once a few frames
        fps_counter++;
        std::cout << fps_counter << std::endl;
        if (fps_counter >= (FPS_LIMIT / SNAKE_SPEED)) {
            fps_counter = 0;

            //move snake
            nextPos = sf::Vector2f(snake[0].x + changeX, snake[0].y + changeY);
            if (nextPos.x >= 0 && nextPos.x < WINDOW_SIZE && nextPos.y >= 0 && nextPos.y < WINDOW_SIZE) {

                snake.insert(snake.begin(), nextPos);

                if (food == snake[0]) {
                    food = generateFood(snake);
                }
                else {
                    snake.pop_back();
                }
            }
            else {
                gameOver = true;
            }
        }

        if (gameOver) {

        }

        //fps count
        last_time = now;
        now = std::chrono::high_resolution_clock::now();
        fps = 1.0f / std::chrono::duration_cast<std::chrono::duration<float>>(now - last_time).count();


        fps_text.setString(std::to_string(fps));

        window.clear();

        drawGrid(window, block);
        drawSnake(window, block, snake);
        drawFood(window, Jablko, food);
        window.draw(fps_text);

        //sleep
        //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        window.display();
    }

    return 0;
}
//verzia zakazane otacanie