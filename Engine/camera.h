#pragma once

#include "screen.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

void Camera::setLocation(glm::vec3 new_location) {
    location = new_location;
}
void Camera::setDirection(glm::vec3 new_direction) {
    direction = new_direction;
}

glm::mat4 Camera::getCameraTransformationMatrix() const {
    glm::vec3 viewUpVector = glm::vec3{0,1.f,0};
    std::vector<glm::vec3> orthonormalCameraBasis(3);
    orthonormalCameraBasis[2] = -direction;
    orthonormalCameraBasis[0] = glm::cross(direction, viewUpVector);
    orthonormalCameraBasis[1] = glm::cross(orthonormalCameraBasis[0], direction);
    for (auto& vec : orthonormalCameraBasis) {
        vec /= vec.length();
    }
    // orthonormalCameraBasis[0] = -orthonormalCameraBasis[0];
    glm::mat4 transformMatrix = glm::mat4(0.f);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            transformMatrix[j][i] = orthonormalCameraBasis[i][j];
        }
    }
    transformMatrix[3][3] = 1.f;
    glm::mat4 translation = glm::mat4(1.f);
    for (int i = 0; i < 3; ++i) {
        translation[3][i] = -location[i];
    }
    return transformMatrix * translation;
}
