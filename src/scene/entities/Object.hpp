#pragma once

#include "Entity.hpp"
#include "../../mgl/mglMesh.hpp"
#include "../../materials/Material.hpp"

class Object : public Entity, std::enable_shared_from_this<Object> {
private:
    friend class SceneSerializer;

    std::string name;
    std::string meshFilePath;
    mgl::Mesh *mesh;
    Material *material;
    std::shared_ptr<Object> parent = nullptr;
    std::vector<std::shared_ptr<Object>> children;
public:
    Object(std::string name, std::string meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID);

    void draw(GLuint &materialUBO);

    void createShaderPrograms();

    void makeParent(std::shared_ptr<Object> parent);

    void addChild(std::shared_ptr<Object> child);

    glm::mat4 getModelMatrix();

    std::string &getName();

    Material *getMaterial();

    std::vector<std::shared_ptr<Object>> &getChildren();

    bool hasChildren();

    void clearChildren();

    const glm::vec3& getRotation();
};
