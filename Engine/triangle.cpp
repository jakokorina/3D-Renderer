#include "triangle.h"
#include <iostream>

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

    void Triangle::draw(Screen& screen, const glm::mat4& cameraTransform, const glm::mat4& transformMatrix) const {
        glm::mat3x4 newPoints(3);
        for (int i = 0; i < 3; ++i) {
            newPoints[i] = {points[i].x, points[i].y, points[i].z, 1.0f};
        }
        newPoints = cameraTransform * newPoints;

        std::vector<bool> belowZero(3);
        std::cout << newPoints[0].z << " " << newPoints[1].z << " " << newPoints[2].z << '\n';
        float near = screen.getNear();
        for (int i = 0; i < 3; ++i) {
            belowZero[i] = newPoints[i].z > -near ? 1 : 0;
        }
        std::cout << belowZero[0] << belowZero[1] << belowZero[2] << '\n';
        if (belowZero[0] && belowZero[1] && belowZero[2]) {
            return;
        }
        if (!(belowZero[0] || belowZero[1] || belowZero[2])) {
            afterClipping(transformMatrix, newPoints, screen, colour);
        }

        auto newColors = colour;
        if (belowZero[2]) {
            std::swap(newPoints[2], newPoints[0]);
            std::swap(belowZero[2], belowZero[0]);
            std::swap(newColors[2], newColors[0]);
        }
        if (belowZero[1]) {
            std::swap(newPoints[1], newPoints[0]);
            std::swap(belowZero[1], belowZero[0]);
            std::swap(newColors[1], newColors[0]);
        }
        if (belowZero[1]) {
            auto[p1, c1] = intersection(newPoints[0], newPoints[2], newColors[0], newColors[2], near);
            auto[p2, c2] = intersection(newPoints[1], newPoints[2], newColors[1], newColors[2], near);
            newPoints[0] = p1;
            newColors[0] = c1;
            newPoints[1] = p2;
            newColors[1] = c2;
            afterClipping(transformMatrix, newPoints, screen, newColors);

        } else {
            auto[p1, c1] = intersection(newPoints[0], newPoints[1], newColors[0], newColors[1], near);
            auto[p2, c2] = intersection(newPoints[0], newPoints[2], newColors[0], newColors[2], near);
            newPoints[0] = p1;
            newColors[0] = c1;
            auto newPoints2 = newPoints;
            auto newColors2 = newColors;
            newPoints2[1] = p2;
            newColors2[1] = c2;
            afterClipping(transformMatrix, newPoints, screen, newColors);
            afterClipping(transformMatrix, newPoints2, screen, newColors2);
        }
    }

    std::pair<bool, std::pair<float, sf::Color>>
    Triangle::barycentricCoordinates(const glm::mat3x4& V, const glm::vec2& P, const std::vector<sf::Color>& color) {
        glm::vec3 a = {V[1].x - V[0].x, V[2].x - V[0].x, V[0].x - P.x};
        glm::vec3 b = {V[1].y - V[0].y, V[2].y - V[0].y, V[0].y - P.y};
        glm::vec3 c = glm::cross(a, b);
        c /= c.z;
        c.z = 1 - c.x - c.y;
        glm::vec4 point = c.z * V[0] + c.x * V[1] + c.y * V[2];
        sf::Color col = multiply(color[0], c.z) + multiply(color[1], c.x) + multiply(color[2], c.y);
        return {c.x >= 0 && c.y >= 0 && c.z >= 0, {point.z, col}};
    }

    sf::Color Triangle::multiply(sf::Color color, float f) {
        return sf::Color(color.r * f, color.g * f, color.b * f, (color.a * f));
    }

    void Triangle::afterClipping(const glm::mat4& transformMatrix, glm::mat3x4& newPoints, Screen& screen,
                                 const std::vector<sf::Color>& color) {
        newPoints = transformMatrix * newPoints;
        newPoints[0] /= newPoints[0].w;
        newPoints[1] /= newPoints[1].w;
        newPoints[2] /= newPoints[2].w;

        auto[h, w] = screen.getSize();
        float left = std::min({newPoints[0].x, newPoints[1].x, newPoints[2].x}), right = std::max(
                {newPoints[0].x, newPoints[1].x, newPoints[2].x});
        float bottom = std::min({newPoints[0].y, newPoints[1].y, newPoints[2].y}), top = std::max(
                {newPoints[0].y, newPoints[1].y, newPoints[2].y});
        left = std::max(left, (float) 0), right = std::min(right, (float) w - 1);
        bottom = std::max(bottom, (float) 0), top = std::min(top, (float) h - 1);
        for (int x = (int) left; x <= (int) right; ++x) {
            for (int y = (int) bottom; y <= (int) top; ++y) {
                auto[inTriangle, value] = barycentricCoordinates(newPoints, glm::vec2{x, y}, color);
                if (inTriangle) {
                    screen.setColour(value.second, x, y, value.first);
                }
            }
        }
    }

    std::pair<glm::vec4, sf::Color>
    Triangle::intersection(const glm::vec4& P1, const glm::vec4& P2, sf::Color c1, sf::Color c2, float n) {
        float A = (P2.z + n) / (P2.z - P1.z);
        auto P = P1 * A + P2 * (1 - A);
        P.w = 1;
        sf::Color c = multiply(c1, A) + multiply(c2, 1 - A);
        return std::make_pair(P, c);
    }
}
