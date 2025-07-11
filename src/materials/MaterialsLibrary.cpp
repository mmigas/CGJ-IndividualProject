#include <iostream>
#include "MaterialsLibrary.hpp"

void MaterialsLibrary::createMaterial(const std::string &name, glm::vec3 color) {
    addMaterial(name, new Material(latestID, color));
    latestID++;
}

void MaterialsLibrary::createMaterial(const std::string &name, glm::vec3 color, float shininess, float reflectiveness, bool transparent, mgl::ShaderType shaderType) {
    addMaterial(name, new Material(latestID, color, shininess, reflectiveness, transparent, shaderType));
    latestID++;
}

void MaterialsLibrary::loadMaterial(int id, const std::string &name, glm::vec3 color, float shininess, float reflectiveness, bool transparent, mgl::ShaderType shaderType) {
    addMaterial(name, new Material(id, color, shininess, reflectiveness, transparent, shaderType));
    latestID = latestID > id ? latestID : id;
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

std::unordered_map<std::string, Material *> &MaterialsLibrary::getMaterials() {
    return materials;
}

void MaterialsLibrary::clear() {
    for (auto &pair: materials) {
        delete pair.second;
    }
    materials.clear();
}


MaterialsLibrary MaterialsLibrary::instance;
