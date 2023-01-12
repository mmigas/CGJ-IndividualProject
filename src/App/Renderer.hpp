#pragma once

#include <unordered_map>
#include "Scene.hpp"
#include "../textures/SkyBox.hpp"

class Renderer {

    Scene &scene;
    std::unordered_map<mgl::ShaderType, std::shared_ptr<mgl::ShaderProgram>> shaderPrograms;
    SkyBox skybox{};

    GLuint materialsUBO;
public:
    Renderer();

    void init();

    void createShaderPrograms();

    void loadSkyBox(const std::string &skyboxFolder);

    void draw();

private:
    void createShaderProgram(mgl::ShaderType, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void createSkyBoxShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void drawScene();

    void drawSkyBox();

    void drawChildren(Object &object);

    void drawObject(Object &object);
};
