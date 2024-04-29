#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SnakeGame.hpp"

int main() {
    SnakeGame game;

    game.run();

    /*while (!game.restartGame) {
        game.run();
        game.retryMenu();
    }*/

    return 0;
}