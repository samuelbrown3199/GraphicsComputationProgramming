#pragma once

#include <iostream>
#include <exception>
#include <memory>
#include <vector>
#include <chrono>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "CubeRenderer.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "Texture.h"

class Application
{
private:

	glm::mat4 proj;

	int windowHeight = 1000, windowWidth = 1000;
	SDL_Window* window;

	bool loop = true;
	int shadowType;

	std::shared_ptr<Camera> cam;
	std::shared_ptr<Shader> shader, depthShader, depthShaderPL;
	std::shared_ptr<Texture> crateTexture, floorTexture;
	std::shared_ptr<Material> floorMat, crateMat;

	std::vector<std::shared_ptr<CubeRenderer>> cubes;
	std::vector<std::shared_ptr<MeshRenderer>> meshes;
	std::shared_ptr<Light> directionalLight;
	std::vector<std::shared_ptr<Light>> lights;

	void UpdateScreenSize();

public:

	Application();

	void Initialise(int type);
	void MainLoop();
	void RenderScene();
	void RenderScene(std::shared_ptr<Shader> shader);
	void RenderQuad();
	glm::mat4 GetProjectionMatrix();
};

