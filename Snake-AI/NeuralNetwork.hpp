#pragma once

#include "Globals.hpp"

#include <vector>
#include <random>

class NeuralNetwork {

public:
    NeuralNetwork(const std::vector<int>& layers);

    void SGD(const std::vector<std::vector<double>>& trainingData, int epochs, int miniBatchSize, double learningRate);
    void updateMiniBatch(const std::vector<std::vector<double>>& miniBatch, double learningRate);

private:
    void forwardPass(const std::vector<double>& input, std::vector<std::vector<double>>& activations, std::vector<std::vector<double>>& zs) const;
    void backprop(const std::vector<double>& input, const std::vector<double>& expected, std::vector<std::vector<double>>& nablaB, std::vector<std::vector<std::vector<double>>>& nablaW) const;

    double sigmoid(double z);
    double sigmoidPrime(double z);
    double costDerivative(double activation, double expected);


    std::vector<int> layers;
    int numLayers;
    std::vector<std::vector<double>> biases;
    std::vector<std::vector<std::vector<double>>> weights;
};