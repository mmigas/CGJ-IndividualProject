#pragma once

#include "Entity.hpp"
#include "../../mgl/mglMesh.hpp"
#include "../../materials/Material.hpp"

class Object : public Entity {
private:
    std::string name;
    mgl::Mesh *mesh;
    int materialID;
    Material *material;
    Object *parent = nullptr;
    std::vector<Object> children;
public:
    Object(std::string name, const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID);

    void draw(GLuint &materialUBO);

    void createShaderPrograms();

    void makeParent(Object &parent);

    void addChild(Object child);

    glm::mat4 getModelMatrix();

    mgl::Mesh &getMesh();

    Material *getMaterial();

    std::string getName();

    std::vector<Object> &getChildren();
};
