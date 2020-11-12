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

public:

	CubeRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Texture> _tex);

	GLuint vaoId = 0;
	void InitialiseCube();
	glm::mat4 GetModelMatrix();
	void RenderCube(glm::mat4 projection, glm::mat4 view);
	void RenderCube(glm::mat4 projection, glm::mat4 view, std::shared_ptr<Shader> _shader);
};

