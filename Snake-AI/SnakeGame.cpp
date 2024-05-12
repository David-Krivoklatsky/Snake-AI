#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "StartMenu.hpp"
#include "NeuralNetwork.hpp"

SnakeGame::SnakeGame()
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake AI")
    , event()
    , snake(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2))
    , food(find_empty_cell())
    , menu()
    , startMenu()
{
    window.setFramerateLimit(FPS_LIMIT);
    srand(time(0));

    snake.setTextures(sf::Color::Blue); //set texture default blue, if you click to change skin it is handled lower
      
    startMenu.assignFilenames(textureFiles, startMenu.numberOfSkins);


    general_font.loadFromFile("font.ttf");

    scoreText.setFont(general_font);
    scoreText.setFillColor(sf::Color::White);

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));

    std::vector<int> layers = { PIXEL_SIZE * PIXEL_SIZE, PIXEL_SIZE, 3 };

    //vytvorenie hadakov umelych
    for (int i = 0; i < 2; i++) {
        ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), layers));
    }
}

void SnakeGame::run() {
    gameOver = false;

    while (window.isOpen() && start_menu) {
        startInput();

        window.clear();
        startMenu.draw(window);
        window.display();
    }

    while (window.isOpen()) {

        while (pause) {
            handleInput();
        }

        handleInput();

        if (isGameFrame()) {

            switch (startMenu.mode)
            {
            case 0: classicMode();
                break;

            case 1: randomMode();
				break;

            case 2: peacefulMode();
                break;

            case 3: aiMode();
                break;

            case 4: trainAiMode();
				break;

            case 5: aiNoobMode();
                break;

            default:
                break;
            }
        }

        //update();
        render();

        if (gameOver) retryMenu();
        gameOver = false;
    }
}

void SnakeGame::retryMenu() {
    restartGame = false;

    snake.reset(sf::Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE / 2));

	scoreText.setPosition(WINDOW_SIZE / 2 - (scoreText.getGlobalBounds().width), WINDOW_SIZE / 2 - 20);
	scoreText.setCharacterSize(50);

    while (window.isOpen() && !restartGame) {

        retryInput();
        window.clear();
        menu.draw(window);
        window.draw(scoreText);
        window.display();
    }
    scoreText.setCharacterSize(30);
}

void SnakeGame::startInput()
{
    bool pressed = true;

    while (window.pollEvent(event)) {
        switch (event.type){

            case sf::Event::Closed: {
                window.close();

                break;
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Space) {
                    start_menu = false;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            pressed = true;
			if (startMenu.clickSkin(window)) {
                startMenu.button = 1;
                startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickStart(window)) {
                startMenu.button = 2;
                startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickMode(window)) {
                startMenu.button = 3;
                startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickSound(window)) {
				startMenu.turnSound();
			}
            

        }
            if (!startMenu.clickSkin(window) && startMenu.button == 1) {
                startMenu.setUnpressed(startMenu.button);
            }
			if (!startMenu.clickStart(window) && startMenu.button == 2) {
				startMenu.setUnpressed(startMenu.button);
			}
            if (!startMenu.clickMode(window) && startMenu.button == 3) {
				startMenu.setUnpressed(startMenu.button);
            }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && pressed)
        {
            if (startMenu.clickSkin(window)) {
                startMenu.button = 1;
                startMenu.setUnpressed(startMenu.button);
                startMenu.anotherSkin(skinChose, startMenu.numberOfSkins);
                pressed = false;
                snake.setTextures(textureFiles[skinChose]); //set textures here because it was lagging
            }

            else if (startMenu.clickStart(window)) {
                startMenu.button = 2;
				startMenu.setUnpressed(startMenu.button);
                start_menu = false;
                pressed = false;
                break;
            }

            else if (startMenu.clickMode(window)) {
                pressed = false;
                startMenu.button = 3;
                startMenu.setUnpressed(startMenu.button);
				startMenu.changeMod();
            }

        }
    }
}

void SnakeGame::handleInput() {
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                window.close();

                break;
            }

            case sf::Event::KeyPressed:
            {
                Direction last_dir = snake.get_direction();

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Left && last_dir != Right)
                {
                    snake.set_direction(Left);
                }
                else if (event.key.code == sf::Keyboard::Right && last_dir != Left)
                {
                    snake.set_direction(Right);
                }
                else if (event.key.code == sf::Keyboard::Up && last_dir != Down)
                {
                    snake.set_direction(Up);
                }
                else if (event.key.code == sf::Keyboard::Down && last_dir != Up)
                {
                    snake.set_direction(Down);
                }

				if (event.key.code == sf::Keyboard::P) {
					pause = !pause;
				}

                if (event.key.code == sf::Keyboard::M) {
                    startMenu.turnSound();
                }
            }

        default:
            break;
        }
    }
}

void SnakeGame::retryInput() {
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        //check mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (menu.click(window))
            {
                restartGame = true;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            restartGame = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }
}

void SnakeGame::update() {
    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

void SnakeGame::render() {
    window.clear();

    for (auto& object : draw_objects)
        object->draw(window);

    for (auto& ai_snake : ai_snakes) {
        ai_snake->draw(window);
    }

    snake.draw(window);
    food.draw(window);

    window.draw(scoreText);

    window.display();
}

bool SnakeGame::isGameFrame()
{
    fpsCounter++; //increase frame counter

    if (fpsCounter >= (FPS_LIMIT / SNAKE_SPEED)) {
        fpsCounter = 0;
        return true;
    }

    return false;
}

void SnakeGame::classicMode()
{
    snake.move();
    gameOver = !snake.legal_move();
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    snake.set_old_direction();

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

void SnakeGame::randomMode()
{
    snake.move();
    gameOver = !snake.legal_move();
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    snake.set_old_direction();

    for (auto& ai_snake : ai_snakes) {
        ai_snake->set_random_direction();

        ai_snake->move();
        if (!ai_snake->legal_move()) ai_snake->reset(find_empty_cell());
        else if (ai_snake->eats(food.get_position())) food.generateFood(find_empty_cell());

        ai_snake->set_old_direction();
    }

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

void SnakeGame::peacefulMode()
{
}

void SnakeGame::aiMode()
{
    snake.move();
    gameOver = !snake.legal_move();

    if (gameOver) return;

    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
        
    for (auto& ai_snake : ai_snakes) {
        for (const sf::Vector2f& s : ai_snake->get_positions()) {
            if (snake.get_positions()[0] == s) {
                gameOver = true;
				return;
			}
        }
    }

    snake.set_old_direction();

    for (size_t i = 0; i < ai_snakes.size(); i++) {

        ai_snakes[i]->set_direction_from_ai(ai_snakes[i]->ai.forwardPass(type_matrix_to_vector(get_all_positions(ai_snakes[i]->get_positions()))));

        ai_snakes[i]->move();
        if (!ai_snakes[i]->legal_move()) ai_snakes[i]->reset(find_empty_cell());
        else if (ai_snakes[i]->eats(food.get_position())) food.generateFood(find_empty_cell());

        for (size_t j = 0; j < ai_snakes.size(); j++) {
            if (i != j) {
                for (const sf::Vector2f& s : ai_snakes[j]->get_positions()) {
                    if (ai_snakes[i]->get_positions()[0] == s) {
						ai_snakes[i]->reset(find_empty_cell());
                        break;
					}
				}
			}
		}

        ai_snakes[i]->set_old_direction();
    }
}

void SnakeGame::trainAiMode()
{
}

void SnakeGame::aiNoobMode()
{
    snake.move();
    gameOver = !snake.legal_move();
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    snake.set_old_direction();

    for (auto& ai_snake : ai_snakes) {
        ai_snake->set_direction(ai_snake->set_direction_of_food(ai_snake, food.get_position(), ai_snake->get_direction()));

        ai_snake->move();
        if (!ai_snake->legal_move()) ai_snake->reset(find_empty_cell());
        else if (ai_snake->eats(food.get_position())) food.generateFood(find_empty_cell());

        ai_snake->set_old_direction();
    }

    /*for (int w = 0; w < ai_snakes.size(); w++) {
        ai_snakes[w]->set_direction(ai_snakes[w]->set_direction_of_food(ai_snakes[w], food.get_position(), ai_snakes[w]->get_direction()));

        ai_snakes[w]->move();
        if (!ai_snakes[w]->legal_move()) ai_snakes[w]->reset(find_empty_cell());
        else if (ai_snakes[w]->eats(food.get_position())) food.generateFood(find_empty_cell());

        ai_snakes[w]->set_old_direction();
    }*/

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

sf::Vector2f SnakeGame::find_empty_cell()
{
    sf::Vector2f freePos;

    //find valid position
    bool invalidPos;
    do {
        invalidPos = false;

        freePos.x = rand() % PIXEL_SIZE * BLOCK_SIZE;
        freePos.y = rand() % PIXEL_SIZE * BLOCK_SIZE;

        if (freePos == food.get_position()) invalidPos = true;

        for (const sf::Vector2f s : snake.get_positions()) {
            if (freePos == s) {
                invalidPos = true;
                break;
            }
        }

        for (const auto& ai_snake : ai_snakes) {
            for (const sf::Vector2f s : ai_snake->get_positions()) {
                if (freePos == s) {
                    invalidPos = true;
                    break;
                }
            }
        }

    } while (invalidPos);

    return freePos;
}

std::vector<std::vector<Type>> SnakeGame::get_all_positions(const std::vector<sf::Vector2f>& these_positions)
{
    std::vector<std::vector<Type>> all_positions(PIXEL_SIZE, std::vector<Type>(PIXEL_SIZE, Empty_type));

    //chyba - ak je had mimo okna, program padne

    for (const sf::Vector2f& s : snake.get_positions()) {
	    all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = otherSnake;
    }

    for (const auto& ai_snake : ai_snakes) {
        for (const sf::Vector2f& s : ai_snake->get_positions()) {
			all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = otherSnake;
		}
	}

    for (const sf::Vector2f& s : these_positions) {
        all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = thisSnake;
    }

	all_positions[food.get_position().x / BLOCK_SIZE][food.get_position().y / BLOCK_SIZE] = Food_type;

	return all_positions;
}

std::vector<double> SnakeGame::type_matrix_to_vector(const std::vector<std::vector<Type>>& matrix)
{
    std::vector<double> inputs(PIXEL_SIZE * PIXEL_SIZE);

    for (int i = 0; i < PIXEL_SIZE; i++) {
        for (int j = 0; j < PIXEL_SIZE; j++) {
            if (matrix[i][j] == thisSnake) {
				inputs[i * PIXEL_SIZE + j] = 0.;
			}
            else if (matrix[i][j] == otherSnake) {
                inputs[i * PIXEL_SIZE + j] = 0.2;
			}
            else if (matrix[i][j] == Food_type) {
                inputs[i * PIXEL_SIZE + j] = 1.;
			}
            else {
                inputs[i * PIXEL_SIZE + j] = 0.5;
			}
		}
	}

    return inputs;
}
