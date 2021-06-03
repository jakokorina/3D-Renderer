#pragma once

#include "screen.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>


namespace Engine {
    class Camera {
    private:
        glm::vec3 location;
        glm::vec3 direction;
        glm::mat4 transformMatrix{};
        glm::mat4 computeBasis();
        static glm::mat4 computeTranslation(const glm::vec3& vec);

    public:
        Camera(glm::vec3 loc, glm::vec3 dir);
        Camera() = delete;

        void changeLocation(glm::vec3 delta);
        void changeDirection(glm::vec3 deltaPhi);

        glm::mat4 getCameraTransformMatrix() const;
    };
}
