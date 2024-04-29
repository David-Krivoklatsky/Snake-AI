#pragma once

#include "Globals.hpp"

#include <vector>
#include <random>

struct Neuron {
    double value = 0;
    double bias = 0;
    std::vector<double> input_weights;
};

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layers);

private:
    std::vector<std::vector<Neuron>> net;

    std::vector<double> forwardPass(const std::vector<double>& input);
    void backprop(const std::vector<double>& input, const std::vector<double>& expected, std::vector<std::vector<double>>& nablaB, std::vector<std::vector<std::vector<double>>>& nablaW) const;

    double sigmoid(double z) const;
    double sigmoidPrime(double z) const;

    std::vector<int> layers;
    int numLayers;
};