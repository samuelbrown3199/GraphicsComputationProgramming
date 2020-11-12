#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
    int type = 0;
    glm::vec3 position, direction, ambient, diffuse, specular;
    float constant, linear, quadratic;

    Light(int _type, glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spec);
};

