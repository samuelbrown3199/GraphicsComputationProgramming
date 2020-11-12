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
	depthShader = std::make_shared<Shader>("vertexDepth.vs", "fragmentDepth.fs");
	depthDebugShader = std::make_shared<Shader>("vertexDepthDebug.vs", "fragmentDepthDebug.fs");

	shader->UseShader();
	//bind any required data to the shaders in intialisation

	shader->BindVector3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->BindVector3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	shader->BindVector3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->BindFloat("material.shininess", 32.0f);

	shader->BindVector3("dirLight.direction", glm::vec3(-10, -10, -10));
	shader->BindVector3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->BindVector3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.31f));
	shader->BindVector3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	lights.push_back(std::make_shared<Light>(1, glm::vec3(-15, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f)));
	lights.push_back(std::make_shared<Light>(1, glm::vec3(-5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	lights.push_back(std::make_shared<Light>(1, glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	lights.push_back(std::make_shared<Light>(1, glm::vec3(15, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

	for (int i = 0; i < 4; i++)
	{
		std::string location = "pointLights[" + std::to_string(i);
		shader->BindVector3(location + "].position", lights[i]->position);
		shader->BindVector3(location + "].ambient", lights[i]->ambient);
		shader->BindVector3(location + "].diffuse", lights[i]->diffuse);
		shader->BindVector3(location + "].specular", lights[i]->specular);

		shader->BindFloat(location + "].constant", lights[i]->constant);
		shader->BindFloat(location + "].linear", lights[i]->linear);
		shader->BindFloat(location + "].quadratic", lights[i]->quadratic);
	}

	glUseProgram(0);

	crateTexture = std::make_shared<Texture>();
	crateTexture->resourcePath = "crate.png";
	crateTexture->OnLoad();

	floorTexture = std::make_shared<Texture>();
	floorTexture->resourcePath = "floor.png";
	floorTexture->OnLoad();

	catTexture = std::make_shared<Texture>();
	catTexture->resourcePath = "Whiskers_diffuse.png";
	catTexture->OnLoad();

	catSpecular = std::make_shared<Texture>();
	catSpecular->resourcePath = "Whiskers_specular.png";
	catSpecular->OnLoad();

	catMat = std::make_shared<Material>(catTexture, catSpecular);
	floorMat = std::make_shared<Material>(floorTexture);
	crateMat = std::make_shared<Material>(crateTexture);

	meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(-5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), catMat, "curuthers.obj"));
	meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(100, 0.5, 100), floorMat, "cube.obj")); //floor

	meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));	//other cubes
	meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(5, 5, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));

}

void Application::MainLoop()
{
	SDL_Event e = { 0 };
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	//Configure the depth map FBO
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	//create depth texture
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColour[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);

	//attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

		glm::mat4 lightProjection, lightView, lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 1000.0f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0, 1, 0));
		lightSpaceMatrix = lightProjection * lightView;
		depthShader->UseShader();
		depthShader->BindMatrix("u_LightSpaceMatrix", lightSpaceMatrix);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glClear(GL_DEPTH_BUFFER_BIT);
		RenderScene(depthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, windowWidth, windowHeight);

		cam->CameraControls();
		cam->UpdateCamera();

		shader->UseShader();
		shader->BindVector3("viewPos", cam->position);
		shader->BindMatrix("u_LightSpaceMatrix", lightSpaceMatrix);
		shader->BindInt("shadowMap", 2);
		glUseProgram(0);

		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		RenderScene();
	}
}

void Application::RenderScene()
{
	for (size_t cu = 0; cu < cubes.size(); cu++)
	{
		cubes.at(cu)->RenderCube(GetProjectionMatrix(), cam->view);
	}
	for (size_t mu = 0; mu < meshes.size(); mu++)
	{
		meshes.at(mu)->RenderMesh(GetProjectionMatrix(), cam->view);
	}

	SDL_GL_SwapWindow(window);
}

void Application::RenderScene(std::shared_ptr<Shader> shader)
{
	for (size_t cu = 0; cu < cubes.size(); cu++)
	{
		cubes.at(cu)->RenderCube(GetProjectionMatrix(), cam->view, shader);
	}
	for (size_t mu = 0; mu < meshes.size(); mu++)
	{
		meshes.at(mu)->RenderMesh(GetProjectionMatrix(), cam->view, shader);
	}
}

void Application::RenderQuad()
{
	unsigned int quadVAO = 0;
	unsigned int quadVBO;

	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Application::UpdateScreenSize()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	proj = GetProjectionMatrix();
}

glm::mat4 Application::GetProjectionMatrix()
{
	proj = glm::perspective(glm::radians(90.0f), (float)windowHeight / (float)windowWidth, 0.1f, 250.0f);
	return proj;
}