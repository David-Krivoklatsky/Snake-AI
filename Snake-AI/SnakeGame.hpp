#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "DrawObjects.hpp"
#include "Globals.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "StartMenu.hpp"

enum Type {
    thisSnake,
    otherSnake,
    Food_type,
    Empty_type,
    Wall_type
};

class SnakeGame {
public:
    SnakeGame();
    void run();
    void retryMenu();

private:
    void startInput();
    void handleInput();
    void retryInput();
    void update();
    void render();

    sf::Vector2f find_empty_cell();

    std::vector<std::vector<Type>> get_all_positions(const std::vector<sf::Vector2f>&);
    std::vector<double> type_matrix_to_vector(const std::vector<std::vector<Type>>&);

public:
    bool restartGame = false;
    int skinChose = 0;

private:
    sf::RenderWindow window;
    sf::Event event;

    Snake snake;
    Food food;
    Menu menu;
    StartMenu startMenu;

    std::vector<std::string> textureFiles;
    std::vector<std::unique_ptr<AI_Snake>> ai_snakes; //hadi

    sf::Font general_font;

    sf::Text scoreText;
    //sf::Text fpsText;

    //sf::Font fps_font;
    
    bool start_menu = true;
	bool pause = false;
    bool gameOver = false;

    int fpsCounter = 0;
    float fps = 60;

    //std::chrono::high_resolution_clock::time_point lastTime, now;

    std::vector<std::unique_ptr<DrawObject>> draw_objects;
};