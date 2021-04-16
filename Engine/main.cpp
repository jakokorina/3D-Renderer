#include <iostream>
#include "world.h"

int main() {
    World W(800, 600);
    Triangle T({{1,1,1}, {-1, -1, 1}, {-1, 1, 1}}, sf::Color::Red);
    W.addObject(T);
    W.start();
    return 0;
}
