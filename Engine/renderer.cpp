#include "renderer.h"

namespace Engine {
    void Renderer::drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window) {
        glm::mat4 screenTransformMatrix = screen.getScreenMatrix();
        glm::mat4 cameraTransformMatrix = camera.getCameraTransformMatrix();
        for (const auto& object : objects) {
            object.draw(screen, cameraTransformMatrix, screenTransformMatrix);
        }

        screen.screenToWindow(window);
        {
            auto[h, w] = screen.getSize();
            sf::RectangleShape pixel;
            pixel.setSize({5.f, 5.f});
            pixel.setPosition({(float) w / 2, (float) h / 2});
            pixel.setFillColor(sf::Color::White);
            window.draw(pixel);
        }
    }
}
