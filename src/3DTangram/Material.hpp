#pragma once

#include "glm/glm.hpp"

class Material {
private:
    glm::vec4 color;

public:
    Material(const glm::vec4 &color);

    const glm::vec4 &getColor();
};
