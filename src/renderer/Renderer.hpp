#pragma once

#include <unordered_map>
#include "../scene/Scene.hpp"
#include "FrameBuffer.hpp"

class Renderer {
    Scene &scene;
    std::unordered_map<mgl::ShaderType, std::shared_ptr<mgl::ShaderProgram>> shaderPrograms;

    GLuint materialsUBO;
    GLFWwindow *win;
    FrameBuffer frameBuffer;
public:
    Renderer();

    void init(GLFWwindow *win);

    void createShaderPrograms();

    void loadSkyBox(const std::string &skyboxFolder);

    void draw();

    FrameBuffer& getFramebuffer();

private:
    void createShaderProgram(mgl::ShaderType, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void createSkyBoxShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void drawScene();

    void drawSkyBox();

    void drawChildren(std::shared_ptr<Object> object);

    void drawObject(std::shared_ptr<Object> object);
};
