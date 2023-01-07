#pragma once

#include "../mgl/mglMesh.hpp"
#include "../mgl/mgl.hpp"
#include "../materials/Material.hpp"

class Entity {
private:
    mgl::Mesh *mesh;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    int materialID;
    Material *material;
    GLint modelMatrixID;
    glm::mat4 modelMatrix{1};

public:

    Entity(const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID);

    void move(glm::vec3 position);

    void rotate(glm::vec3 radians);

    void setScale(glm::vec3 scale);

    void draw();

    void createShaderPrograms();

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

    glm::vec3 getPosition();

    glm::vec3 getRotation();
};
