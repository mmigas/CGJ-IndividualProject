#pragma once

#include "../mgl/mglMesh.hpp"
#include "../mgl/mgl.hpp"
#include "../materials/Material.hpp"
#include "Entity.hpp"

class Object : public Entity {
private:
    mgl::Mesh *mesh;
    int materialID;
    Material *material;

public:

    Object(const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID);

    void draw(GLuint &materialUBO);

    void createShaderPrograms();

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

    Material* getMaterial();
};
