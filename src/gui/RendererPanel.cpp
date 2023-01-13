#include <cstdint>
#include "RendererPanel.hpp"
#include "imgui.h"

Renderer &RendererPanel::getRenderer() {
    return renderer;
}

void RendererPanel::onUpdate() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Renderer");
    ImVec2 wsize = ImGui::GetContentRegionAvail();
    renderer.getFramebuffer().resize(wsize.x, wsize.y);
    Scene::getInstance().getCamera()->resize(wsize.x, wsize.y);
    renderer.getFramebuffer().bind();
    renderer.draw();
    renderer.getFramebuffer().unBind();
    uint64_t textureID = renderer.getFramebuffer().getColorAttachmentRenderer();
    ImGui::Image(reinterpret_cast<void *>(textureID), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::PopStyleVar();
}
