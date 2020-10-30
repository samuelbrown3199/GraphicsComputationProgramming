#include "Application.h"

Application::Application()
{
	std::cout << "Created application" << std::endl;
	srand(time(NULL));
}

void Application::Initialise()
{
	window = SDL_CreateWindow("GCP Assigment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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
	for (int i = 0; i < 10; i++)
	{
		cubes.push_back(std::make_shared<CubeRenderer>(shader, glm::vec3(rand() % 30 - 30, rand() % 30 - 30, rand() % 30 - 30), glm::vec3(rand() % 360, rand() % 360, rand() % 360), glm::vec3(1,1,1)));
	}

	cubes.push_back(std::make_shared<CubeRenderer>(shader, glm::vec3(0, -15, 0), glm::vec3(0,0,0), glm::vec3(25, 1, 25)));
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
}

glm::mat4 Application::GetProjectionMatrix()
{
	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)windowHeight / (float)windowWidth, 0.1f, 100.0f);
	return proj;
}