#pragma once

#include "screen.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>


namespace Engine {
    class Camera {
    private:
        glm::vec3 location;
        glm::vec3 direction;
        glm::mat4 transformMatrix;
        void computeMatrix();

    public:
        Camera(glm::vec3 loc, glm::vec3 dir);
        Camera() = delete;

        void changeLocation(glm::vec3 delta);
        void changeDirection(glm::vec3 delta);

        glm::mat4 getCameraTransformMatrix() const;
    };
}
