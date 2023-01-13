#pragma once

#include "glm/glm.hpp"
#include "../mgl/mglShader.hpp"
#include "../mgl/mglConventions.hpp"

class Material {
private:
    friend class SceneSerializer;

    const int id;
    glm::vec3 color;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float reflectiveness;
    GLuint transparent;
    mgl::ShaderType shaderType;

public:
    mgl::ShaderProgram *shaders;

    Material(int id, const glm::vec3 &color, float shininess = 32.0f, float reflectiveness = 0.5f, GLuint transparent = true, mgl::ShaderType shaderType = mgl::ShaderType::light);

    const glm::vec3 &getColor();

    int getID() const;

    void bind(GLuint &uboID);

    const mgl::ShaderType &getShaderType();
};
