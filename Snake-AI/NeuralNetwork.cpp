#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<int>& vrstvy)
    : layers(vrstvy)
    , numLayers(layers.size())
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    // Initialize biases
    for (int i = 1; i < numLayers; ++i) {
        std::vector<double> layerBiases;
        for (int j = 0; j < layers[i]; ++j) {
            layerBiases.push_back(dist(gen));
        }
        biases.push_back(layerBiases);
    }

    // Initialize weights
    for (int i = 1; i < numLayers; ++i) {
        std::vector<std::vector<double>> layerWeights;
        for (int j = 0; j < layers[i]; ++j) {
            std::vector<double> neuronWeights;
            for (int k = 0; k < layers[i - 1]; ++k) {
                neuronWeights.push_back(dist(gen));
            }
            layerWeights.push_back(neuronWeights);
        }
        weights.push_back(layerWeights);
    }
}

inline double NeuralNetwork::sigmoid(double z) {
	return 1.0 / (1.0 + exp(-z));
}

inline double NeuralNetwork::sigmoidPrime(double z) {
	return sigmoid(z) * (1 - sigmoid(z));
}

inline double NeuralNetwork::costDerivative(double activation, double expected) {
	return activation - expected;
}

void NeuralNetwork::SGD(const std::vector<std::vector<double>>& trainingData, int epochs, int miniBatchSize, double learningRate) {
    int n = trainingData.size();
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(trainingData.begin(), trainingData.end(), g);
        for (int i = 0; i < n; i += miniBatchSize) {
            std::vector<std::vector<double>> miniBatch(trainingData.begin() + i, trainingData.begin() + std::min(i + miniBatchSize, n));
            updateMiniBatch(miniBatch, learningRate);
        }
    }
}

void NeuralNetwork::forwardPass(const std::vector<double>& input, std::vector<std::vector<double>>& activations, std::vector<std::vector<double>>& zs) const {
    std::vector<double> a = input;
    activations.clear();
    zs.clear();
    activations.push_back(a);

    for (int l = 1; l < numLayers; ++l) {
        std::vector<double> z;
        std::vector<double> nextLayerActivations(layers[l], 0.0);
        for (int j = 0; j < layers[l]; ++j) {
            double weightedSum = 0.0;
            for (int k = 0; k < layers[l - 1]; ++k) {
                weightedSum += weights[l - 1][j][k] * activations[l - 1][k];
            }
            z.push_back(weightedSum + biases[l - 1][j]);
            nextLayerActivations[j] = sigmoid(z.back());
        }
        zs.push_back(z);
        activations.push_back(nextLayerActivations);
    }
}

void NeuralNetwork::backprop(const std::vector<double>& input, const std::vector<double>& expectedOutput, std::vector<std::vector<double>>& nablaB, std::vector<std::vector<std::vector<double>>>& nablaW) const {
    std::vector<std::vector<double>> activations;
    std::vector<std::vector<double>> zs;
    forwardPass(input, activations, zs);

    // Initialize delta for the output layer
    std::vector<double> delta = costDerivative(activations.back(), expectedOutput);

    // Backpropagate the error
    for (int l = numLayers - 2; l >= 0; --l) {
        std::vector<double> sp;
        for (int j = 0; j < layers[l]; ++j) {
            double z = zs[l][j];
            sp.push_back(sigmoidPrime(z));
        }
        std::vector<double> nextDelta(layers[l], 0.0);
        for (int j = 0; j < layers[l]; ++j) {
            double sum = 0.0;
            for (int k = 0; k < layers[l + 1]; ++k) {
                sum += weights[l][k][j] * delta[k];
            }
            nextDelta[j] = sum * sp[j];
        }
        delta = nextDelta;

        // Accumulate gradients for biases and weights
        for (int j = 0; j < layers[l + 1]; ++j) {
            nablaB[l][j] += delta[j];
            for (int k = 0; k < layers[l]; ++k) {
                nablaW[l][j][k] += delta[j] * activations[l][k];
            }
        }
    }
}
