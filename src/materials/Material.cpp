#include "Material.hpp"
#include "glm/gtc/type_ptr.hpp"

Material::Material(int id, const glm::vec3 &color, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, mgl::ShaderType shaderType) :
        id(id), color(color), diffuse(diffuse), specular(specular), shininess(shininess), shaderType(shaderType) {
    glGenBuffers(1, &UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4) + sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, mgl::MATERIAL_BLOCK_BINDING_POINT, UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

const glm::vec3 &Material::getColor() {
    return color;
}

int Material::getID() const {
    return id;
}

void Material::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(color));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(specular));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2 + sizeof(glm::vec3), sizeof(float), &shininess);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

const mgl::ShaderType &Material::getShaderType() {
    return shaderType;
}


