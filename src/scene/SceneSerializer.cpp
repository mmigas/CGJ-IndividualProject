#include "SceneSerializer.hpp"
#include "glm/glm.hpp"
#include "entities/Object.hpp"
#include "Scene.hpp"
#include "../materials/MaterialsLibrary.hpp"

#include <fstream>
#include <filesystem>

#include <yaml-cpp/yaml.h>

namespace YAML {

    template<>
    struct convert<glm::vec2> {
        static Node encode(const glm::vec2 &rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node &node, glm::vec2 &rhs) {
            if (!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3 &rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node &node, glm::vec3 &rhs) {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec4> {
        static Node encode(const glm::vec4 &rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node &node, glm::vec4 &rhs) {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };

}

YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec2 &v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
    return out;
}

YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return out;
}

YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
    return out;
}

void SceneSerializer::serializeObject(YAML::Emitter &out, const std::shared_ptr<Object> &object) {
    out << YAML::BeginMap;
    out << YAML::Key << "Name" << YAML::Value << object->name;
    std::string meshName = object->meshFilePath;
    meshName = meshName.substr(object->meshFilePath.find_last_of('/') + 1);
    out << YAML::Key << "MeshName" << YAML::Value << meshName;
    out << YAML::Key << "Position" << YAML::Value << object->position;
    out << YAML::Key << "Rotation" << YAML::Value << object->rotation;
    out << YAML::Key << "Scale" << YAML::Value << object->scale;
    out << YAML::Key << "MaterialID" << YAML::Value << object->material->id;

    if (object->hasChildren()) {
        out << YAML::Key << "Children" << YAML::Value << YAML::BeginSeq;
        for (auto &child: object->getChildren()) {
            serializeObject(out, child);
        }
        out << YAML::EndSeq;
    }
    out << YAML::EndMap;
}

void SceneSerializer::serializeMaterial(YAML::Emitter &out, std::pair<std::string, Material *> &pair) {
    Material *material = pair.second;
    out << YAML::BeginMap;
    out << YAML::Key << "Name" << YAML::Value << pair.first;
    out << YAML::Key << "ID" << YAML::Value << material->id;
    out << YAML::Key << "color" << YAML::Value << material->color;
    out << YAML::Key << "diffuse" << YAML::Value << material->diffuse;
    out << YAML::Key << "specular" << YAML::Value << material->specular;
    out << YAML::Key << "shininess" << YAML::Value << material->shininess;
    out << YAML::Key << "reflectiveness" << YAML::Value << material->reflectiveness;
    out << YAML::Key << "transparent" << YAML::Value << material->transparent;
    out << YAML::Key << "shaderType" << YAML::Value << material->shaderType;

    out << YAML::EndMap;
}

void SceneSerializer::serializeLight(YAML::Emitter &out, const std::shared_ptr<Light> &light) {
    out << YAML::BeginMap;
    out << YAML::Key << "position" << YAML::Value << light->position;
    out << YAML::Key << "color" << YAML::Value << light->color;
    out << YAML::Key << "intensity" << YAML::Value << light->intensity;
    out << YAML::EndMap;
}

void SceneSerializer::serializeSkybox(YAML::Emitter &out, SkyBox &skybox) {
    out << YAML::BeginMap;
    out << YAML::Key << "skyboxFolder" << YAML::Value << skybox.skyboxFolder;
    out << YAML::EndMap;
}

void SceneSerializer::serialize(const std::string &filepath) {
    YAML::Emitter out;

    out << YAML::BeginMap;
    out << YAML::Key << "Materials" << YAML::Value << YAML::BeginSeq;
    for (std::pair<std::string, Material *> pair: MaterialsLibrary::getInstance().getMaterials()) {
        serializeMaterial(out, pair);
        std::cout << "Serialize material with name =" << pair.first << std::endl;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "Objects" << YAML::Value << YAML::BeginSeq;
    for (std::shared_ptr<Object> object: Scene::getInstance().getObjects()) {
        serializeObject(out, object);
        std::cout << "Serialize object with name =" << object->name << std::endl;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "Light" << YAML::Value << YAML::BeginSeq;
    serializeLight(out, Scene::getInstance().getLight());
    std::cout << "Serialize light" << std::endl;
    out << YAML::EndSeq;
    out << YAML::Key << "Skybox" << YAML::Value << YAML::BeginSeq;
    serializeSkybox(out, Scene::getInstance().getSkybox());
    std::cout << "Serialize skybox" << std::endl;
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout(filepath);
    fout << out.c_str();
    fout.close();
}

static void deserializeObject(YAML::Node objectYAML, const std::shared_ptr<Object> &parent) {
    std::string name = objectYAML["Name"].as<std::string>();

    std::cout << "Deserialized object with name = " << name << std::endl;
    std::string meshFilePath = objectYAML["MeshName"].as<std::string>();
    glm::vec3 position = objectYAML["Position"].as<glm::vec3>();
    glm::vec3 rotation = objectYAML["Rotation"].as<glm::vec3>();
    glm::vec3 scale = objectYAML["Scale"].as<glm::vec3>();
    int materialID = objectYAML["MaterialID"].as<int>();

    if (parent != nullptr) {
        Scene::getInstance().createEntity(name, meshFilePath, materialID, position, rotation, scale, parent->getName());
    } else {
        Scene::getInstance().createEntity(name, meshFilePath, materialID, position, rotation, scale, "");
    }
    auto childrenNode = objectYAML["Children"];
    for (auto childNodeYAML: childrenNode) {
        if (childrenNode) {
            deserializeObject(childNodeYAML, Scene::getInstance().searchObjectByName(name));
        }
    }
}

void SceneSerializer::deserializeMaterial(YAML::Node materialYAML) {
    std::string name = materialYAML["Name"].as<std::string>();

    std::cout << "Deserialized object with name = " << name << std::endl;
    int id = materialYAML["ID"].as<int>();
    glm::vec3 color = materialYAML["color"].as<glm::vec3>();
    float shininess = materialYAML["shininess"].as<float>();
    float reflectiveness = materialYAML["reflectiveness"].as<float>();
    GLuint transparent = materialYAML["transparent"].as<GLuint>();
    mgl::ShaderType shaderType = (mgl::ShaderType) (materialYAML["shaderType"].as<int>());
    MaterialsLibrary::getInstance().loadMaterial(id, name, color, shininess, reflectiveness, transparent, shaderType);
}

void SceneSerializer::deserializeLight(YAML::Node lightYAML) {
    std::cout << "Deserialized light" << std::endl;
    glm::vec3 position = lightYAML["position"].as<glm::vec3>();
    glm::vec3 color = lightYAML["color"].as<glm::vec3>();
    float intensity = lightYAML["intensity"].as<float>();
    Scene::getInstance().createLight(position, color, intensity);
}

void SceneSerializer::deserializeSkybox(YAML::Node skyboxYAML) {
    std::cout << "Deserialized skybox" << std::endl;
    std::string skyboxFolder = skyboxYAML["skyboxFolder"].as<std::string>();
    Scene::getInstance().getSkybox().loadCubeMap(skyboxFolder);
}

bool SceneSerializer::deserialize(const std::string &filepath) {
    YAML::Node data;
    try {
        data = YAML::LoadFile(filepath);
    }
    catch (YAML::Exception &e) {
        std::cout << "Failed to load .scene file " << filepath << ".\n      " << e.what() << std::endl;
        return false;
    }
    YAML::Node node = data["Materials"];
    MaterialsLibrary::getInstance().clear();
    if (node) {
        for (YAML::Node materialYAML: node) {
            deserializeMaterial(materialYAML);
        }
    }

    node = data["Objects"];
    Scene::getInstance().clear();
    if (node) {
        for (YAML::Node objectYAML: node) {
            deserializeObject(objectYAML, nullptr);
        }
    }

    node = data["Light"];
    if (node) {
        for (YAML::Node lightYAML: node) {
            deserializeLight(lightYAML);
        }
    }

    node = data["Skybox"];
    if (node) {
        for (YAML::Node skyboxYAML: node) {
            deserializeSkybox(skyboxYAML);
        }
    }

    return true;
}