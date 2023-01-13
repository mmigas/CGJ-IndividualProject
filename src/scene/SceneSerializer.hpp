#pragma once

#include <string>
#include "yaml-cpp/emitter.h"
#include "../materials/Material.hpp"
#include "entities/Object.hpp"
#include "../light/Light.hpp"
#include "../textures/SkyBox.hpp"

class SceneSerializer {
public:
    static void serialize(const std::string &filepath);

    static bool deserialize(const std::string &filepath);

    static void serializeMaterial(YAML::Emitter &out, std::pair<std::string, Material *> &pair);

    static void serializeObject(YAML::Emitter &out, const std::shared_ptr<Object> &object);

    static void deserializeMaterial(YAML::Node materialYAML);

    static void serializeLight(YAML::Emitter &out, const std::shared_ptr<Light> &light);

    static void serializeSkybox(YAML::Emitter &out, SkyBox &skybox);

    static void deserializeLight(YAML::Node lightYAML);

    static void deserializeSkybox(YAML::Node skyboxYAML);
};
