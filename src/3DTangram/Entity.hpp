#pragma once

#include "../mgl/mglMesh.hpp"
#include "../mgl/mgl.hpp"
#include "Material.hpp"

class Entity {
private:
    mgl::Mesh *mesh;
    Material material;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    mgl::ShaderProgram *shaders;

    GLint modelMatrixID;
    glm::mat4 modelMatrix{1};

public:

    Entity(const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);

    void move(glm::vec3 position);

    void rotate(glm::vec3 radians);

    void setScale(glm::vec3 scale);

    void draw();

    void createShaderPrograms();

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

};
