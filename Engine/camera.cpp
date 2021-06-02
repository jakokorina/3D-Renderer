#include "camera.h"

namespace Engine {
    Camera::Camera(glm::vec3 loc, glm::vec3 dir) : location(loc), direction(dir) {
        computeBasis();
        computeTranslation();
        computeMatrix();
    }

    void Camera::changeLocation(glm::vec3 delta) {
        location += delta;
        computeTranslation();
        computeMatrix();
    }
    void Camera::changeDirection(glm::vec3 deltaPhi) {
        //basisMatrix = glm::rotate(basisMatrix, deltaPhi);
        computeMatrix();
    }

    glm::mat4 Camera::getCameraTransformMatrix() const {
        return transformMatrix;
    }

    void Camera::computeMatrix() {
        transformMatrix = basisMatrix * translationMatrix;
    }

    void Camera::computeBasis() {
        glm::vec3 viewUpVector = glm::vec3{0, 1.f, 0};
        std::vector<glm::vec3> orthonormalCameraBasis(3);
        orthonormalCameraBasis[0] = -glm::cross(direction, viewUpVector);
        orthonormalCameraBasis[1] = -glm::cross(orthonormalCameraBasis[0], direction);
        orthonormalCameraBasis[2] = -direction;
        for (auto& vec : orthonormalCameraBasis) {
            glm::normalize(vec);
        }
        basisMatrix = glm::mat4(1.f);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                basisMatrix[j][i] = orthonormalCameraBasis[i][j];
            }
        }
    }

    void Camera::computeTranslation() {
        translationMatrix = glm::mat4(1.f);
        for (int i = 0; i < 3; ++i) {
            translationMatrix[3][i] = -location[i];
        }
    }
}
