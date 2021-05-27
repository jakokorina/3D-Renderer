#pragma once

#include <SFML/Graphics.hpp>
#include "triangle.h"
#include "camera.h"
#include "screen.h"
#include <vector>

namespace Engine {

    class Renderer {
    private:
        Camera& camera;
        Screen& screen;

    public:
        Renderer(Screen& scr, Camera& cam) : screen(scr), camera(cam) {}
        void drawObjects(const std::vector<Triangle>& objects, sf::RenderWindow& window);
    };
}
