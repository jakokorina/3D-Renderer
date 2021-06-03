#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "renderer.h"
#include "camera.h"
#include "screen.h"
#include "triangle.h"
#include <string>
#include <iosfwd>
#include <iostream>
#include <vector>
#include <filesystem>

namespace Engine {

    class World {
    private:
        std::vector<Triangle> objects;
        Camera camera;
        Screen screen;
        Renderer renderer;
        sf::RenderWindow window;
        sf::Font font;
        sf::Text text;
        void drawPicture(const sf::Clock& clock);;

    public:
        World(int width = 800, int height = 800, glm::vec3 camLoc = {0, 0, -1}, glm::vec3 camDir = {0, 0, 1});
        void addObject(const std::vector<glm::vec3>& points, sf::Color colour);
        void addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour);
        void
        addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const std::vector<sf::Color>& colour);
        void start();
        void keyPressed(sf::Keyboard::Key key);
    };
}
