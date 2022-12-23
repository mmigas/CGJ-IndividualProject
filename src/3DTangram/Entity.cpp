#include "Entity.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>


Entity::Entity(const std::string &meshFilePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
        : position(position), rotation(rotation), scale(scale), material(color) {
    mesh = new mgl::Mesh();
    mesh->joinIdenticalVertices();
    mesh->create(meshFilePath, color);
    createShaderPrograms();
}


void Entity::move(glm::vec3 position) {
    this->position = position;
}

void Entity::rotate(glm::vec3 radians) {
    this->rotation = radians;
}

void Entity::setScale(glm::vec3 scale) {
    this->scale = scale;
}

glm::mat4 Entity::getModelMatrix() {
    return glm::translate(glm::mat4(1), position) *
           glm::toMat4(glm::quat(glm::radians(rotation))) *
           glm::scale(glm::mat4(1), scale);
}

void Entity::draw() {
    if (mesh->initialized) {
        shaders->bind();
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
        mesh->draw();
        shaders->unbind();
    }
}

mgl::Mesh &Entity::getMesh() {
    return *mesh;
}

void Entity::createShaderPrograms() {
    shaders = new mgl::ShaderProgram();
    shaders->addShader(GL_VERTEX_SHADER, "resources/shaders/cube-vs.glsl");
    shaders->addShader(GL_FRAGMENT_SHADER, "resources/shaders/cube-fs.glsl");

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
    shaders->addUniformBlock(mgl::MATERIAL_BLOCK, mgl::CAMERA_BLOCK_BINDING_POINT);
    shaders->create();

    modelMatrixID = shaders->Uniforms[mgl::MODEL_MATRIX].index;
}
