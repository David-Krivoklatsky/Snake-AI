#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"

class Milan : public DrawObject {
public:
    Milan();

    virtual void draw(sf::RenderWindow&) override;

private:
    sf::RectangleShape petrovaFrajerka;
};
