#pragma once

#include <SFML/Graphics.hpp>
#include "triangle.h"
#include "camera.h"
#include "screen.h"
#include <vector>

namespace Engine {

    class Renderer {
    private:
        Camera& camera;
        Screen& screen;

    public:
        Renderer(Screen& scr, Camera& cam) : screen(scr), camera(cam) {}
        void drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window);
    };

    void Renderer::drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window) {
        glm::mat4 transformMatrix =
                screen.getViewOrtMatrix() * screen.getProjectionMatrix() * camera.getCameraTransformationMatrix();
        for (const auto& object : objects) {
            object.draw(screen, transformMatrix);
        }
        screen.screenToWindow(window);
        {
            auto[h, w] = screen.getSize();
            sf::RectangleShape pixel;
            pixel.setSize({10.f, 10.f});
            pixel.setPosition({(float) w / 2, (float) h / 2});
            pixel.setFillColor(sf::Color::White);
            window.draw(pixel);
        }
    }
}
