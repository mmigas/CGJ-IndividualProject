#pragma once

#include "../App/Scene.hpp"

class SceneHierarchy {
public:
    void onUpdate();

    void drawEntityNode(Object &object);

    Object *selectedGO = nullptr;
};
