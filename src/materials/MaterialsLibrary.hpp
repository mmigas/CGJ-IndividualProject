#pragma once

#include <unordered_map>
#include <string>
#include "Material.hpp"

class MaterialsLibrary {
private:
    friend class SceneSerializer;
    MaterialsLibrary() = default;

    static MaterialsLibrary instance;
    std::unordered_map<std::string, Material *> materials;
    int latestID = 0;

    void loadMaterial(int id, const std::string &name, glm::vec3 color, float shininess, float reflectiveness, bool transparent, mgl::ShaderType shaderType);

    void addMaterial(const std::string &name, Material *material);

public:

    void createMaterial(const std::string &name, glm::vec3 color);

    void createMaterial(const std::string &name, glm::vec3 color, float shininess, float reflectiveness, bool transparent, mgl::ShaderType shaderType);

    int getMaterialID(const std::string &name);

    Material *getMaterial(int id);

    std::unordered_map<std::string, Material *> &getMaterials();

    static MaterialsLibrary &getInstance();

    void clear();
};
