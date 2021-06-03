#include "triangle.h"

namespace Engine {
    Triangle::Triangle(const std::vector<glm::vec3>& p, sf::Color colour_) {
        assert(p.size() == 3);
        points = p;
        colour = std::vector<sf::Color>(3, colour_);
    }

    Triangle::Triangle(const std::vector<glm::vec3>& p, const std::vector<sf::Color>& colour_) {
        assert(p.size() == 3 && colour_.size() == 3);
        points = p;
        colour = colour_;
    }

    Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, sf::Color colour_) {
        points = {p1, p2, p3};
        colour = std::vector<sf::Color>(3, colour_);
    }

    Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
                       const std::vector<sf::Color>& colour_) {
        assert(colour_.size() == 3);
        points = {p1, p2, p3};
        colour = colour_;
    }

    void Triangle::draw(Screen& screen, const glm::mat4& transformMatrix) const {
        glm::mat3x4 newPoints(3);
        for (int i = 0; i < 3; ++i) {
            newPoints[i] = {points[i].x, points[i].y, points[i].z, 1.0f};
        }
        newPoints = transformMatrix * newPoints;
        newPoints[0] /= newPoints[0].w;
        newPoints[1] /= newPoints[1].w;
        newPoints[2] /= newPoints[2].w;
        if (newPoints[0].y == newPoints[1].y && newPoints[0].y == newPoints[2].y) {
            return; // треугольники, стоящие перпендиклярно камере, не интересны
        }
        if (newPoints[0].x == newPoints[1].x && newPoints[0].x == newPoints[2].x) {
            return; // треугольники, стоящие перпендиклярно камере, не интересны #2
        }
        /*for (const auto& P: newPoints) {
            std::cout << P.x << " " << P.y << '\n';
        }
        std::cout << '\n';*/
        auto[h, w] = screen.getSize();
        float left = std::min({newPoints[0].x, newPoints[1].x, newPoints[2].x}), right = std::max(
                {newPoints[0].x, newPoints[1].x, newPoints[2].x});
        float bottom = std::min({newPoints[0].y, newPoints[1].y, newPoints[2].y}), top = std::max(
                {newPoints[0].y, newPoints[1].y, newPoints[2].y});
        left = std::max(left, (float) 0),  right = std::min(right, (float) w - 1);
        bottom = std::max(bottom, (float) 0),  top = std::min(top, (float) h - 1);
        for (int x = (int) left; x <= (int) right; ++x) {
            for (int y = (int) bottom; y <= (int) top; ++y) {
                auto[inTriangle, zValue] = barycentricCoordinates(newPoints, glm::vec2{x, y});
                if (inTriangle) {
                    screen.setColour(zValue.second, x, y, zValue.first);
                }
            }
        }
    }

    std::pair<bool, std::pair<float, sf::Color>>
    Triangle::barycentricCoordinates(const glm::mat3x4& V, const glm::vec2& P) const {
        glm::vec3 a = {V[1].x - V[0].x, V[2].x - V[0].x, V[0].x - P.x};
        glm::vec3 b = {V[1].y - V[0].y, V[2].y - V[0].y, V[0].y - P.y};
        glm::vec3 c = glm::cross(a, b);
        c /= c.z;
        c.z = 1 - c.x - c.y;
        glm::vec4 point = c.z * V[0] + c.x * V[1] + c.y * V[2];
        sf::Color col = multiplicate(colour[0], c.z) + multiplicate(colour[1], c.x) + multiplicate(colour[2], c.y);
        return {c.x >= 0 && c.y >= 0 && c.z >= 0, {point.z, col}};
    }
    sf::Color Triangle::multiplicate(sf::Color color, float f) {
        return sf::Color(color.r * f, color.g * f, color.b * f, (color.a * f));
    }
}
