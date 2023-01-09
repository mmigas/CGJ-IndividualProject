#include "Material.hpp"
#include "glm/gtc/type_ptr.hpp"

Material::Material(int id, const glm::vec3 &color, float shininess, float reflectiveness, GLuint transparent, mgl::ShaderType shaderType) :
        id(id), color(color), diffuse(color * 0.6f), specular(color * 0.3f), shininess(shininess), reflectiveness(reflectiveness), transparent(transparent), shaderType(shaderType) {
}

const glm::vec3 &Material::getColor() {
    return color;
}

int Material::getID() const {
    return id;
}

void Material::bind(GLuint &uboID) {
    glBindBuffer(GL_UNIFORM_BUFFER, uboID);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(color));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(specular));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2 + sizeof(glm::vec3), sizeof(float), &shininess);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2 + sizeof(glm::vec3) + sizeof(float), sizeof(float), &reflectiveness);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2 + sizeof(glm::vec3) + 2 * sizeof(float), sizeof(GLuint), &transparent);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

const mgl::ShaderType &Material::getShaderType() {
    return shaderType;
}


