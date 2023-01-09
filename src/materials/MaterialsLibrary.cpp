#include <iostream>
#include "MaterialsLibrary.hpp"

void MaterialsLibrary::createMaterial(const std::string &name, glm::vec3 color) {
    addMaterial(name, new Material(latestID, color));
    latestID++;
}

void MaterialsLibrary::createMaterial(const std::string &name, glm::vec3 color, float shininess, float reflectiveness, mgl::ShaderType shaderType) {
    addMaterial(name, new Material(latestID, color, shininess, reflectiveness, shaderType));
    latestID++;
}

void MaterialsLibrary::addMaterial(const std::string &name, Material *material) {
    materials[name] = material;
}

int MaterialsLibrary::getMaterialID(const std::string &name) {
    return materials[name]->getID();
}

Material *MaterialsLibrary::getMaterial(const int id) {
    for (auto &entry: materials) {
        if (entry.second->getID() == id) {
            return entry.second;
        }
    }
    std::cout << "Invalid material with: " << id << " id!!" << std::endl;
    return nullptr;
}

MaterialsLibrary &MaterialsLibrary::getInstance() {
    return instance;
}


MaterialsLibrary MaterialsLibrary::instance;
