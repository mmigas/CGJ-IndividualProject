#pragma once

#include <string>
#include <vector>
#include "GL/glew.h"

class SkyBox {
private:
    GLuint textureID;

    GLuint vao;
    GLuint vbo;

    void loadCubeMapFaces(std::vector<std::string> faces);

public:
    void init();

    void loadCubeMap(const std::string &skyboxFolder);

    void draw();
};
