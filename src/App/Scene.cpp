#include <filesystem>
#include "Scene.hpp"

void Scene::init(mgl::Camera *camera) {
    this->camera = camera;
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID) {
    createEntity(name, meshFile, materialID, glm::vec3(0), glm::vec3(0), glm::vec3(1));
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position) {
    createEntity(name, meshFile, materialID, position, glm::vec3(0), glm::vec3(1));
}

void Scene::createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    std::string modelsPath = std::filesystem::current_path().string() + "/resources/models/";
    std::string meshFullname = modelsPath + meshFile;
    objects.emplace_back(name, meshFullname, position, rotation, scale, materialID);
}

void Scene::createLight(glm::vec3 position, glm::vec3 color, float intensity) {
    light = std::make_shared<Light>(position, color, intensity);
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

