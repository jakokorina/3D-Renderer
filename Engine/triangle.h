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
        std::pair<bool, std::pair<float, sf::Color>>
        static barycentricCoordinates(const glm::mat3x4& V, const glm::vec2& P, const std::vector<sf::Color>& color);
        static sf::Color multiply(sf::Color color, float f);
        static void afterClipping(const glm::mat4& transformMatrix, glm::mat3x4& newPoints, Screen& screen,
                                  const std::vector<sf::Color>& color);
        static std::pair<glm::vec4, sf::Color>
        intersection(const glm::vec4& A1, const glm::vec4& A2, sf::Color c1, sf::Color c2, float n);

    public:
        Triangle(const std::vector<glm::vec3>& p, sf::Color colour_);
        Triangle(const std::vector<glm::vec3>& p, const std::vector<sf::Color>& colour_);
        Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour_);
        Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const std::vector<sf::Color>& colour_);
        void draw(Screen& screen, const glm::mat4& cameraTransform, const glm::mat4& transformMatrix) const;
    };
}
