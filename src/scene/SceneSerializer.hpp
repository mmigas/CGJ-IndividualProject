#pragma once

#include <string>
#include "yaml-cpp/emitter.h"
#include "../materials/Material.hpp"
#include "entities/Object.hpp"

class SceneSerializer {
public:
    static void serialize(const std::string &filepath);

    static bool deserialize(const std::string &filepath);

    static void serializeMaterial(YAML::Emitter &out, std::pair<std::string, Material *> &pair);

    static void serializeGameObject(YAML::Emitter &out, std::shared_ptr<Object> object);

    static void deserializeMaterial(YAML::Node materialYAML);
};
