#include "NeuralNetwork.hpp"

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
void NeuralNetwork::backprop(const std::vector<double>& input, const std::vector<double>& expected, std::vector<std::vector<double>>& nablaB, std::vector<std::vector<std::vector<double>>>& nablaW) const {
	std::vector<std::vector<double>> activations;
	std::vector<std::vector<double>> zs;

	activations.resize(numLayers);
	zs.resize(numLayers);

	for (size_t i = 0; i < numLayers; i++)
	{
		activations[i].resize(layers[i]);
		zs[i].resize(layers[i]);
	}

	for (size_t i = 0; i < input.size(); i++)
	{
		activations[0][i] = input[i];
	}

	for (size_t i = 1; i < numLayers; i++)
	{
		for (size_t j = 0; j < layers[i]; j++)
		{
			double temp_value = 0;
			for (size_t k = 0; k < layers[i - 1]; k++)
			{
				temp_value += activations[i - 1][k] * net[i][j].input_weights[k];
			}
			temp_value += net[i][j].bias;

			zs[i][j] = temp_value;
			activations[i][j] = sigmoid(temp_value);
		}
	}

	std::vector<std::vector<double>> delta;
	delta.resize(numLayers);

	for (size_t i = 0; i < numLayers; i++)
	{
		delta[i].resize(layers[i]);
	}

	for (size_t i = 0; i < layers.back(); i++)
	{
		delta.back()[i] = (activations.back()[i] - expected[i]) * sigmoidPrime(zs.back()[i]);
	}

	for (size_t i = numLayers - 2; i > 0; i--)
	{
		for (size_t j = 0; j < layers[i]; j++)
		{
			double temp_value = 0;
			for (size_t k = 0; k < layers[i + 1]; k++)
			{
				temp_value += delta[i + 1][k] * net[i + 1][k].input_weights[j];
			}
			delta[i][j] = temp_value * sigmoidPrime(zs[i][j]);
		}
	}
}