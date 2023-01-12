#include "Entity.hpp"

Entity::Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : position(position), rotation(rotation), scale(scale) {

}

void Entity::move(glm::vec3 position) {
    this->position = position;
}

void Entity::rotate(glm::vec3 radians) {
    this->rotation = radians;
}

void Entity::setScale(glm::vec3 scale) {
    this->scale = scale;
}

