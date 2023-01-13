#pragma once

#include <imgui.h>
#include "SceneHierarchy.hpp"
#include "Guizmo.hpp"
#include <windows.h>

class GuiManager {
private:
    ImGuiContext *imguiContext;
    SceneHierarchy sceneHierarchy;
    Guizmo guizmo;
public:
    void initImGui(GLFWwindow *win);

    void beginImGuiFrame();

    void endImGuiFrame();

    void createDockSpace();

    void createMenuBar();

    void update();

    void openScene();

    std::string openFileWindow(const char *filter);

    std::string saveFile(const char *filter);

    void saveScene();
};
