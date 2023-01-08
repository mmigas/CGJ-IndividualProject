#pragma once

#include <unordered_map>
#include "Scene.hpp"

class Renderer {

    Scene &scene;
    std::unordered_map<mgl::ShaderType, std::shared_ptr<mgl::ShaderProgram>> shaderPrograms;
public:
    Renderer();

    void createShaderPrograms();

    void drawScene();

private:
    void createShaderProgram(mgl::ShaderType, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
};
