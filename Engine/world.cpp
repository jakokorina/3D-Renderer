#include "world.h"

namespace Engine {
    void World::addObject(const std::vector<glm::vec3>& points, sf::Color colour) {
        Triangle triangle(points, colour);
        objects.push_back(triangle);
    }
    void World::addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour) {
        Triangle triangle(p1, p2, p3, colour);
        objects.push_back(triangle);
    }

    void World::setCameraLocation(glm::vec3 new_location) {
        camera.setLocation(new_location);
    }

    void World::drawPicture() {
        window.clear();
        screen.clear();
        renderer.drawObjects(objects, window);
        window.display();
    }

    void World::start() {
        drawPicture();
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                // Request for closing the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // здесь можно написать обработку движения камеры с клавиатуры
        }
    }
    void World::setCameraDirection(glm::vec3 new_direction) {
        camera.setDirection(new_direction);
    }
}