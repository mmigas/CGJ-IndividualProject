#include "Material.hpp"

Material::Material(int id, const glm::vec4 &color, mgl::ShaderType shaderType) : id(id), color(color), shaderType(shaderType) {

}

const glm::vec4 &Material::getColor() {
    return color;
}

int Material::getID() const {
    return id;
}

void Material::bind() {
    shaders->bind();
}

void Material::unbind() {
    shaders->unbind();
}


