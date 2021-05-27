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
        sf::Color colour;
        static std::pair<bool, float> barycentricCoordinates(const std::vector<glm::vec4>& V, const glm::vec2& P);

    public:
        Triangle(const std::vector<glm::vec3>& p, sf::Color colour_);
        Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour_);
        void draw(Screen& screen, const glm::mat4& transformMatrix) const;
    };
}
