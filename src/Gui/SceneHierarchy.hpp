#pragma once

#include "../App/Scene.hpp"

class SceneHierarchy {
private:
    Object *selectedGO = nullptr;
public:
    void onUpdate();

    void drawEntityNode(Object &object);
};
