#include "Application.h"

Application::Application()
{
	std::cout << "Created application" << std::endl;
	srand(time(NULL));
}

void Application::Initialise()
{
	window = SDL_CreateWindow("GCP Assignment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}
	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	cam = std::make_shared<Camera>();
	shader = std::make_shared<Shader>("vertex.vs", "fragment.fs");

	shader->UseShader();
	//bind any required data to the shaders in intialisation
	shader->BindVector3("u_ALightColour", glm::vec3(0.0f, 0.45f, 0.45f));
	shader->BindFloat("u_ALightStrength", 0.25);
	shader->BindVector3("u_LightPosition", glm::vec3(10, 10, 10));
	glUseProgram(0);

	crateTexture = std::make_shared<Texture>();
	crateTexture->resourcePath = "crate.png";
	crateTexture->OnLoad();

	floorTexture = std::make_shared<Texture>();
	floorTexture->resourcePath = "floor.png";
	floorTexture->OnLoad();

	cubes.push_back(std::make_shared<CubeRenderer>(shader, glm::vec3(0, 0, 0), glm::vec3(0,0,0), glm::vec3(25, 0.5, 25), floorTexture)); //floor

	cubes.push_back(std::make_shared<CubeRenderer>(shader, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateTexture));	//other cubes
	cubes.push_back(std::make_shared<CubeRenderer>(shader, glm::vec3(5, 5, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateTexture));
}

void Application::MainLoop()
{
	SDL_Event e = { 0 };
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	while (loop)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
		}
		UpdateScreenSize();

		cam->CameraControls();
		cam->UpdateCamera();

		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		for (size_t cu = 0; cu < cubes.size(); cu++)
		{
			cubes.at(cu)->RenderCube(GetProjectionMatrix(), cam->view);
		}

		SDL_GL_SwapWindow(window);
	}
}

void Application::UpdateScreenSize()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	proj = GetProjectionMatrix();
}

glm::mat4 Application::GetProjectionMatrix()
{
	proj = glm::perspective(glm::radians(90.0f), (float)windowHeight / (float)windowWidth, 0.1f, 100.0f);
	return proj;
}