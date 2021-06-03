#include "screen.h"

namespace Engine {
    Screen::Screen(int h, int w) : height(h), width(w) {
        colourBuf = std::vector<std::vector<sf::Color>>(w, std::vector<sf::Color>(h, sf::Color::Black));
        zBuf = std::vector<std::vector<float>>(w, std::vector<float>(h, far + 1));
        screenMatrix = computeViewOrt() * computeProjection();
    }

    std::pair<int, int> Screen::getSize() const {
        return std::pair<size_t, size_t>(height, width);
    }

    glm::mat4 Screen::getScreenMatrix() const {
        return screenMatrix;
    }

    void Screen::setColour(sf::Color colour, size_t x, size_t y, float z) {
        assert(x < width && y < height);
        if (z < -1 || z > 1) {
            return;
        }
        y = height - 1 - y;  // т.к. у экрана ось y направлена вниз
        mutex.lock();
        if (z < zBuf[x][y]) { // height - 1 - y
            zBuf[x][y] = z;
            colourBuf[x][y] = colour;
        }
        mutex.unlock();
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

    glm::mat4 Screen::computeViewOrt() const {
        glm::mat4 viewport(1);
        viewport[3][0] = (width - 1) / 2.f;
        viewport[3][1] = (height - 1) / 2.f;
        viewport[0][0] = width / 2.f;
        viewport[1][1] = height / 2.f;
        glm::mat4 ort(1);
        ort[0][0] = 2.f / (right - left);
        ort[1][1] = 2.f / (top - bottom);
        ort[2][2] = -1;
        ort[3][0] = -(right + left) / (right - left);
        ort[3][1] = -(top + bottom) / (top - bottom);
        return viewport * ort;
    }
    glm::mat4 Screen::computeProjection() const {
        glm::mat4 projection(near);
        projection[2][2] = (far + near) / (far - near);
        projection[3][3] = 0;
        projection[2][3] = -1;
        projection[3][2] = 2 * far * near / (far - near);
        return projection;
    }
    int Screen::inViewFrustrum(const glm::vec4& vec) const {
        if (vec.z >= near) {
            return 1;
        } else if (vec.z <= far) {
            return -1;
        } else {
            return 0;
        }
    }
}
