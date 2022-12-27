#include <filesystem>
#include "Scene.hpp"

void Scene::buildTangram() {
    std::string modelsPath = std::filesystem::current_path().string() + "/resources/models/";
    std::string meshFile = "RedSquare.obj"; //Parallelogram
    std::string meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), UboBP, glm::vec3(-1.4f, 6.55f, -0.3f), glm::vec3(90.0f, 0.0f, 0.0f));
}

void Scene::updatePieces(int direction) {
    frameCounter = frameCounter + (direction * .006);
    if (frameCounter > 1.0f) frameCounter = 1.0f;
    if (frameCounter < 0.0f) frameCounter = 0.0f;
    for (Entity& entity : entities) {
        entity.move(mix(entity.getStartPosition(), entity.getEndPosition(), frameCounter));
        entity.rotate(mix(entity.getStartRotation(), entity.getEndRotation(), frameCounter));
    }
}

void Scene::drawScene() {
    for (Entity &entity: entities) {
        entity.draw();
    }
}
