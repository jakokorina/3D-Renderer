#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <utility>
#include <vector>

namespace Engine {
    class Screen {
    private:
        int height, width;
        float far = 100.0f, near = 0.5f;
        float left = -2, right = 2, top = 1, bottom = -1;
        std::vector<std::vector<sf::Color>> colourBuf;
        std::vector<std::vector<float>> zBuf;
        glm::mat4 screenMatrix;
        glm::mat4 computeViewOrt();
        glm::mat4 computeProjection();

    public:
        Screen(int h, int w);
        std::pair<size_t, size_t> getSize() const;
        glm::mat4 getScreenMatrix() const;
        void setColour(sf::Color colour, size_t x, size_t y, float z);
        void screenToWindow(sf::RenderWindow& window);
        void clear();
    };
}
