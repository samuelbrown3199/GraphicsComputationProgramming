#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "bugl.h"

struct Material
{
	std::shared_ptr<Texture> diffuse, specular;
	Material(std::shared_ptr<Texture> _diffuse, std::shared_ptr<Texture> _specular)
	{
		diffuse = _diffuse;
		specular = _specular;
	}
};

class MeshRenderer
{
private:

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Material> material;

	std::string fileName;
	size_t drawCount;

public:

	glm::vec3 position, rotation, scale;

	MeshRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Material> _mat, std::string _fileName);

	GLuint vaoId = 0;
	void InitialiseMesh();
	glm::mat4 GetModelMatrix();
	void RenderMesh(glm::mat4 projection, glm::mat4 view);
};

