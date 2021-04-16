#pragma once

#include <SFML/Graphics.hpp>
#include "triangle.h"
#include "camera.h"
#include "screen.h"
#include <vector>

class Renderer{
    Camera& camera;
    Screen& screen;

public:
    Renderer(Screen &scr, Camera &cam): screen(scr), camera(cam) {}
    void drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window);
};

void Renderer::drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window) {
    glm::mat4 transformMatrix = screen.getVeiwOrtMatrix() * screen.getProjectionMatrix() * camera.getCameraTransformationMatrix();
    for (const auto& object : objects) {
        object.draw(screen, transformMatrix);
    }
    screen.screenToWindow(window);
}