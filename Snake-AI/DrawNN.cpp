#include "DrawNN.hpp"

int NEURON_SHAPE_RADIUS = 4;
int LINE_THICKNESS = 1;
int HORIZONTAL_SPACING = 50;
int VERTICAL_SPACING = 20;

void drawNN(const NeuralNetwork& ai, std::shared_ptr<sf::RenderWindow> window) {
    const std::vector<std::vector<Neuron>>& net = ai.getNetwork();
    const std::vector<int>& layers = ai.getLayers();

    // Prepare neuron shape
    sf::CircleShape neuron_shape(NEURON_SHAPE_RADIUS);
    neuron_shape.setOutlineColor(sf::Color(255, 255, 255));
    neuron_shape.setOutlineThickness(-LINE_THICKNESS);

    // Get window dimensions
    sf::Vector2u windowSize = window->getSize();

    // Calculate drawing positions
    std::vector<std::vector<sf::Vector2f>> neuron_positions;

    float startX = windowSize.x / 2.0f - (layers.size() - 1) * HORIZONTAL_SPACING / 2.0f;

    for (size_t layer = 0; layer < layers.size(); ++layer) {
        std::vector<sf::Vector2f> layer_positions;
        float startY = windowSize.y / 2.0f - (layers[layer] - 1) * VERTICAL_SPACING / 2.0f;

        for (int neuron = 0; neuron < layers[layer]; ++neuron) {
            layer_positions.emplace_back(startX + layer * HORIZONTAL_SPACING, startY + neuron * VERTICAL_SPACING);
        }

        neuron_positions.push_back(layer_positions);
    }

    // Draw connections
    for (size_t layer = 1; layer < layers.size(); ++layer) {
        for (size_t neuron = 0; neuron < layers[layer]; ++neuron) {
            for (size_t prev_neuron = 0; prev_neuron < layers[layer - 1]; ++prev_neuron) {
                sf::Vertex line[] = {
                    sf::Vertex(neuron_positions[layer - 1][prev_neuron], sf::Color::White),
                    sf::Vertex(neuron_positions[layer][neuron], sf::Color::White)
                };
                window->draw(line, 2, sf::Lines);
            }
        }
    }

    // Draw neurons
    for (size_t layer = 0; layer < layers.size(); ++layer) {
        for (size_t neuron = 0; neuron < layers[layer]; ++neuron) {
            neuron_shape.setPosition(neuron_positions[layer][neuron] - sf::Vector2f(NEURON_SHAPE_RADIUS, NEURON_SHAPE_RADIUS));
            window->draw(neuron_shape);
        }
    }
}
