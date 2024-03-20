#include "SnakeGame.h"
//#include <Windows.h>
#include <ctime>

SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SnakeAI")
    , block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE))
    , gameOver(false)
    , isError(false)
    , restartGame(false)
    , changeX(0)
    , changeY(0)
    , fpsCounter(0)
    , now(std::chrono::high_resolution_clock::now())
{
    window.setSize(sf::Vector2u(WINDOW_SIZE, WINDOW_SIZE));
    window.setFramerateLimit(FPS_LIMIT);

    //load fonts
    if (!font_fps.loadFromFile("font.ttf")) {
        isError = true;
    }
    if (!font_papyrus.loadFromFile("papyrus.ttf")) {
        isError = true;
    }

    setTextures(); //food and snakes

    //generate head of snake
    snake.push_back(sf::Vector2f(PIXEL_SIZE / 2 * BLOCK_SIZE, PIXEL_SIZE / 2 * BLOCK_SIZE));
    food_pos = generateFood(); //generate first food

    srand(time(0));

    fpsText.setFont(font_fps);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(0, 0); //left up corner

}

SnakeGame::~SnakeGame() {
    //nic take
}

void SnakeGame::run() {
    gameOver = false;
    while (window.isOpen()) {
        handleInput();
        update();
        render();

        if (gameOver) retryMenu();
    }
}

void SnakeGame::retryMenu() {
    setRetryText();
    restartGame = false;

    while (window.isOpen() && !restartGame) {
        retryInput();
        render();
    }
}

void SnakeGame::handleInput() {
    sf::Event event;
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
}

void SnakeGame::retryInput() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        //check mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (retry.getGlobalBounds().contains(mousePos))
            {
                restartGame = true;
                //std::cout << "Restart" << std::endl;
                //button pressed
            }
        }
    }
}

void SnakeGame::drawGrid() {
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

void SnakeGame::drawSnake() {
    //dufam ze to funguje len som to skopiroval od mina XD

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
            if (snake[i + 1].x == snake[i - 1].x && snake[i + 1].y != snake[i - 1].y) {
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
}

void SnakeGame::drawFood() {
    food.setPosition(food_pos);
    window.draw(food);
}

sf::Vector2f SnakeGame::generateFood() {
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

bool SnakeGame::legalMove() {
    if (snake[0].x < 0 && snake[0].x >= WINDOW_SIZE && snake[0].y < 0 && snake[0].y >= WINDOW_SIZE) {
        return false;
    }
    
    for (int i = 1; i < snake.size(); i++) {
        if (snake[0] == snake[i]) {
            return false;
        }
    }

    return true;
}

void SnakeGame::moveSnake(const sf::Vector2f& nextPos) {
    //inserts new pos to snake depending on the direction it is moving
    snake.insert(snake.begin(), nextPos);

    //ak had zjdol ovocie tak sa vygeneruje nove (a zostane mu chvost)
    //inak mu zmizne chvost - takze sa len posunie
    if (food_pos == snake[0]) {
        food_pos = generateFood();
    }
    else {
        snake.pop_back(); 
    }
}

void SnakeGame::update() {
    fpsCounter++; //increase frame counter

    if (fpsCounter >= (FPS_LIMIT / SNAKE_SPEED)) {
        fpsCounter = 0;

        sf::Vector2f nextPos(snake[0].x + changeX, snake[0].y + changeY);
        moveSnake(nextPos);
        gameOver = !legalMove();


        //last move
        lastChangedX = changeX;
        lastChangedY = changeY;
    }

    lastTime = now;
    now = std::chrono::high_resolution_clock::now();
    fps = 1.f / std::chrono::duration_cast<std::chrono::duration<float>>(now - lastTime).count();
    
    fpsText.setString(std::to_string(fps));
}

void SnakeGame::render() {
    window.clear();

    drawGrid();
    drawSnake();
    drawFood();

    window.draw(fpsText);
    window.draw(endOfGame);
    window.draw(retry);
    window.draw(restart);

    window.display();
}

void SnakeGame::setTextures() {
    //load jablko texture
    if (!jablko.loadFromFile("jablcko.png")) {
        isError = true;
        food.setColor(sf::Color::Red);
    }
    else {
        food.setTexture(jablko); //set texture only if it loaded
    }

    if (!tail_left.loadFromFile("Snake_texture/tail_left.png")) {
        isError = true;
    }
    else {
        tailLeft.setTexture(tail_left);
    }

    sf::Texture tail_right; // ->
    if (!tail_right.loadFromFile("Snake_texture/tail_right.png")) {
        isError = true;
    }
    else {
        tailRight.setTexture(tail_right);
    }

    sf::Texture tail_down; // V
    if (!tail_down.loadFromFile("Snake_texture/tail_down.png")) {
        isError = true;
    }
    else {
        tailDown.setTexture(tail_down);
    }

    sf::Texture tail_up; // A
    if (!tail_up.loadFromFile("Snake_texture/tail_up.png")) {
        isError = true;
    }
    else {
        tailUp.setTexture(tail_up);
    }

    sf::Texture horizontal; // --
    if (!horizontal.loadFromFile("Snake_texture/body_horizontal.png")) {
        isError = true;
    }
    else {
        horiz.setTexture(horizontal);
    }

    sf::Texture vertical; // |
    if (!vertical.loadFromFile("Snake_texture/body_vertical.png")) {
        isError = true;
    }
    else {
        vertic.setTexture(vertical);
    }

    sf::Texture topright; // L
    if (!topright.loadFromFile("Snake_texture/body_topright.png")) {
        isError = true;
    }
    else {
        topRight.setTexture(topright);
    }

    sf::Texture topleft; // ⅃
    if (!topleft.loadFromFile("Snake_texture/body_topleft.png")) {
        isError = true;
    }
    else {
        topLeft.setTexture(topleft);
    }

    sf::Texture bottomleft; // ꓶ
    if (!bottomleft.loadFromFile("Snake_texture/body_bottomleft.png")) {
        isError = true;
    }
    else {
        bottomLeft.setTexture(bottomleft);
    }

    sf::Texture bottomright; // F
    if (!bottomright.loadFromFile("Snake_texture/body_bottomright.png")) {
        isError = true;
    }
    else {
        bottomRight.setTexture(bottomright);
    }

    sf::Texture head_left; // <- hlava
    if (!head_left.loadFromFile("Snake_texture/head_left.png")) {
        isError = true;
    }
    else {
        headLeft.setTexture(head_left);
    }

    sf::Texture head_right; // -> hlava
    if (!head_right.loadFromFile("Snake_texture/head_right.png")) {
        isError = true;
    }
    else {
        headRight.setTexture(head_right);
    }

    sf::Texture head_down; // V hlava
    if (!head_down.loadFromFile("Snake_texture/head_down.png")) {
        isError = true;
    }
    else {
        headDown.setTexture(head_down);
    }

    sf::Texture head_up; // A hlava
    if (!head_up.loadFromFile("Snake_texture/head_up.png")) {
        isError = true;
    }
    else {
        headUp.setTexture(head_up);
    }
}

void SnakeGame::setRetryText() {
    endOfGame.setFont(font_papyrus);
    endOfGame.setString("Game Over");
    endOfGame.setFillColor(sf::Color::Red);
    endOfGame.setStyle(sf::Text::Bold);
    endOfGame.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f);

    retry.setFillColor(sf::Color::White);
    retry.setSize(sf::Vector2f(100, 50));
    retry.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);

    restart.setFont(font_papyrus);
    restart.setString("Try Again");
    restart.setFillColor(sf::Color::Black);
    restart.setStyle(sf::Text::Bold);
    restart.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f - 70);
}