#include "Light.hpp"
#include "../mgl/mglConventions.hpp"
#include "glm/gtc/type_ptr.hpp"

Light::Light(const glm::vec3 &position, const glm::vec3 &color, float intensity) : Entity(position, glm::vec3(1), glm::vec3(1)), color(color), intensity(intensity) {
    glGenBuffers(1, &UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 4, nullptr, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, mgl::LIGHT_BLOCK_BINDING_POINT, UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

glm::vec3 Light::ambient() {
    return glm::vec3(diffuse() * (0.2f * intensity));
}

glm::vec3 Light::diffuse() {
    return glm::vec3(color * (0.5f * intensity));
}

glm::vec3 Light::specular() const {
    return glm::vec3(intensity);
}

void Light::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER, UboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(position));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(ambient()));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(diffuse()));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 3, sizeof(glm::vec3), glm::value_ptr(specular()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}