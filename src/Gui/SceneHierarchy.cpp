#include "SceneHierarchy.hpp"
#include <imgui.h>

void SceneHierarchy::onUpdate() {
    ImGui::Begin("Scene Hierarchy");
    if (!Scene::getInstance().getObjects().empty()) {
        for (auto &element: Scene::getInstance().getObjects()) {
            drawEntityNode(element);
        }
    }
    ImGui::End();
}

void SceneHierarchy::drawEntityNode(Object &object) {
    std::string name = object.getName();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (selectedGO != nullptr) {
        flags |= ((selectedGO->getName() == object.getName()) ? ImGuiTreeNodeFlags_Selected : 0) |
                 (object.getChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0);
    }

    bool opened = ImGui::TreeNodeEx(&object, flags, "%s", name.c_str());
    if (ImGui::IsItemClicked()) {
        selectedGO = &object;
    }

    if (opened) {
        for (auto &child: object.getChildren()) {
            drawEntityNode(child);
        }

        ImGui::TreePop();
    }
}
