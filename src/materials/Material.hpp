#pragma once

#include "glm/glm.hpp"
#include "../mgl/mglShader.hpp"
#include "../mgl/mglConventions.hpp"

class Material {
private:
    const int id;
    GLuint UboId;
    glm::vec3 color;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    mgl::ShaderType shaderType;

public:
    mgl::ShaderProgram *shaders;

    Material(int id, const glm::vec3 &color, mgl::ShaderType shaderType);

    const glm::vec3 &getColor();

    int getID() const;

    void bind();

    void unbind();

};
