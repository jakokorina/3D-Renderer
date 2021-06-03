#include <iostream>
#include "world.h"

int main() {
    Engine::World W(800, 600, {10, 10, -1});
    std::vector<sf::Color> V = {sf::Color::Red, sf::Color::Green, sf::Color::Blue};
    std::vector<sf::Color> V1 = {sf::Color::Red, sf::Color::Yellow, sf::Color::Yellow};
    std::vector<sf::Color> V2 = {sf::Color::Cyan, sf::Color::Magenta, sf::Color::Yellow};

    W.addObject({10, 10, 5}, {-10, -5, 5}, {10, -5, 5}, V);
    W.addObject({10, 10, 5}, {-10, -5, 5}, {-10, 10, 5}, V);

    W.addObject({10, 10, 5}, {-10, 10, 5}, {-10, 15, 9}, V1);
    W.addObject({10, 10, 5}, {20, 15, 9}, {-10, 15, 9}, V1);

    W.addObject({10, 10, 5}, {10, -5, 5}, {20, 15, 9}, V2);
    W.addObject({20, -7, 9}, {10, -5, 5}, {20, 15, 9}, V2);
    //W.addObject({10, 10, 5}, {15, 15, 9}, {-10, 15, 9}, V1);

    //W.addObject({10, 10, 5}, {-10, -10, 5}, {-10, 10, 5}, V);
    //W.addObject({1, 1, 0.5}, {-1, -1, 6}, {1, -1, 0.5}, V1);
    W.start();
    return 0;
}
