#include "world.h"

namespace Engine {
    void World::addObject(const std::vector<glm::vec3>& points, sf::Color colour) {
        objects.emplace_back(points, colour);
    }
    void World::addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour) {
        objects.emplace_back(p1, p2, p3, colour);
    }
    void World::addObject(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
                          const std::vector<sf::Color>& colour) {
        objects.emplace_back(p1, p2, p3, colour);
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
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    keyPressed(event.key.code);
                    drawPicture();
                }
            }
        }
    }
    void World::keyPressed(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::A:
                camera.changeLocation({-0.5, 0, 0});
                break;
            case sf::Keyboard::D:
                camera.changeLocation({0.5, 0, 0});
                break;
            case sf::Keyboard::W:
                camera.changeLocation({0, 0.5, 0});
                break;
            case sf::Keyboard::S:
                camera.changeLocation({0, -0.5, 0});
                break;
            case sf::Keyboard::X:
                camera.changeLocation({0, 0, -0.5});
                break;
            case sf::Keyboard::C:
                camera.changeLocation({0, 0, 0.5});
                break;
            case sf::Keyboard::Up:
                camera.changeDirection({0, M_PI / 20, 0});
                break;
            case sf::Keyboard::Down:
                camera.changeDirection({0, -M_PI / 20, 0});
                break;
            case sf::Keyboard::Right:
                camera.changeDirection({M_PI / 20, 0, 0});
                break;
            case sf::Keyboard::Left:
                camera.changeDirection({-M_PI / 20, 0, 0});
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
        }
    }
}
