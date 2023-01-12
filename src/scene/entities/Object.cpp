#include "Object.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../../materials/MaterialsLibrary.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <utility>

Object::Object(std::string name, const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int materialID)
        : name(std::move(name)), materialID(materialID), Entity(position, rotation, scale) {
    mesh = new mgl::Mesh();
    mesh->joinIdenticalVertices();
    mesh->create(meshFilePath, materialID);
    material = MaterialsLibrary::getInstance().getMaterial(materialID);
    createShaderPrograms();
}

void Object::draw(GLuint &materialUBO) {
    if (mesh->initialized) {
        material->bind(materialUBO);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
        mesh->draw();
    }
}

void Object::createShaderPrograms() {
    mgl::ShaderProgram *shaders = new mgl::ShaderProgram();
    shaders->addShader(GL_VERTEX_SHADER, "resources/shaders/light-vs.glsl");
    shaders->addShader(GL_FRAGMENT_SHADER, "resources/shaders/light-fs.glsl");

    shaders->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);
    if (getMesh().hasNormals()) {
        shaders->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);
    }
    if (getMesh().hasTexcoords()) {
        shaders->addAttribute(mgl::TEXCOORD_ATTRIBUTE, mgl::Mesh::TEXCOORD);
    }
    if (getMesh().hasTangentsAndBitangents()) {
        shaders->addAttribute(mgl::TANGENT_ATTRIBUTE, mgl::Mesh::TANGENT);
    }

    shaders->addUniform(mgl::MODEL_MATRIX);
    shaders->addUniformBlock(mgl::CAMERA_BLOCK, mgl::CAMERA_BLOCK_BINDING_POINT);
    shaders->addUniformBlock(mgl::MATERIAL_BLOCK, mgl::MATERIAL_BLOCK_BINDING_POINT);
    shaders->create();

    modelMatrixID = shaders->Uniforms[mgl::MODEL_MATRIX].index;
    material->shaders = shaders;
}

void Object::makeParent(Object &parent) {
    this->parent = &parent;
}

void Object::addChild(Object child) {
    child.makeParent(*this);
    children.emplace_back(child);
}

glm::mat4 Object::getModelMatrix() {
    Object *parent = this->parent;
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

mgl::Mesh &Object::getMesh() {
    return *mesh;
}

Material *Object::getMaterial() {
    return material;
}

std::string Object::getName() {
    return name;
}

std::vector<Object>& Object::getChildren() {
    return children;
}


