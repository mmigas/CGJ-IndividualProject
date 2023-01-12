#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/Object.hpp"
#include "../light/Light.hpp"
#include "../mgl/mglCamera.hpp"

class Scene {
private:
    std::vector<Object> objects;
    mgl::Camera *camera;
    std::shared_ptr<Light> light;
    static Scene instance;
public:
    void init(mgl::Camera *camera);

    void createEntity(const std::string &name, const std::string &meshFile, int materialID, const std::string &parent = "");

    void createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, const std::string &parent = "");

    void createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string &parent = "");

    void createLight(glm::vec3 position, glm::vec3 color, float intensity);

    void addChildTo(const std::string &parentName, const Object &child);

    mgl::Camera *getCamera();

    std::vector<Object> &getObjects();

    static Scene &getInstance();

    std::shared_ptr<Light> getLight();

    Object *searchObjectByName(const std::string &name);

    Object *searchObjectByNameinChildren(Object &parent, const std::string &name);
};
