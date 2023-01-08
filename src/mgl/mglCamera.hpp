////////////////////////////////////////////////////////////////////////////////
//
// Camera Abstraction Class
//
// (c)2022 by Carlos Martinho
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MGL_CAMERA_HPP
#define MGL_CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace mgl {

///////////////////////////////////////////////////////////////////////// Camera

    class Camera {
    private:
        GLuint UboId = 0;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;

        int width = 0;
        int height = 0;
        float aspectRatio = 0;

        glm::vec3 m_eye; // Camera position in 3D
        glm::vec3 m_lookAt; // Point that the camera is looking at
        glm::vec3 m_upVector; // Orientation of the camera

        float FoV = 45.0f;
        float orthoLimit = 1.0f;
        bool isOrtho = false;

    public:
        Camera(int width, int height, glm::vec3 eye, glm::vec3 lookat, glm::vec3 up);

        ~Camera();

        void setViewMatrix(glm::mat4 viewMatrix);

        void changeMode();

        void updateZoom(float zoom);

        void updateViewMatrix();

        void updateProjectionMatrix();

        void resize(int width, int height);

        glm::vec3 GetEye() const;

        glm::vec3 GetUpVector() const;

        glm::vec3 GetLookAt() const;

        int GetWidth() const;

        int GetHeight() const;

        glm::vec3 GetViewDir() const;

        glm::vec3 GetRightVector() const;

        void updateMatrices();

        void bind();

        glm::mat4 GetViewMatrix();

        glm::mat4 GetProjectionMatrix();


    };

////////////////////////////////////////////////////////////////////////////////
} // namespace mgl

#endif /* MGL_CAMERA_HPP */
