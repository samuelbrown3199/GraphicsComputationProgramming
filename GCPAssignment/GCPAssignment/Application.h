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

class Application
{
private:

	int windowHeight = 650, windowWidth = 650;
	SDL_Window* window;

	bool loop = true;

	std::shared_ptr<Camera> cam;
	std::shared_ptr<Shader> shader;
	std::vector<std::shared_ptr<CubeRenderer>> cubes;

	void UpdateScreenSize();

public:

	Application();

	void Initialise();
	void MainLoop();
	glm::mat4 GetProjectionMatrix();
};

