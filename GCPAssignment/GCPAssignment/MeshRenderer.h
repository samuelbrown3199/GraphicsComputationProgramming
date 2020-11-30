#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "bugl.h"

/**
*Stores data relating to the material properties of the object.
*/
struct Material
{
	/**
	*Stores the textures of the diffuse and specular.
	*/
	std::shared_ptr<Texture> diffuse, specular;
	Material(std::shared_ptr<Texture> _diffuse, std::shared_ptr<Texture> _specular)
	{
		diffuse = _diffuse;
		specular = _specular;
	}
	Material(std::shared_ptr<Texture> _diffuse)
	{
		diffuse = _diffuse;
	}
};

/**
*Class for rendering a mesh.
*/
class MeshRenderer
{
private:

	/**
	*Stores the shader of the mesh.
	*/
	std::shared_ptr<Shader> shader;
	/**
	*Stores the material of the mesh.
	*/
	std::shared_ptr<Material> material;
	/**
	*Stores the file directory of the model.
	*/
	std::string fileName;
	/**
	*Stores the amount of vertices the model has for drawing later.
	*/
	size_t drawCount;

public:
	/**
	*Stores the position, rotation and scale to generate a model matrix later.
	*/
	glm::vec3 position, rotation, scale;
	/**
	*Creates a Mesh renderer with the passed parameters.
	*/
	MeshRenderer(std::shared_ptr<Shader> _shader, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, std::shared_ptr<Material> _mat, std::string _fileName);

	/**
	*The VAO ID used to store the mesh data.
	*/
	GLuint vaoId = 0;
	/**
	*Loads a model and sets up data for rendering.
	*/
	void InitialiseMesh();
	/**
	*Generates a model matrix for use in rendering.
	*/
	glm::mat4 GetModelMatrix();

	/**
	*Renders the mesh with the shader within the instance of the class.
	*/
	void RenderMesh(glm::mat4 projection, glm::mat4 view);
	/**
	*Renders the mesh with the shader passed into the function.
	*/
	void RenderMesh(glm::mat4 projection, glm::mat4 view, std::shared_ptr<Shader> _shader);
};

