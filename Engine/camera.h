#pragma once

#include "screen.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Engine {
    class Camera {
    private:
        glm::vec3 location;
        glm::vec3 direction;

    public:
        Camera(glm::vec3 loc, glm::vec3 dir) : location(loc), direction(dir) {}
        Camera() = delete;

        void setLocation(glm::vec3 new_location);
        void setDirection(glm::vec3 new_direction);

        glm::mat4 getCameraTransformationMatrix() const;
    };
}
