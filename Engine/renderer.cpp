#include "renderer.h"

namespace Engine {
    void Renderer::drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window) {
        glm::mat4 transformMatrix =
                screen.getScreenMatrix() * camera.getCameraTransformMatrix();
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
