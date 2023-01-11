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
    ImGuiTreeNodeFlags flags = 0;
    if (selectedGO != nullptr) {
        //flags = ((selectedGO->getName() == object.getName()) ? ImGuiTreeNodeFlags_Selected : 0);
        /*(object->getChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0) |*/
    }

    bool opened = ImGui::TreeNodeEx(&object, flags, "%s", name.c_str());
    if (ImGui::IsItemClicked()) {
        selectedGO = &object;
    }
/*
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Make Child")) {
            GameObject *child = new QuadMeshTest(object->getName() + "'s Child");
            Scene::getInstance().makeChildTo(object, child);
        }
        if (ImGui::MenuItem("Duplicate")) {
            new QuadMeshTest(object->getName() + "'s duplicate", object);
        }
        if (ImGui::MenuItem("Delete GameObject")) {
            TechEngineCore::EventDispatcher::getInstance().dispatch(new RequestDeleteGameObject(object));
            TechEngineCore::EventDispatcher::getInstance().dispatch(new OnDeselectGameObjectEvent(object));
            selectedGO = nullptr;
        }

        ImGui::EndPopup();
    }*/

    if (opened) {
/*        for (const auto &pair: object->getChildren()) {
            drawEntityNode(pair.second);
        }*/

        ImGui::TreePop();
    }
    std::cout << object.getName() << " " << opened << std::endl;
}
