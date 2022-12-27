#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <iostream>

#include "mglCamera.hpp"
#include "mglConventions.hpp"

namespace mgl {

///////////////////////////////////////////////////////////////////////// Camera

    Camera::Camera(int width, int height,GLuint UboId, glm::vec3 eye, glm::vec3 lookat, glm::vec3 up)
            : UboId(UboId),ViewMatrix(glm::mat4(1.0f)), ProjectionMatrix(glm::mat4(1.0f)), width(width), height(height), m_eye(eye), m_lookAt(lookat), m_upVector(up) {
        aspectRatio = (float) width / (float) height;
        updateMatrices();
    }

    Camera::~Camera() {
    }

    void Camera::SetCameraView(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up) {
        m_eye = eye;
        m_lookAt = lookat;
        m_upVector = up;
        updateViewMatrix();
    }

    void Camera::changeMode() {
        isOrtho = !isOrtho;
        updateProjectionMatrix();
    }

    void Camera::updateZoom(float zoom) {
        if (isOrtho) {
            if (zoom <= 0.0f)
                orthoLimit = orthoLimit / -(0.9 * zoom);
            else
                orthoLimit = orthoLimit * (0.9 * zoom);
            updateProjectionMatrix();
        } else {
            FoV = FoV - zoom;
            updateProjectionMatrix();
        }
    }

    void Camera::updateMatrices() {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void Camera::updateViewMatrix() {
        ViewMatrix = glm::lookAt(m_eye, m_lookAt, m_upVector);
        glBindBuffer(GL_UNIFORM_BUFFER, UboId);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ViewMatrix));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void Camera::updateProjectionMatrix() {
        if (isOrtho) {
            ProjectionMatrix = glm::ortho<float>(-orthoLimit * aspectRatio, orthoLimit * aspectRatio, -orthoLimit * aspectRatio, orthoLimit * aspectRatio, -20.0f, 20.0f);
        } else {
            ProjectionMatrix = glm::perspective<float>(glm::radians(FoV), aspectRatio, 0.1f, 20.0f);
        }
        glBindBuffer(GL_UNIFORM_BUFFER, UboId);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ProjectionMatrix));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    glm::vec3 Camera::GetEye() const {
        return m_eye;
    }

    glm::vec3 Camera::GetUpVector() const {
        return m_upVector;
    }

    glm::vec3 Camera::GetLookAt() const {
        return m_lookAt;
    }

    int Camera::GetWidth() const {
        return width;
    }

    int Camera::GetHeight() const {
        return height;
    }

    glm::vec3 Camera::GetViewDir() const {
        return -glm::transpose(ViewMatrix)[2];
    }

    glm::vec3 Camera::GetRightVector() const {
        return glm::transpose(ViewMatrix)[0];
    }

    void Camera::resize(int width, int height) {
        this->width = width;
        this->height = height;
        aspectRatio = (float) width / (float) height;
        updateProjectionMatrix();
    }

////////////////////////////////////////////////////////////////////////////////
} // namespace mgl
