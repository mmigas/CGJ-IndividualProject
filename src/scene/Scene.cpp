#include <filesystem>
#include <memory>
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
        objects.emplace_back(std::make_shared<Object>(name, meshFullname, position, rotation, scale, materialID));
    } else {
        std::shared_ptr<Object> object = searchObjectByName(parent);
        object->getChildren().emplace_back(std::make_shared<Object>(name, meshFullname, position, rotation, scale, materialID));
        object->getChildren().back()->makeParent(object);
    }
}

void Scene::createLight(glm::vec3 position, glm::vec3 color, float intensity) {
    light = std::make_shared<Light>(position, color, intensity);
}

std::shared_ptr<Object> Scene::searchObjectByNameinChildren(std::shared_ptr<Object> parent, const std::string &name) {
    for (std::shared_ptr<Object> object: parent->getChildren()) {
        if (object->getName() == name) {
            return object;
        }
        searchObjectByNameinChildren(object, name);
    }
    return nullptr;
}

std::shared_ptr<Object> Scene::searchObjectByName(const std::string &name) {
    for (std::shared_ptr<Object> object: objects) {
        if (object->getName() == name) {
            return object;
        }
        searchObjectByNameinChildren(object, name);
    }
    return nullptr;
}

void Scene::addChildTo(const std::string &parentName, std::shared_ptr<Object> child) {
    std::shared_ptr<Object> object = searchObjectByName(parentName);
    if (object == nullptr) {
        std::cout << parentName << " not found" << std::endl;
    } else {
        object->addChild(child);
    }
}

mgl::Camera *Scene::getCamera() {
    return camera;
}

std::vector<std::shared_ptr<Object>> &Scene::getObjects() {
    return objects;
}

Scene &Scene::getInstance() {
    return instance;
}

std::shared_ptr<Light> Scene::getLight() {
    return light;
}

void Scene::clear() {
    for (std::shared_ptr<Object> object: objects) {
        object->clearChildren();
    }
    objects.clear();
}

SkyBox &Scene::getSkybox() {
    return skybox;
}

Scene Scene::instance;

