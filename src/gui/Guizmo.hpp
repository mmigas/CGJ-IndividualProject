#pragma once

#include <imGuizmo.h>
#include "../scene/entities/Object.hpp"

class Guizmo {
private:
    GLFWwindow *window;
public:

    void editTransform(ImGuiContext *context, std::shared_ptr<Object> selectedObject);
};
