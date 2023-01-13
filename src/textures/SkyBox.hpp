#pragma once

#include <string>
#include <vector>
#include "../mgl/mgl.hpp"

class SkyBox {
private:
    friend class SceneSerializer;

    std::string skyboxFolder;
    GLuint textureID;
    GLuint vao;
    GLuint vbo;

    void loadCubeMapFaces(std::vector<std::string> faces);

public:
    void init();

    void loadCubeMap(const std::string &skyboxFolder);

    void draw();
};
