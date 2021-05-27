#include <iostream>
#include "world.h"

int main() {
    Engine::World W(1800, 1000);
    W.addObject({10,10,5}, {-10, -10, 5}, {10, -10, 5}, sf::Color::Red);
    W.addObject({1,1,0.5}, {-1, -1, 0.5}, {1, -1, 0.5}, sf::Color::Green);
    W.start();
    return 0;
}
