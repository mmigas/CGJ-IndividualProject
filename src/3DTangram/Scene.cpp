#include <filesystem>
#include "Scene.hpp"

Scene::Scene() {
}


void Scene::init(mgl::Camera *camera) {
    this->camera = camera;
}

void Scene::createEntity(const std::string &meshFile, int materialID) {
    createEntity(meshFile, materialID, glm::vec3(0), glm::vec3(0), glm::vec3(1));
}

void Scene::createEntity(const std::string &meshFile, int materialID, glm::vec3 position) {
    createEntity(meshFile, materialID, position, glm::vec3(0), glm::vec3(1));
}

void Scene::createEntity(const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    std::string modelsPath = std::filesystem::current_path().string() + "/resources/models/";
    std::string meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, position, rotation, scale, materialID);
}

void Scene::drawScene() {
    for (Entity &entity: entities) {
        entity.draw();
    }
}


mgl::Camera *Scene::getCamera() {
    return camera;
}



