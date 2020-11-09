#pragma once

#include <iostream>
#include <exception>
#include <memory>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "CubeRenderer.h"
#include "MeshRenderer.h"
#include "Texture.h"

class Application
{
private:

	glm::mat4 proj;

	int windowHeight = 900, windowWidth = 900;
	SDL_Window* window;

	bool loop = true;

	std::shared_ptr<Camera> cam;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> crateTexture, floorTexture, catTexture, catSpecular;
	std::shared_ptr<Material> catMat;

	std::vector<std::shared_ptr<CubeRenderer>> cubes;
	std::vector<std::shared_ptr<MeshRenderer>> meshes;

	void UpdateScreenSize();

public:

	Application();

	void Initialise();
	void MainLoop();
	glm::mat4 GetProjectionMatrix();
};

