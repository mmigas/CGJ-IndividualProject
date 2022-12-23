#include <filesystem>
#include "Scene.hpp"

void Scene::buildTangram() {
    std::string modelsPath = std::filesystem::current_path().string() + "/resources/models/";
    std::string meshFile = "Parallelogram.obj"; //Parallelogram
    std::string meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(0.93f, 0.0f, -2.6f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), UboBP, glm::vec3(-1.4f, 6.55f, -0.3f), glm::vec3(90.0f, 0.0f, 0.0f));
    meshFile = "GreenTriangle.obj";             //Medium Triangle
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(-1.9f, 0.0f, -2.3f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), UboBP, glm::vec3(-1.2f, 4.3f, 0.0f), glm::vec3(90.0f, 180.0f, -90.0f));
    meshFile = "LightBlueTriangle.obj";         //Bottom Small Triangle 
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(1.6f, 0.0f, -4.9f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.34f, 1.0f, 1.0f), UboBP, glm::vec3(1.7f, 3.8f, 0.0f), glm::vec3(90.0f, 180.0f, -90.0f));
    meshFile = "OrangeTriangle.obj";            //Big Triangle 1
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(-0.8f, 0.0f, -0.2f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.83f, 0.0f, 1.0f), UboBP, glm::vec3(2.2f, 6.0f, 0.0f), glm::vec3(90.0f, -180.0f, -90.0f));
    meshFile = "RedSquare.obj";                 //Square
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(0.45f, 0.0f, 3.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), UboBP, glm::vec3(0.45f, 4.7f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f));
    meshFile = "YellowTriangle.obj";            //Left small triangle
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(-4.1f, 0.0f, -2.5f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), UboBP, glm::vec3(-0.35f, 6.0f, 0.0f), glm::vec3(90.0f, 180.0f, -90.0f));
    meshFile = "OrangeTriangle2.obj";           //replace with new object when possible     //Big triangle 2
    meshFullname = modelsPath + meshFile;
    entities.emplace_back(meshFullname, glm::vec3(1.25f, 0.0f, 0.45f), glm::vec3(0.0f, -135.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.83f, 0.0f, 1.0f), UboBP, glm::vec3(0.45f, 7.8f, 0.0f), glm::vec3(90.0f, 180.0f, 0.0f));
}

void Scene::updatePieces(int direction) {
}

void Scene::drawScene() {
    for (Entity &entity: entities) {
        entity.draw();
    }
}
