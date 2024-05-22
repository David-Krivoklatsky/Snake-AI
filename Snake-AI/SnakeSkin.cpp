#include "SnakeSkin.hpp"

SnakeSkin::SnakeSkin(const std::string& folder)
{
    if (!tail_left.loadFromFile(folder + "/tail_left.png")) {
        //isError = true;
    }
    else {
        tailLeft.setTexture(tail_left);
    }

    if (!tail_right.loadFromFile(folder + "/tail_right.png")) {
        //isError = true;
    }
    else {
        tailRight.setTexture(tail_right);
    }

    if (!tail_down.loadFromFile(folder + "/tail_down.png")) {
        //isError = true;
    }
    else {
        tailDown.setTexture(tail_down);
    }

    if (!tail_up.loadFromFile(folder + "/tail_up.png")) {
        //isError = true;
    }
    else {
        tailUp.setTexture(tail_up);
    }

    if (!horizontal.loadFromFile(folder + "/body_horizontal.png")) {
        //isError = true;
    }
    else {
        horiz.setTexture(horizontal);
    }

    if (!vertical.loadFromFile(folder + "/body_vertical.png")) {
        //isError = true;
    }
    else {
        vertic.setTexture(vertical);
    }

    if (!topright.loadFromFile(folder + "/body_topright.png")) {
        //isError = true;
    }
    else {
        topRight.setTexture(topright);
    }

    if (!topleft.loadFromFile(folder + "/body_topleft.png")) {
        //isError = true;
    }
    else {
        topLeft.setTexture(topleft);
    }

    if (!bottomleft.loadFromFile(folder + "/body_bottomleft.png")) {
        //isError = true;
    }
    else {
        bottomLeft.setTexture(bottomleft);
    }

    if (!bottomright.loadFromFile(folder + "/body_bottomright.png")) {
        //isError = true;
    }
    else {
        bottomRight.setTexture(bottomright);
    }

    if (!head_left.loadFromFile(folder + "/head_left.png")) {
        //isError = true;
    }
    else {
        headLeft.setTexture(head_left);
    }

    if (!head_right.loadFromFile(folder + "/head_right.png")) {
        //isError = true;
    }
    else {
        headRight.setTexture(head_right);
    }

    if (!head_down.loadFromFile(folder + "/head_down.png")) {
        //isError = true;
    }
    else {
        headDown.setTexture(head_down);
    }

    if (!head_up.loadFromFile(folder + "/head_up.png")) {
        //isError = true;
    }
    else {
        headUp.setTexture(head_up);
    }
}