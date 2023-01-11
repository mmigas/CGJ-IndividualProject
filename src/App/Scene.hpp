#pragma once

#include "../Entities/Object.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    void createEntity(const std::string &name, const std::string &meshFile, int materialID);

    void createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position);

    void createEntity(const std::string &name, const std::string &meshFile, int materialID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void createLight(glm::vec3 position, glm::vec3 color, float intensity);

    mgl::Camera *getCamera();

    std::vector<Object> &getObjects();

    static Scene &getInstance();

    std::shared_ptr<Light> getLight();

};
