#include "Light.h"

Light::Light(int _type, glm::vec3 _pos, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spec)
{
	type = _type;
	position = _pos;
	ambient = _amb;
	diffuse = _dif;
	specular = _spec;

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}