#pragma once

#include "glm/glm.hpp"
#include "../mgl/mglShader.hpp"
#include "../mgl/mglConventions.hpp"

class Material {
private:
    const int id;
    glm::vec4 color;
    mgl::ShaderType shaderType;

public:
    mgl::ShaderProgram *shaders;

    Material(int id, const glm::vec4 &color, mgl::ShaderType shaderType);

    const glm::vec4 &getColor();

    int getID() const;

    void bind();

    void unbind();

};
