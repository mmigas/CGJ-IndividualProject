#pragma once

#include "../../mgl/mgl.hpp"
#include "glm/glm.hpp"

class Entity {
protected:
    Entity(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 modelMatrix{1};

public:
    void move(glm::vec3 position);

    void rotate(glm::vec3 radians);

    void setScale(glm::vec3 scale);

};
