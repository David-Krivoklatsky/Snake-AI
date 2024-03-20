#include <SFML/Graphics.hpp>
#include "SnakeGame.h"

int main() {
    SnakeGame game;
    while (game.restartGame) {
        game.run();
        game.retryMenu();
    }
    return 0;
}
