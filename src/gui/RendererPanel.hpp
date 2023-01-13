#pragma once


#include "../renderer/Renderer.hpp"

class RendererPanel {
private:
    Renderer renderer;
public:
    Renderer &getRenderer();

    void onUpdate();
};
