#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
    int type = 0;
    /**
    *Stores the values of the light to buffer into the shader later.
    */
    glm::vec3 position, ambient, diffuse, specular;
    float constant, linear, quadratic;

    /**
    *Sets up a light with approriate values.
    */
    Light(int _type, glm::vec3 _pos, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spec);
};

