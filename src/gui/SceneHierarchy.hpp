#pragma once

#include "../scene/Scene.hpp"

class SceneHierarchy {
public:
    void onUpdate();

    void drawEntityNode(std::shared_ptr<Object> object);

    std::shared_ptr<Object> selectedGO = nullptr;
};
