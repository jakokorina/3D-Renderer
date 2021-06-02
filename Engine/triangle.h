#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <vector>
#include <algorithm>
#include "screen.h"

namespace Engine {

    class Triangle {
    private:
        std::vector<glm::vec3> points;
        std::vector<sf::Color> colour;
        std::pair<bool, std::pair<float, sf::Color>> barycentricCoordinates(const glm::mat3x4& V, const glm::vec2& P) const;
        static sf::Color multiplicate(sf::Color color, float f) ;

    public:
        Triangle(const std::vector<glm::vec3>& p, sf::Color colour_);
        Triangle(const std::vector<glm::vec3>& p, const std::vector<sf::Color>& colour_);
        Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour_);
        Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const std::vector<sf::Color>& colour_);
        void draw(Screen& screen, const glm::mat4& transformMatrix) const;
    };
}
