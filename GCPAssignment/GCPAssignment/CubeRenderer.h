#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"

class CubeRenderer
{
private:

	std::shared_ptr<Shader> shader;
	glm::vec3 position, rotation, scale;

public:

	CubeRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);

	GLuint vaoId = 0;
	void InitialiseCube();
	glm::mat4 GetModelMatrix();
	void RenderCube(glm::mat4 projection, glm::mat4 view);
};

