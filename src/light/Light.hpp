#pragma once


#include "../scene/entities/Entity.hpp"

class Light : public Entity {
private:

    glm::vec3 color;
    float intensity;
    GLuint UboId;
public:
    Light(const glm::vec3 &position, const glm::vec3 &color, float intensity);

    glm::vec3 ambient();

    glm::vec3 diffuse();

    glm::vec3 specular() const;


    void bind();
};
