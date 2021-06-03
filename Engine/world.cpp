#include <sstream>
#include "world.h"

namespace Engine {
    World::World(int width, int height, glm::vec3 camLoc, glm::vec3 camDir) :
            camera(camLoc, camDir),
            screen(height, width),
            renderer(screen, camera),
            window(sf::RenderWindow(sf::VideoMode(width, height), "Simple renderer")) {
        std::string string = std::filesystem::current_path();
        if (!font.loadFromFile(string + "/arial.ttf")) {
            exit(1);
        }
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(24);
    }

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

    void World::drawPicture(const sf::Clock& clock) {
        window.clear();
        screen.clear();
        float before = clock.getElapsedTime().asSeconds();
        renderer.drawObjects(objects, window);
        float time = clock.getElapsedTime().asSeconds() - before;
        text.setString("Seconds per frame: " + std::to_string(time) + "\nNumber of triangles: " +
                       std::to_string(objects.size()));
        window.draw(text);
        window.display();
    }

    void World::start() {
        sf::Clock clock;
        clock.restart();
        drawPicture(clock);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    keyPressed(event.key.code);
                    drawPicture(clock);
                }
            }
        }
    }
    void World::keyPressed(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::A:
                camera.changeLocation({-0.2, 0, 0});
                break;
            case sf::Keyboard::D:
                camera.changeLocation({0.2, 0, 0});
                break;
            case sf::Keyboard::W:
                camera.changeLocation({0, 0.2, 0});
                break;
            case sf::Keyboard::S:
                camera.changeLocation({0, -0.2, 0});
                break;
            case sf::Keyboard::C:
                camera.changeLocation({0, 0, -0.2});
                break;
            case sf::Keyboard::X:
                camera.changeLocation({0, 0, 0.2});
                break;
            case sf::Keyboard::Up:
                camera.changeDirection({0, M_PI / 32, 0});
                break;
            case sf::Keyboard::Down:
                camera.changeDirection({0, -M_PI / 32, 0});
                break;
            case sf::Keyboard::Right:
                camera.changeDirection({M_PI / 32, 0, 0});
                break;
            case sf::Keyboard::Left:
                camera.changeDirection({-M_PI / 32, 0, 0});
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
        }
    }

}
