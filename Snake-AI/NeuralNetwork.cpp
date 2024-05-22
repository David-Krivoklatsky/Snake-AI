#include "NeuralNetwork.hpp"

#include <random>
#include <fstream>
#include <iostream>

NeuralNetwork::NeuralNetwork(const std::vector<int>& vrstvy)
    : layers(vrstvy)
    , numLayers(layers.size())
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    net.resize(numLayers);
    net[0].resize(layers[0]);

    for (size_t i = 1; i < numLayers; ++i) {
        net[i].resize(layers[i]);

        for (size_t j = 0; j < layers[i]; j++) {
            net[i][j].bias = dist(gen);
            
            net[i][j].input_weights.resize(layers[i - 1]);
            for (size_t k = 0; k < layers[i - 1]; k++) {
                net[i][j].input_weights[k] = dist(gen);
            }
        }
    }
}

NeuralNetwork::NeuralNetwork(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {

        file >> numLayers;

        layers.resize(numLayers);
        for (int i = 0; i < numLayers; i++)
            file >> layers[i];

        net.resize(numLayers);
        net[0].resize(layers[0]);

        for (size_t i = 1; i < numLayers; ++i) {
            net[i].resize(layers[i]);

            for (size_t j = 0; j < layers[i]; j++) {
                file >> net[i][j].bias;

                net[i][j].input_weights.resize(layers[i - 1]);
                for (size_t k = 0; k < layers[i - 1]; k++) {
                    file >> net[i][j].input_weights[k];
                }
            }
        }

        file.close();
    }

    else {
        std::cout << "Fail loading ai from file: " << filename << "\n";
    }
}

inline double NeuralNetwork::sigmoid(double z) const {
	return 1.0 / (1.0 + exp(-z));
}

inline double NeuralNetwork::sigmoidPrime(double z) const {
	return sigmoid(z) * (1 - sigmoid(z));
}

std::vector<double> NeuralNetwork::forwardPass(const std::vector<double>& inputs) {
    for (size_t i = 0; i < inputs.size(); i++)
    {
        net[0][i].value = inputs[i];
    }

    for (size_t i = 1; i < net.size(); i++)
    {
        for (size_t j = 0; j < net[i].size(); j++)
        {
            double temp_value = 0;
            for (size_t k = 0; k < net[i - 1].size(); k++)
            {
                temp_value += net[i - 1][k].value * net[i][j].input_weights[k];
            }
            temp_value += net[i][j].bias;

            net[i][j].value = sigmoid(temp_value);
        }
    }

    std::vector<double> output;
    for (size_t i = 0; i < net.back().size(); i++)
    {
        output.push_back(net.back()[i].value);
    }
    return output;
}

void NeuralNetwork::backprop(const std::vector<double>& input, const std::vector<double>& expected) {
    // Perform forward pass to calculate outputs
    std::vector<double> outputs = forwardPass(input);

    // Calculate output layer errors
    std::vector<double> outputErrors;
    for (size_t i = 0; i < expected.size(); ++i) {
        double error = expected[i] - outputs[i];
        outputErrors.push_back(error * sigmoidPrime(outputs[i]));
    }

    // Backpropagate errors
    for (int layer = numLayers - 1; layer > 0; --layer) {
        for (size_t i = 0; i < net[layer].size(); ++i) {
            double error = 0.0;
            // Calculate error for hidden layers
            if (layer < numLayers - 1) {
                for (size_t j = 0; j < net[layer + 1].size(); ++j) {
                    error += net[layer + 1][j].input_weights[i] * net[layer + 1][j].error;
                }
                error *= sigmoidPrime(net[layer][i].value);
            }
            else { // Output layer
                error = outputErrors[i];
            }
            net[layer][i].error = error;
        }
    }

    // Update weights and biases
    for (int layer = numLayers - 1; layer > 0; --layer) {
        for (size_t i = 0; i < net[layer].size(); ++i) {
            for (size_t j = 0; j < net[layer][i].input_weights.size(); ++j) {
                double delta = learningRate * net[layer][i].error * net[layer - 1][j].value;
                net[layer][i].input_weights[j] += delta;
            }
            double deltaBias = learningRate * net[layer][i].error;
            net[layer][i].bias += deltaBias;
        }
    }
}

void NeuralNetwork::save2file(const std::string& filename)
{
    std::ofstream file(filename);

    if (file.is_open()) {
        file << numLayers << "\n";
        for (int i = 0; i < numLayers; i++) {
			file << layers[i] << " ";
		}

        for (int i = 1; i < net.size(); i++) {
            for (int j = 0; j < net[i].size(); j++) {
                file << net[i][j].bias << " ";
                for (int k = 0; k < net[i][j].input_weights.size(); k++) {
                    file << net[i][j].input_weights[k] << " ";
                }
                file << std::endl;
            }
            file << std::endl;
        }
        file.close();
    }
}