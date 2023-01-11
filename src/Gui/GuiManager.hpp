#pragma once

#include <imgui.h>
#include "SceneHierarchy.hpp"

class GuiManager {
private:
    ImGuiContext *imguiContext;
    SceneHierarchy sceneHierarchy;
public:
    void initImGui(GLFWwindow *win);

    void beginImGuiFrame();

    void endImGuiFrame();

    void createDockSpace();

    void createMenuBar();

    void update();
};
