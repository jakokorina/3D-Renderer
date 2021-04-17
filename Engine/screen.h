#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <utility>
#include <vector>

class Screen {
    int height, width;
    float far = 10.0f, near = 0.5f;
    float left = -2, right = 2, top = 1, bottom = -1;
    std::vector<std::vector<sf::Color>> colourBuf;
    std::vector<std::vector<float>> zBuf;

public:
    Screen(int h, int w);
    std::pair<size_t, size_t> getSize() const;
    glm::mat4 getProjectionMatrix() const;
    void setColour(sf::Color colour, size_t x, size_t y, float z);
    void screenToWindow(sf::RenderWindow& window);
    void clear();
    glm::mat4 getVeiwOrtMatrix() const;
};

std::pair<size_t, size_t> Screen::getSize() const {
    return std::pair<size_t, size_t>(height, width);
}

glm::mat4 Screen::getProjectionMatrix() const {
    glm::mat4 projection(near);
    projection[2][2] = (far + near) / (far - near);
    projection[3][3] = 0;
    projection[2][3] = -1;
    projection[3][2] = 2 * far * near / (far - near);
    return projection;
}

void Screen::setColour(sf::Color colour, size_t x, size_t y, float z) {
    assert(x < width && y < height);
    if (z < -1 || z > 1) {
        return;
    }
    if (z < zBuf[x][height - 1 - y]) { // height - 1 - y т.к. у экрана y смотрит вниз
        zBuf[x][height - 1 - y] = z;
        colourBuf[x][height - 1 - y] = colour;
    }
}

void Screen::screenToWindow(sf::RenderWindow& window) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            sf::RectangleShape pixel;
            pixel.setSize({1.f, 1.f});
            pixel.setPosition({(float) x, (float) y});
            pixel.setFillColor(colourBuf[x][y]);
            window.draw(pixel);
        }
    }
}

void Screen::clear() {
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j) {
            colourBuf[i][j] = sf::Color::Black;
            zBuf[i][j] = 2;
        }
}

glm::mat4 Screen::getVeiwOrtMatrix() const {
    glm::mat4 veiwPort(1);
    veiwPort[3][0] = (width - 1) / 2.f;
    veiwPort[3][1] = (height - 1) / 2.f;
    veiwPort[0][0] = width / 2.f;
    veiwPort[1][1] = height / 2.f;
    glm::mat4 ort(1);
    ort[0][0] = 2.f / (right - left);
    ort[1][1] = 2.f / (top - bottom);
    ort[2][2] = 2.f / (far - near);
    ort[3][0] = -(right + left) / (right - left);
    ort[3][1] = -(top + bottom) / (top - bottom);
    ort[3][2] = (near + far) / (far - near);
    return veiwPort * ort;
}

Screen::Screen(int h, int w): height(h), width(w) {
    colourBuf = std::vector<std::vector<sf::Color>>(w, std::vector<sf::Color>(h, sf::Color::Black));
    zBuf = std::vector<std::vector<float>>(w, std::vector<float>(h, far + 1));
}
