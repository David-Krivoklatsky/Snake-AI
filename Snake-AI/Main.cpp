#include "SnakeGame.hpp"
//#include "NeuralNetwork.hpp"
//#include <iostream>

int main() {
    SnakeGame game;

    game.run();


    /* //TEST NEURONOVEJ SIETE, FUNGUJE XDD
    NeuralNetwork mojaSiet({ 2, 3, 2 });

    double v1, v2;
    std::cin >> v1 >> v2;
    
    double o1, o2;
    std::cin >> o1 >> o2;

    std::vector<double> vystup = mojaSiet.forwardPass({ v1, v2 });
    std::cout << vystup[0] << vystup[1] << "\n\n";

    for (int i = 0; i < 10000; i++) {
        mojaSiet.backprop({ v1, v2 }, { o1, o2 });
        vystup = mojaSiet.forwardPass({ v1, v2 });
        std::cout << vystup[0] << "\t\t" << vystup[1] << "\n";

        if (vystup[0] == o1) std::cout << "----------prve dobre\n";
        if (vystup[1] == o2) std::cout << "---------druhe dobre\n";
    }
    */
    


    return 0;
}