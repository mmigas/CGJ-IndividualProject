#pragma once

#include "Entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
private:
    std::vector<Entity> entities;
    mgl::Camera *camera;
public:

    Scene();

    void init(mgl::Camera *camera);

    void createEntity(const std::string &meshFile, int materialID);

    void createEntity(const std::string &meshFile, int materialID, glm::vec3 position);

    void createEntity(const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void drawScene();

    mgl::Camera *getCamera();

};
