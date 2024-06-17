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
    NeuralNetwork(const std::string&);

    std::vector<double> forwardPass(const std::vector<double>&);
    void backprop(const std::vector<double>&, const std::vector<double>&);

    void save2file(const std::string&);

    const std::vector<std::vector<Neuron>>& getNetwork() const { return net; }
    const std::vector<int>& getLayers() const { return layers; }

private:
    std::vector<std::vector<Neuron>> net;

    double learningRate = .05;

    double sigmoid(double z) const;
    double sigmoidPrime(double z) const;

    std::vector<int> layers;
    int numLayers;
};