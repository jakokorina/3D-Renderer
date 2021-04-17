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
    static std::pair<bool, float> barycentricCoordinates(const std::vector<glm::vec4>& V, const glm::vec2& P);

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
    if (newPoints[0].x == newPoints[1].x && newPoints[0].x == newPoints[2].x) {
        return; // треугольники, стоящие перпендиклярно камере, не интересны #2
    }
    /*for (int i = 0; i < 3; ++i) {
        std::cout << newPoints[i].x << " "<< newPoints[i].y << " " << newPoints[i].z << '\n';
    }*/
    auto[h, w] = screen.getSize();
    float left = std::min({newPoints[0].x, newPoints[1].x, newPoints[2].x}), right = std::max(
            {newPoints[0].x, newPoints[1].x, newPoints[2].x});
    float bottom = std::min({newPoints[0].y, newPoints[1].y, newPoints[2].y}), top = std::max(
            {newPoints[0].y, newPoints[1].y, newPoints[2].y});
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            if (x < left || y < bottom || x > right || y > top) {
                continue;
            } // точка не попадает в минимальный прямоугольник, содержащий наш треугольник
            auto[inTriangle, zValue] = barycentricCoordinates(newPoints, glm::vec2{x, y});
            if (inTriangle) {
                screen.setColour(colour, x, y, zValue);
            }
        }
    }
}

std::pair<bool, float> Triangle::barycentricCoordinates(const std::vector<glm::vec4>& V, const glm::vec2& P) {
    glm::vec3 a = {V[1].x - V[0].x, V[2].x - V[0].x, V[0].x - P.x};
    glm::vec3 b = {V[1].y - V[0].y, V[2].y - V[0].y, V[0].y - P.y};
    glm::vec3 c = glm::cross(a, b);
    c /= c.z;
    c.z = 1 - c.x - c.y;
    glm::vec4 point = c.z * V[0] + c.x * V[1] + c.y * V[2];
    return {c.x >= 0 && c.y >= 0 && c.z >= 0, point.z};
}
