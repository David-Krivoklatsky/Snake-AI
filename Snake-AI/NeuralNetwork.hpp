#pragma once

#include "Globals.hpp"

#include <vector>
#include <string>

struct Neuron {
    double value = 0;
    double bias = 0;
    std::vector<double> input_weights;

    double error = 0;
};

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>&);

    std::vector<double> forwardPass(const std::vector<double>&);
    void backprop(const std::vector<double>&, const std::vector<double>&);

    void save2file(const std::string&);
private:
    std::vector<std::vector<Neuron>> net;

    double learningRate = 1.;

    double sigmoid(double z) const;
    double sigmoidPrime(double z) const;

    std::vector<int> layers;
    int numLayers;
};