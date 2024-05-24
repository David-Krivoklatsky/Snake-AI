#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "Direction.hpp"
#include "SnakeGame.hpp"
#include "DrawObjects.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "StartMenu.hpp"
#include "NeuralNetwork.hpp"
#include "SnakeSkin.hpp"

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

    for (int i = 1; i <= numberOfSkins; i++) {
		skins.push_back(std::make_shared<SnakeSkin>("Snake_texture" + std::to_string(i)));
	}

    snake.setSkin(skins[0]);

    general_font.loadFromFile("font.ttf");

    scoreText.setFont(general_font);
    scoreText.setFillColor(sf::Color::White);

    draw_objects.push_back(std::make_unique<Grid>(BLOCK_SIZE));
}

void SnakeGame::run() {
    gameOver = false;

    while (window.isOpen() && start_menu) {
        startInput();

        window.clear();
        startMenu.draw(window);
        window.display();
    }

    setMode(startMenu.mode);

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
                case 6: battleRoyal();
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

    if (startMenu.mode == 4) ai_snakes[0]->ai.save2file("test.snake");
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
                startMenu.anotherSkin(skinChose, numberOfSkins);
                pressed = false;
                snake.setSkin(skins[skinChose]); //set textures here because it was lagging
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

    for (auto& ai_snake : ai_snakes)
        ai_snake->draw(window);

    for (auto& noob_snake : noob_snakes)
		noob_snake->draw(window);

    snake.draw(window);
    food.draw(window);

    window.draw(scoreText);

    window.display();
}

void SnakeGame::setMode(int)
{
    switch (startMenu.mode)
    {
    // case 0: classicMode();

    // random mode
    case 1: {
        for (int i = 0; i < 2; i++) {
            noob_snakes.push_back(std::make_unique<Noob_Snake>(find_empty_cell()));
        }

        for (auto& noob_snake : noob_snakes) {
			noob_snake->setSkin(skins[2 % numberOfSkins]);
		}

        break;
    }

    // peaceful mode - train ai, create new snake
    case 2: {
        std::vector<int> layers = { PIXEL_SIZE * PIXEL_SIZE, PIXEL_SIZE, 3 };

        ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), layers));
        ai_snakes[0]->setSkin(skins[1 % numberOfSkins]);
        break;
    }

    // ai
    case 3: {
        std::vector<int> layers = { PIXEL_SIZE * PIXEL_SIZE, 5 * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, 20, 10, 5 , 10, 3 };

        for (int i = 0; i < 2; i++) {
			ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), layers));
		}

        for (auto& ai_snake : ai_snakes) {
			ai_snake->setSkin(skins[1 % numberOfSkins]);
		}

		break;
    }
    
    // train ai
    case 4: {
        std::vector<int> layers = { PIXEL_SIZE * PIXEL_SIZE, PIXEL_SIZE, 3 };

        ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), layers));

        ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), "test.snake"));
        ai_snakes[0]->setSkin(skins[1]);
        ai_snakes[1]->setSkin(skins[2]);
        break;
    }
    
    // ai noob
    case 5: {
        for (int i = 0; i < 2; i++) {
            noob_snakes.push_back(std::make_unique<Noob_Snake>(find_empty_cell()));
        }

        for (auto& noob_snake : noob_snakes) {
            noob_snake->setSkin(skins[2 % numberOfSkins]);
        }

        break;
    }

    case 6: {
        for (int i = 0; i < 5; i++) {
            noob_snakes.push_back(std::make_unique<Noob_Snake>(find_empty_cell()));
            ai_snakes.push_back(std::make_unique<AI_Snake>(find_empty_cell(), "test.snake"));
        }

        for (auto& noob_snake : noob_snakes) {
            noob_snake->setSkin(skins[2 % numberOfSkins]);
        }

        for (auto& ai_snake : ai_snakes) {
            ai_snake->setSkin(skins[1 % numberOfSkins]);
        }

        break;
    }

	default:
		break;
	}
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

    for (auto& noob_snake : noob_snakes) {
        noob_snake->set_random_direction();

        noob_snake->move();
        if (!noob_snake->legal_move()) noob_snake->reset(find_empty_cell());
        else if (noob_snake->eats(food.get_position())) food.generateFood(find_empty_cell());

        noob_snake->set_old_direction();
    }

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
}

void SnakeGame::peacefulMode()
{
    AI_Snake& had = *ai_snakes[0];

    had.copyFrom(snake);
    had.setSkin(skins[1 % numberOfSkins]);

    std::vector<double> target = { 0., 0., 0. };
    target[snake.get_relative_direction()] = 1.;

    std::vector<double> grid = type_matrix_to_vector(get_all_positions(had.get_positions()));
    std::vector<double> output = had.ai.forwardPass(grid);
    had.set_direction_from_ai(output);
    had.ai.backprop(grid, target);
    had.move();

    snake.move();
    gameOver = !snake.legal_move();
    if (gameOver) return;
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());

    snake.set_old_direction();
    had.set_old_direction();

    std::cout << snake.get_direction() << "\t" << had.get_direction() << "\n";
    for (int i = 0; i < 3; i++) {
        std::cout << output[i] << "\t";
    }
    std::cout << "\n";

    if (had.eats(food.get_position())) food.generateFood(find_empty_cell());

    scoreText.setString(std::to_string(snake.get_score()));
    scoreText.setPosition(WINDOW_SIZE - (scoreText.getGlobalBounds().width + 10), 0);
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
    AI_Snake& had = *ai_snakes[0];

    had.copyFrom(snake);
    had.setSkin(skins[1 % numberOfSkins]);

    std::vector<double> target = {0., 0., 0. };
    target[snake.get_relative_direction()] = 1.;

    std::vector<double> grid = type_matrix_to_vector(get_all_positions(had.get_positions()));
    std::vector<double> output = had.ai.forwardPass(grid);
    had.set_direction_from_ai(output);
    had.ai.backprop(grid, target);
    had.move();

    snake.move();
    gameOver = !snake.legal_move();
    if (gameOver) return;
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    
    snake.set_old_direction();
    had.set_old_direction();

    std::cout << snake.get_direction() << "\t" << had.get_direction() << "\n";
    for (int i = 0; i < 3; i++) {
		std::cout << output[i] << "\t";
	}
    std::cout << "\n";

    if (had.eats(food.get_position())) food.generateFood(find_empty_cell());

    AI_Snake& freeSnake = *ai_snakes[1];

    freeSnake.ai = had.ai;

    freeSnake.set_direction_from_ai(freeSnake.ai.forwardPass(type_matrix_to_vector(get_all_positions(freeSnake.get_positions()))));
    freeSnake.move();

    freeSnake.set_old_direction();

    if (freeSnake.eats(food.get_position())) food.generateFood(find_empty_cell());
    if (!freeSnake.legal_move()) freeSnake.reset(find_empty_cell());
}

void SnakeGame::aiNoobMode()
{
    snake.move();
    gameOver = !snake.legal_move();
    if (gameOver) return;
    if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    snake.set_old_direction();


    for (auto& noob_snake : noob_snakes) {

        std::unique_ptr<Noob_Snake> had1 = std::make_unique<Noob_Snake>(find_empty_cell());
        std::unique_ptr<Noob_Snake> had2 = std::make_unique<Noob_Snake>(find_empty_cell());
        std::unique_ptr<Noob_Snake> had3 = std::make_unique<Noob_Snake>(find_empty_cell());

        had1->copyFrom(*noob_snake);
        had2->copyFrom(*noob_snake);
        had3->copyFrom(*noob_snake);

        noob_snake->set_direction(noob_snake->set_direction_of_food(had1, had2, had3, food.get_position(), noob_snake->get_direction()));

        noob_snake->move();
        if (!noob_snake->legal_move()) noob_snake->reset(find_empty_cell());
        else if (noob_snake->eats(food.get_position())) food.generateFood(find_empty_cell());

        noob_snake->set_old_direction();
    }
}

//pridat reset list, resetovat na konci pohnutia
void SnakeGame::battleRoyal()
{
    std::vector<std::unique_ptr<Snake>> to_reset;

    snake.move();
    //if (!snake.legal_move()) to_reset.push_back();
    if (!snake.legal_move()) snake.reset(find_empty_cell());
    else if (snake.eats(food.get_position())) food.generateFood(find_empty_cell());
    snake.set_old_direction();

    for (auto& ai_snake : ai_snakes) {
        for (const sf::Vector2f& s : ai_snake->get_positions()) {
            if (snake.get_positions()[0] == s) {
                snake.reset(find_empty_cell());
                break;
            }
        }
    }

    for (auto& noob_snake : noob_snakes) {
        for (const sf::Vector2f& s : noob_snake->get_positions()) {
            if (snake.get_positions()[0] == s) {
                snake.reset(find_empty_cell());
                break;
            }
        }
    }

    for (auto& ai_snake : ai_snakes) {

        ai_snake->set_direction_from_ai(ai_snake->ai.forwardPass(type_matrix_to_vector(get_all_positions(ai_snake->get_positions()))));

        ai_snake->move();
        if (!ai_snake->legal_move()) ai_snake->reset(find_empty_cell());
        else if (ai_snake->eats(food.get_position())) food.generateFood(find_empty_cell());
        ai_snake->set_old_direction();

        for (auto& as : ai_snakes) {
            if (as != ai_snake) {
                for (const sf::Vector2f& s : as->get_positions()) {
                    if (ai_snake->get_positions()[0] == s) {
                        ai_snake->reset(find_empty_cell());
                        break;
                    }
                }
            }
        }

        for (auto& noob_snake : noob_snakes) {
            for (const sf::Vector2f& s : noob_snake->get_positions()) {
                if (ai_snake->get_positions()[0] == s) {
                    ai_snake->reset(find_empty_cell());
                    break;
                }
            }
        }
    }

    for (auto& noob_snake : noob_snakes) {

        std::unique_ptr<Noob_Snake> had1 = std::make_unique<Noob_Snake>(find_empty_cell());
        std::unique_ptr<Noob_Snake> had2 = std::make_unique<Noob_Snake>(find_empty_cell());
        std::unique_ptr<Noob_Snake> had3 = std::make_unique<Noob_Snake>(find_empty_cell());
        had1->copyFrom(st*noob_snake
        had2->copyFrom(st*noob_snake
        had3->copyFrom(st*noob_snake

        noob_snake->set_direction(noob_snake->set_direction_of_food(had1, had2, had3, food.get_position(), noob_snake->get_direction()));

        noob_snake->move();
        if (!noob_snake->legal_move()) noob_snake->reset(find_empty_cell());
        else if (noob_snake->eats(food.get_position())) food.generateFood(find_empty_cell());
        noob_snake->set_old_direction();

        for (auto& ns : noob_snakes) {
            if (ns != noob_snake) {
                for (const sf::Vector2f& s : ns->get_positions()) {
                    if (noob_snake->get_positions()[0] == s) {
                        noob_snake->reset(find_empty_cell());
                        break;
                    }
                }
            }
        }

        for (auto& ai_snake : ai_snakes) {
            for (const sf::Vector2f& s : ai_snake->get_positions()) {
                if (noob_snake->get_positions()[0] == s) {
                    noob_snake->reset(find_empty_cell());
                    break;
                }
            }
        }
    }
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

        for (const auto& noob_snake : noob_snakes) {
            for (const sf::Vector2f s : noob_snake->get_positions()) {
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

	    all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = otherSnake;    }

    for (const auto& ai_snake : ai_snakes) {
        for (const sf::Vector2f& s : ai_snake->get_positions()) {
            if (s.x < WINDOW_SIZE && s.x >= 0 && s.y < WINDOW_SIZE && s.y >= 0) {
                all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = otherSnake;
            }
        }
	}

    for (const auto& noob_snake : noob_snakes) {
        for (const sf::Vector2f s : noob_snake->get_positions()) {
            if (s.x < WINDOW_SIZE && s.x >= 0 && s.y < WINDOW_SIZE && s.y >= 0) {
                all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = otherSnake;
            }
        }
    }

    for (const sf::Vector2f& s : these_positions) {
        if (s.x < WINDOW_SIZE && s.x >= 0 && s.y < WINDOW_SIZE && s.y >= 0) {
            all_positions[s.x / BLOCK_SIZE][s.y / BLOCK_SIZE] = thisSnake;
        }
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
