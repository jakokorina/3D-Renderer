#pragma once

#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "camera.h"
#include "screen.h"
#include "triangle.h"
#include <vector>

namespace Engine {

    class World {
    private:
        std::vector<Triangle> objects;
        Camera camera;
        Screen screen;
        Renderer renderer;
        sf::RenderWindow window;
        void drawPicture();
        void setCameraLocation(glm::vec3 new_location);
        void setCameraDirection(glm::vec3 new_direction);

    public:
        World(int width = 800, int height = 800, glm::vec3 camLoc = {0, 0, -1}, glm::vec3 camDir = {0, 0, 1}) : camera(
                camLoc, camDir),
                                                                                                                screen(height,
                                                                                                                       width),
                                                                                                                renderer(
                                                                                                                        screen,
                                                                                                                        camera),
                                                                                                                window(sf::RenderWindow(
                                                                                                                        sf::VideoMode(
                                                                                                                                width,
                                                                                                                                height),
                                                                                                                        "Simple renderer")) {
        }
        void addObject(const std::vector<glm::vec3>& points, sf::Color colour);
        void addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour);
        void start();
    };
}
