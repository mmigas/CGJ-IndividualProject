#include "Material.hpp"
#include "glm/gtc/type_ptr.hpp"

Material::Material(int id, const glm::vec3 &color, mgl::ShaderType shaderType) : id(id), color(color), shaderType(shaderType) {
    glGenBuffers(1, &UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_STREAM_DRAW);
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
    shaders->bind();
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(color));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(specular));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec3), sizeof(glm::vec3), &shininess);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Material::unbind() {
    shaders->unbind();
}


