#pragma once

#include <unordered_map>
#include <string>
#include "Material.hpp"

class MaterialsLibrary {
private:
    MaterialsLibrary() = default;

    static MaterialsLibrary instance;
    std::unordered_map<std::string, Material *> materials;
    int latestID = 0;

    void addMaterial(const std::string &name, Material *material);

public:

    void createMaterial(const std::string &name, glm::vec4 color, mgl::ShaderType shaderType);

    int getMaterialID(const std::string &name);

    Material *getMaterial(int id);

    static MaterialsLibrary &getInstance();
};
