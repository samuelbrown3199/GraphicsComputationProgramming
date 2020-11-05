#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

class CubeRenderer
{
private:

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> tex;

	glm::vec3 position, rotation, scale;

	GLuint elementBuffer;
	int indices[6 * 6] =
	{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

public:

	CubeRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Texture> _tex);

	GLuint vaoId = 0;
	void InitialiseCube();
	glm::mat4 GetModelMatrix();
	void RenderCube(glm::mat4 projection, glm::mat4 view);
};

