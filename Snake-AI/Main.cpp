#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <cmath>
#include <ctime>


int WINDOW_SIZE = 800; //width and height
int PIXEL_SIZE = 20; //size of the grid, number of rows and columns
int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE; //size of each grid pixel

int FPS_LIMIT = 60;
float SNAKE_SPEED = 7.f; // block / sekunda

bool gameOver = false;

HWND button; //this button dude

//draw the whole playground for snake, chess pattern
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

//draw snake to window, using block
void drawSnake(sf::RenderWindow& window, sf::RectangleShape& block, const std::vector<sf::Vector2f>& snake, int& changeX, int& changeY, sf::Sprite& tailLeft, sf::Sprite& tailRight, sf::Sprite& tailUp, sf::Sprite& tailDown, sf::Sprite& horiz, sf::Sprite& vertic, sf::Sprite& topRight, sf::Sprite& topLeft, sf::Sprite& bottomLeft, sf::Sprite& bottomRight, sf::Sprite& headDown, sf::Sprite& headUp, sf::Sprite& headRight, sf::Sprite& headLeft) {
    /*block.setFillColor(sf::Color::Green);
    
    for (const sf::Vector2f pos : snake) {
        block.setPosition(pos);
        window.draw(block);
    }
    */

    if (changeX == -BLOCK_SIZE) { //head
        headLeft.setPosition(snake[0]);
        window.draw(headLeft);
    }
    else if (changeX == BLOCK_SIZE) {
        headRight.setPosition(snake[0]);
        window.draw(headRight);
    }
    else if (changeY == -BLOCK_SIZE) {
        headUp.setPosition(snake[0]);
        window.draw(headUp);
    }
    else if (changeY == BLOCK_SIZE) {
        headDown.setPosition(snake[0]);
        window.draw(headDown);
    }

    if (snake.size() > 1) { //tail
        if (snake[snake.size() - 2].x == snake[snake.size() - 1].x && snake[snake.size() - 2].y > snake[snake.size() - 1].y) { 
            tailUp.setPosition(snake[snake.size() - 1]);
            window.draw(tailUp);
        }
        else if (snake[snake.size() - 2].x == snake[snake.size() - 1].x && snake[snake.size() - 2].y < snake[snake.size() - 1].y) {
            tailDown.setPosition(snake[snake.size() - 1]);
            window.draw(tailDown);
        }
        else if (snake[snake.size() - 2].x < snake[snake.size() - 1].x && snake[snake.size() - 2].y == snake[snake.size() - 1].y) {
            tailRight.setPosition(snake[snake.size() - 1]);
            window.draw(tailRight);
        }
        else if (snake[snake.size() - 2].x > snake[snake.size() - 1].x && snake[snake.size() - 2].y == snake[snake.size() - 1].y) {
            tailLeft.setPosition(snake[snake.size() - 1]);
            window.draw(tailLeft);
        }
    }

    if (snake.size() > 2) { // if snakes length is bigger then 2 it has middle snake part (chest or smth like that) (everything except tail and head)
        for (int i = 1; i < snake.size() - 1; i++) {
            if (snake[i + 1].x == snake[i - 1].x && snake[i + 1].y != snake[i - 1].y ) {  
                vertic.setPosition(snake[i]);
                window.draw(vertic);
            }
            else if (snake[i + 1].x != snake[i - 1].x && snake[i + 1].y == snake[i - 1].y) {  
                horiz.setPosition(snake[i]);
                window.draw(horiz);
            }
            else if ((snake[i - 1].x > snake[i].x && snake[i + 1].y > snake[i].y) || (snake[i + 1].x > snake[i].x && snake[i - 1].y > snake[i].y)) {
                bottomRight.setPosition(snake[i]);
                window.draw(bottomRight);
            }
            else if ((snake[i - 1].x < snake[i].x && snake[i + 1].y < snake[i].y) || (snake[i + 1].x < snake[i].x && snake[i - 1].y < snake[i].y)) {
                topLeft.setPosition(snake[i]);
                window.draw(topLeft);
            }
            else if ((snake[i - 1].x < snake[i].x && snake[i + 1].y > snake[i].y) || (snake[i + 1].x < snake[i].x && snake[i - 1].y > snake[i].y)) {
                bottomLeft.setPosition(snake[i]);
                window.draw(bottomLeft);
            }
            else if ((snake[i - 1].x > snake[i].x && snake[i + 1].y < snake[i].y) || (snake[i + 1].x > snake[i].x && snake[i - 1].y < snake[i].y)) {
                topRight.setPosition(snake[i]);
                window.draw(topRight);
            }
        }
    }
    //head of the snake has different color
   /* block.setFillColor(sf::Color::Yellow);
    block.setPosition(snake[0]);*/
    /*window.draw(block);*/
}

//creates food on free block, this func is only called when there is no food
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

//draw food
void drawFood(sf::RenderWindow& window, sf::Sprite& food, const sf::Vector2f& food_pos)
{
    food.setPosition(food_pos);
    window.draw(food);
}

void snakeTexture() {
    sf::Texture tail_left; // <-
    if (!tail_left.loadFromFile("Snake_texture/tail_left.png")) {
        return;
    }
    sf::Sprite tailLeft(tail_left);

    sf::Texture tail_right; // ->
    if (!tail_right.loadFromFile("Snake_texture/tail_right.png")) {
        return;
    }
    sf::Sprite tailRight(tail_right);

    sf::Texture tail_down; // V
    if (!tail_down.loadFromFile("Snake_texture/tail_down.png")) {
        return;
    }
    sf::Sprite tailDown(tail_down);

    sf::Texture tail_up; // A
    if (!tail_up.loadFromFile("Snake_texture/tail_up.png")) {
        return;
    }
    sf::Sprite tailUp(tail_up);

    sf::Texture horizontal; // --
    if (!horizontal.loadFromFile("Snake_texture/horizontal.png")) {
        return;
    }
    sf::Sprite horiz(horizontal);

    sf::Texture vertical; // |
    if (!vertical.loadFromFile("Snake_texture/body_vertical.png")) {
        return;
    }
    sf::Sprite vertic(vertical);

    sf::Texture topright; // L
    if (!topright.loadFromFile("Snake_texture/body_topright.png")) {
        return;
    }
    sf::Sprite topRight(topright);

    sf::Texture topleft; // ⅃
    if (!topleft.loadFromFile("Snake_texture/body_topleft.png")) {
        return;
    }
    sf::Sprite topLeft(topleft);

    sf::Texture bottomleft; // ꓶ
    if (!bottomleft.loadFromFile("Snake_texture/body_bottomleft.png")) {
        return;
    }
    sf::Sprite bottomLeft(bottomleft);

    sf::Texture bottomright; // F
    if (!bottomright.loadFromFile("Snake_texture/body_bottomright.png")) {
        return;
    }
    sf::Sprite bottomRight(bottomright);

    sf::Texture head_left; // <- hlava
    if (!head_left.loadFromFile("Snake_texture/head_left.png")) {
        return;
    }
    sf::Sprite headLeft(head_left);

    sf::Texture head_right; // -> hlava
    if (!head_right.loadFromFile("Snake_texture/head_right.png")) {
        return;
    }
    sf::Sprite headRight(head_right);

    sf::Texture head_down; // V hlava
    if (!head_down.loadFromFile("Snake_texture/head_down.png")) {
        return;
    }
    sf::Sprite headDown(head_down);

    sf::Texture head_up; // A hlava
    if (!head_up.loadFromFile("Snake_texture/head_up.png")) {
        return;
    }
    sf::Sprite headUp(head_up);

}

int main()
{
    while (!gameOver) {
        srand(time(0)); //nahodne cisla podla casu

        sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI");
        window.setFramerateLimit(FPS_LIMIT);

        sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)); //used to display anything

        sf::Text endOfGame;
        sf::Text restart;
        sf::RectangleShape retry;
        bool restartTheGame = false;

        sf::Texture jablko; //image of an apple
        if (!jablko.loadFromFile("jablcko.png")) {
            return EXIT_FAILURE;
        }


        sf::Texture tail_left; // <-
        if (!tail_left.loadFromFile("Snake_texture/tail_left.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite tailLeft(tail_left);

        sf::Texture tail_right; // ->
        if (!tail_right.loadFromFile("Snake_texture/tail_right.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite tailRight(tail_right);

        sf::Texture tail_down; // V
        if (!tail_down.loadFromFile("Snake_texture/tail_down.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite tailDown(tail_down);

        sf::Texture tail_up; // A
        if (!tail_up.loadFromFile("Snake_texture/tail_up.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite tailUp(tail_up);

        sf::Texture horizontal; // --
        if (!horizontal.loadFromFile("Snake_texture/body_horizontal.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite horiz(horizontal);

        sf::Texture vertical; // |
        if (!vertical.loadFromFile("Snake_texture/body_vertical.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite vertic(vertical);

        sf::Texture topright; // L
        if (!topright.loadFromFile("Snake_texture/body_topright.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite topRight(topright);

        sf::Texture topleft; // ⅃
        if (!topleft.loadFromFile("Snake_texture/body_topleft.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite topLeft(topleft);

        sf::Texture bottomleft; // ꓶ
        if (!bottomleft.loadFromFile("Snake_texture/body_bottomleft.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite bottomLeft(bottomleft);

        sf::Texture bottomright; // F
        if (!bottomright.loadFromFile("Snake_texture/body_bottomright.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite bottomRight(bottomright);

        sf::Texture head_left; // <- hlava
        if (!head_left.loadFromFile("Snake_texture/head_left.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite headLeft(head_left);

        sf::Texture head_right; // -> hlava
        if (!head_right.loadFromFile("Snake_texture/head_right.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite headRight(head_right);

        sf::Texture head_down; // V hlava
        if (!head_down.loadFromFile("Snake_texture/head_down.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite headDown(head_down);

        sf::Texture head_up; // A hlava
        if (!head_up.loadFromFile("Snake_texture/head_up.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite headUp(head_up);

        //snakeTexture();  << nefunguje

        sf::Sprite food(jablko); //sprite with texture of an apple

        std::vector<sf::Vector2f> snake;
        snake.push_back(sf::Vector2f(PIXEL_SIZE / 2 * BLOCK_SIZE, PIXEL_SIZE / 2 * BLOCK_SIZE));

        sf::Vector2f nextPos; //set next snake position
        int changeX = 0, changeY = 0; //koeficients of changing position to the left or right, up or down
        int lastChangedX = 0, lastChangedY = 0;

        sf::Vector2f food_pos = generateFood(snake);

        //time vars for fps count
        std::chrono::high_resolution_clock::time_point last_time, now = std::chrono::high_resolution_clock::now();;
        float fps;

        int fps_counter = 0; //used to move snake only once a while

        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            return EXIT_FAILURE;
        }

        /*sf::Font papyrus; //I wanted to add another font for "Game Over" text but it applied also for FPS :(
        if (!font.loadFromFile("papyrus.ttf")) {
            return EXIT_FAILURE;
        }*/

        sf::Text fps_text("FPS", font);
        fps_text.setFillColor(sf::Color::White);
        fps_text.setPosition(0, 0); //left up corner

        while (window.isOpen())
        {
            
            sf::Event event;

            //handle input
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) //zavretie okna
                    window.close();

                //Handle LEFT, RIGHT, UP, DOWN
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (lastChangedX != BLOCK_SIZE))
                {
                    changeX = -BLOCK_SIZE;
                    changeY = 0;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (lastChangedX != -BLOCK_SIZE))
                {
                    changeX = BLOCK_SIZE;
                    changeY = 0;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (lastChangedY != BLOCK_SIZE))
                {
                    changeX = 0;
                    changeY = -BLOCK_SIZE;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (lastChangedY != -BLOCK_SIZE))
                {
                    changeX = 0;
                    changeY = BLOCK_SIZE;
                }

            }

            //speed of snake adjusted by moving once a few frames
            fps_counter++;
            if (fps_counter >= (FPS_LIMIT / SNAKE_SPEED)) {

                fps_counter = 0;

                //move snake
                nextPos = sf::Vector2f(snake[0].x + changeX, snake[0].y + changeY);
                if (nextPos.x >= 0 && nextPos.x < WINDOW_SIZE && nextPos.y >= 0 && nextPos.y < WINDOW_SIZE) {

                    snake.insert(snake.begin(), nextPos);

                    if (food_pos == snake[0]) {
                        food_pos = generateFood(snake);
                    }
                    else {
                        snake.pop_back();
                    }
                }
                else {
                    gameOver = true;
                }

                //last move
                lastChangedX = changeX;
                lastChangedY = changeY;
            }

            //if snakes head is crossing with himself then game over
            for (int i = 1; i < snake.size(); i++) {
                if (snake[0] == snake[i]) {
                    gameOver = true;
                }
            }

            if (gameOver) {
                while (window.isOpen()) {

                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed) //zavretie okna
                            window.close();
                    }

                    endOfGame.setFont(font);
                    endOfGame.setString("Game Over");
                    endOfGame.setCharacterSize(80);
                    endOfGame.setFillColor(sf::Color::Red);
                    endOfGame.setStyle(sf::Text::Bold);

                    // real size of text px
                    sf::FloatRect textRect = endOfGame.getLocalBounds();
                    //centred text (not in fullscreen)
                    endOfGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    endOfGame.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


                    sf::Color jj(255, 255, 255);
                    retry.setFillColor(jj);
                    retry.setSize(sf::Vector2f(100, 50));

                    retry.setOrigin(retry.getSize().x / 2.0f, retry.getSize().y / 2.0f);
                    retry.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f + 70);

                    restart.setFont(font);
                    restart.setCharacterSize(20);
                    restart.setString("Retry");
                    restart.setFillColor(sf::Color::Black);
                    restart.setStyle(sf::Text::Bold);

                    // real size of text px
                    sf::FloatRect textRect2 = restart.getLocalBounds();
                    //centred text (not in fullscreen)
                    restart.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
                    restart.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f + 70);

                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (retry.getGlobalBounds().contains(mousePos))
                        {
                            restartTheGame = true;
                            break;
                        }
                    }

                    last_time = now;
                    now = std::chrono::high_resolution_clock::now();
                    fps = 1.0f / std::chrono::duration_cast<std::chrono::duration<float>>(now - last_time).count();


                    fps_text.setString(std::to_string(fps));

                    window.clear();

                    drawGrid(window, block);
                    drawSnake(window, block, snake, lastChangedX, lastChangedY, tailLeft, tailRight, tailUp, tailDown, horiz, vertic, topRight, topLeft, bottomLeft, bottomRight, headDown, headUp, headRight, headLeft);
                    drawFood(window, food, food_pos);
                    window.draw(fps_text);
                    window.draw(endOfGame);
                    window.draw(retry);
                    window.draw(restart);

                    window.display();

                }

                //button = CreateWindow(TEXT("BUTTON"), TEXT("Quit"), WS_CHILD | WS_VISIBLE, 560, 440, 80, 40, window, NULL, NULL, NULL);
            }

            //fps count
            last_time = now;
            now = std::chrono::high_resolution_clock::now();
            fps = 1.0f / std::chrono::duration_cast<std::chrono::duration<float>>(now - last_time).count();

            if (restartTheGame) {
                break;
            }

            fps_text.setString(std::to_string(fps));

            window.clear();

            drawGrid(window, block);
            drawSnake(window, block, snake, lastChangedX, lastChangedY, tailLeft, tailRight, tailUp, tailDown, horiz, vertic, topRight, topLeft, bottomLeft, bottomRight, headDown, headUp, headRight, headLeft);
            drawFood(window, food, food_pos);
            window.draw(fps_text);
            window.draw(endOfGame);
            window.draw(retry);
            window.draw(restart);
            //sleep
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));

            window.display();
        }
        if (restartTheGame) {
            gameOver = false;
            continue;
        }
    }
    return 0;
}
//verzia zakazane otacanie