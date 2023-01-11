#pragma once

#include "Entity.hpp"
#include "../mgl/mglMesh.hpp"
#include "../materials/Material.hpp"

class Object : public Entity {
private:
    std::string name;
    mgl::Mesh *mesh;
    int materialID;
    Material *material;
public:

    Object(const std::string &name, const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID);

    void draw(GLuint &materialUBO);

    void createShaderPrograms();

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

    Material *getMaterial();

    std::string getName();
};
