#pragma once

#include "Entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
private:

    std::vector<Entity> entities;
    float frameCounter = 0.0f;

public:

    void buildTangram();

    void updatePieces(int direction);

    void drawScene();
};
