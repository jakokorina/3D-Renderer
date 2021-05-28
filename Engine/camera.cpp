#include "camera.h"

namespace Engine {
    Camera::Camera(glm::vec3 loc, glm::vec3 dir) : location(loc), direction(dir) {
        direction /= direction.length();
        computeMatrix();
    }

    void Camera::changeLocation(glm::vec3 delta) {
        location += delta;
        computeMatrix();
    }
    void Camera::changeDirection(glm::vec3 delta) {
        direction = delta;
        computeMatrix();
    }

    glm::mat4 Camera::getCameraTransformMatrix() const {
        return transformMatrix;
    }

    void Camera::computeMatrix() {
        glm::vec3 viewUpVector = glm::vec3{0, 1.f, 0};
        std::vector<glm::vec3> orthonormalCameraBasis(3);
        orthonormalCameraBasis[2] = -direction;
        orthonormalCameraBasis[0] = glm::cross(direction, viewUpVector);
        orthonormalCameraBasis[1] = glm::cross(orthonormalCameraBasis[0], direction);
        for (auto& vec : orthonormalCameraBasis) {
            vec /= vec.length();
        }
        // orthonormalCameraBasis[0] = -orthonormalCameraBasis[0];
        glm::mat4 transform = glm::mat4(0.f);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                transform[j][i] = orthonormalCameraBasis[i][j];
            }
        }
        transform[3][3] = 1.f;
        glm::mat4 translation = glm::mat4(1.f);
        for (int i = 0; i < 3; ++i) {
            translation[3][i] = -location[i];
        }
        transformMatrix = transform * translation;
    }
}
