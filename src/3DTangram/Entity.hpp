#pragma once

#include "../mgl/mglMesh.hpp"
#include "../mgl/mgl.hpp"

class Entity {
private:
    mgl::Mesh* mesh;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;
    glm::vec3 keyframe1Position;
    glm::vec3 keyframe1Rotation;
    glm::vec3 keyframe2Position;
    glm::vec3 keyframe2Rotation;

    mgl::ShaderProgram *shaders;

    GLint modelMatrixID;
    glm::mat4 modelMatrix{1};
    const GLuint &UBO_BP;

public:

    Entity(const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, const GLuint &UBO_BP, glm::vec3 altPosition, glm::vec3 altRotation);

    void move(glm::vec3 position);

    void rotate(glm::vec3 radians);

    void setScale(glm::vec3 scale);

    void draw();

    void createShaderPrograms();

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

    glm::vec3 getStartPosition();

    glm::vec3 getStartRotation();

    glm::vec3 getEndPosition();

    glm::vec3 getEndRotation();

};
