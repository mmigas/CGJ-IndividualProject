#include "Object.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../../materials/MaterialsLibrary.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <utility>

Object::Object(std::string name, std::string meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID)
        : name(std::move(name)), meshFilePath(std::move(meshFilePath)), Entity(position, rotation, scale) {
    mesh = new mgl::Mesh();
    mesh->joinIdenticalVertices();
    mesh->create(this->meshFilePath, materialID);
    material = MaterialsLibrary::getInstance().getMaterial(materialID);
}

void Object::draw(GLuint &materialUBO) {
    if (mesh->initialized) {
        material->bind(materialUBO);
        mesh->draw();
    }
}

void Object::makeParent(std::shared_ptr<Object> parent) {
    this->parent = parent;
}

void Object::addChild(std::shared_ptr<Object> child) {
    child->makeParent(shared_from_this());
    children.emplace_back(child);
}

glm::mat4 Object::getModelMatrix() {
    std::shared_ptr<Object> parent = this->parent;
    glm::vec3 globalPosition = this->position;
    glm::vec3 globalRotation = this->rotation;
    glm::vec3 globalScale = this->scale;
    while (parent != nullptr) {
        globalPosition += parent->position;
        globalRotation += parent->rotation;
        globalScale += parent->scale;
        parent = parent->parent;
    }
    modelMatrix = glm::translate(glm::mat4(1), globalPosition) *
                  glm::toMat4(glm::quat(glm::radians(rotation))) *
                  glm::scale(glm::mat4(1), scale);
    return modelMatrix;
}

Material *Object::getMaterial() {
    return material;
}

std::string &Object::getName() {
    return name;
}

std::vector<std::shared_ptr<Object>> &Object::getChildren() {
    return children;
}

bool Object::hasChildren() {
    return !children.empty();
}

void Object::clearChildren() {
    if (!children.empty()) {
        for (std::shared_ptr<Object> object: children) {
            object->clearChildren();
            children.clear();
        }
    }
}

const glm::vec3 &Object::getRotation() {
    return rotation;
}




