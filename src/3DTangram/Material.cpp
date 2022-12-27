#include "Material.hpp"

Material::Material(const glm::vec4 &color) : color(color) {

}

const glm::vec4 &Material::getColor() {
    return color;
}
