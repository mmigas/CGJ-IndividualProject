#include <filesystem>
#include "Scene.hpp"

void Scene::init(mgl::Camera *camera) {
    this->camera = camera;
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID, const std::string &parent) {
    createEntity(name, meshFile, materialID, glm::vec3(0), glm::vec3(0), glm::vec3(1), parent);
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, const std::string &parent) {
    createEntity(name, meshFile, materialID, position, glm::vec3(0), glm::vec3(1), parent);
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string &parent) {
    std::string modelsPath = std::filesystem::current_path().string() + "/resources/models/";
    std::string meshFullname = modelsPath + meshFile;
    if (parent.empty()) {
        objects.emplace_back(name, meshFullname, position, rotation, scale, materialID);
    } else {
        addChildTo(parent, Object(name, meshFullname, position, rotation, scale, materialID));
    }
}

void Scene::createLight(glm::vec3 position, glm::vec3 color, float intensity) {
    light = std::make_shared<Light>(position, color, intensity);
}

Object *Scene::searchObjectByNameinChildren(Object &parent, const std::string &name) {
    for (Object &object: parent.getChildren()) {
        if (object.getName() == name) {
            return &object;
        }
        searchObjectByNameinChildren(object, name);
    }
    return nullptr;
}

Object *Scene::searchObjectByName(const std::string &name) {
    for (Object &object: objects) {
        if (object.getName() == name) {
            return &object;
        }
        searchObjectByNameinChildren(object, name);
    }
    return nullptr;
}

void Scene::addChildTo(const std::string &parentName, const Object &child) {
    Object *object = searchObjectByName(parentName);
    if (object == nullptr) {
        std::cout << parentName << " not found" << std::endl;
    } else {
        object->addChild(child);
    }
}

mgl::Camera *Scene::getCamera() {
    return camera;
}

std::vector<Object> &Scene::getObjects() {
    return objects;
}

Scene &Scene::getInstance() {
    return instance;
}

std::shared_ptr<Light> Scene::getLight() {
    return light;
}

Scene Scene::instance;

