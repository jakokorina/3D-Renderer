#pragma once

#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "camera.h"
#include "screen.h"
#include "triangle.h"
#include <vector>

class World {
private:
    std::vector<Triangle> objects;
    Camera camera;
    Screen screen;
    Renderer renderer;
    sf::RenderWindow window;

public:
    World(int width = 800, int height = 800, glm::vec3 camLoc = {0, 0, -1}, glm::vec3 camDir = {0, 0, 1}): camera(camLoc, camDir),
                                                                                                           screen(height, width),
                                                                                                           renderer(screen, camera),
                                                                                                           window(sf::RenderWindow(sf::VideoMode(width, height), "Simple")){
        window.setFramerateLimit(60);
    }
    void addObject(const Triangle& triangle);
    void setCameraLocation(glm::vec3 new_location);
    void getPicture();
    void start();
};

void World::addObject(const Triangle& triangle) {
    objects.push_back(triangle);
}

void World::setCameraLocation(glm::vec3 new_location) {
    camera.setLocation(new_location);
}

void World::getPicture() {
    window.clear();
    screen.clear();
    renderer.drawObjects(objects, window);
    window.display();
}

void World::start() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        getPicture();
        // здесь можно написать обработку движения камеры с клавиатуры
    }
}
