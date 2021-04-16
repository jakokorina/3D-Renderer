#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <vector>
#include <algorithm>
#include "screen.h"

class Triangle {
private:
    std::vector<glm::vec3> points;
    sf::Color colour;
    static std::pair<bool, glm::vec3> barycentricCoordinates(const std::vector<glm::vec4>& V, const glm::vec2& P);
    static float getZValue(const std::vector<glm::vec4>& V, const glm::vec3& barycentricCoor);

public:
    Triangle(const std::vector<glm::vec3>& p, sf::Color colour_);
    void draw(Screen& screen, const glm::mat4& transformMatrix) const;
};

Triangle::Triangle(const std::vector<glm::vec3>& p, sf::Color colour_) {
    assert(p.size() == 3);
    points = p;
    colour = colour_;
}


void Triangle::draw(Screen& screen, const glm::mat4& transformMatrix) const {
    std::vector<glm::vec4> newPoints(3);
    for (int i = 0; i < 3; ++i) {
        newPoints[i] = {points[i].x, points[i].y, points[i].z, 1.0f};
    }
    for (auto& p : newPoints) {
        p = transformMatrix * p;
        p /= p.w;

    }
    if (newPoints[0].y == newPoints[1].y && newPoints[0].y == newPoints[2].y) {
        return; // треугольники, стоящие перпендиклярно камере, не интересны
    }
    auto[w, h] = screen.getSize();
    float left = std::min({newPoints[0].x, newPoints[1].x, newPoints[2].x}), right = std::max({newPoints[0].x, newPoints[1].x, newPoints[2].x});
    float bottom = std::min({newPoints[0].y, newPoints[1].y, newPoints[2].y}), top = std::max({newPoints[0].y, newPoints[1].y, newPoints[2].y});
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            if (x < left || y < bottom || x > right || y > top) {
                continue;
            } // точка не попадает в минимальный прямоугольник, содержащий наш треугольник
            auto [flag, baryc] = barycentricCoordinates(newPoints, glm::vec2{x, y});
            if (flag) {
                float zValue = getZValue(newPoints, baryc);
                screen.setColour(colour, x, y, zValue);
            }
        }
    }
}

std::pair<bool, glm::vec3> Triangle::barycentricCoordinates(const std::vector<glm::vec4>& V, const glm::vec2& P) {
    glm::vec3 a = {V[1].x - V[0].x, V[2].x - V[0].x, P.x - V[0].x};
    glm::vec3 b = {V[1].y - V[0].y, V[2].y - V[0].y, P.y - V[0].y};
    glm::vec3 c = glm::cross(a, b);
    c /= c.z;
    return {c.x >= 0 && c.y >= 0 && (1 - c.x - c.y) > 0, c};
}

float Triangle::getZValue(const std::vector<glm::vec4>& V, const glm::vec3& barycentricCoor) {
    glm::vec4 P = V[0] * barycentricCoor.x + V[1] * barycentricCoor.y + V[2] * barycentricCoor.z;
    return P.z;
}