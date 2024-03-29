#include "Application.h"

Application::Application()
{
	srand(time(NULL));
}

void Application::Initialise(int type)
{
	shadowType = type;

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
	if (shadowType == 1)
	{
		shader = std::make_shared<Shader>("vertex.vs", "fragmentDL.fs");
	}
	else if(shadowType == 2)
	{
		shader = std::make_shared<Shader>("vertex.vs", "fragmentPL.fs");
	}
	depthShader = std::make_shared<Shader>("vertexDepth.vs", "fragmentDepth.fs");
	depthShaderPL = std::make_shared<Shader>("vertexDepthPL.vs", "geometryDepthPL.gs","fragmentDepthPL.fs");

	shader->UseShader();
	//bind any required data to the shaders in intialisation
	shader->BindVector3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->BindVector3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	shader->BindVector3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->BindFloat("material.shininess", 32.0f);

	glUseProgram(0);

	crateTexture = std::make_shared<Texture>();
	crateTexture->resourcePath = "crate.png";
	crateTexture->OnLoad();

	floorTexture = std::make_shared<Texture>();
	floorTexture->resourcePath = "floor.png";
	floorTexture->OnLoad();

	floorMat = std::make_shared<Material>(floorTexture);
	crateMat = std::make_shared<Material>(crateTexture);

	if (shadowType == 1)
	{
		shader->UseShader();
		directionalLight = std::make_shared<Light>(0, glm::vec3(-10, -20, -10), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f));

		shader->BindVector3("dirLight.direction", directionalLight->position);
		shader->BindVector3("dirLight.ambient", directionalLight->ambient);
		shader->BindVector3("dirLight.diffuse", directionalLight->diffuse);
		shader->BindVector3("dirLight.specular", directionalLight->specular);
		glUseProgram(0);

		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(100, 0.5, 100), floorMat, "cube.obj")); //floor

		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 1.33, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));	//other cubes
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(9, 5, 3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));
	}
	else if (shadowType == 2)
	{
		lights.push_back(std::make_shared<Light>(1, glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f)));

		shader->UseShader();
		for (int i = 0; i < lights.size(); i++)
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

		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, -10, 0), glm::vec3(0, 0, 0), glm::vec3(10, 0.5, 10), floorMat, "cube.obj")); //floor
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 10, 0), glm::vec3(0, 0, 0), glm::vec3(10, 0.5, 10), floorMat, "cube.obj")); //top
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.5, 10, 10), floorMat, "cube.obj")); //right
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(-10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.5, 10, 10), floorMat, "cube.obj")); //left
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(10, 10, 0.5), floorMat, "cube.obj")); //forward
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(10, 10, 0.5), floorMat, "cube.obj")); //back

		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(4, 4, 4), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(-4, -4, -4), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));
		meshes.push_back(std::make_shared<MeshRenderer>(shader, glm::vec3(-6, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), crateMat, "cube.obj"));
	}
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
	const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
	unsigned int depthMap;
	unsigned int depthCubeMap;

	glGenTextures(1, &depthMap);
	glGenTextures(1, &depthCubeMap);

	if (shadowType == 1)
	{
		//generates the depth texture with the correct sizes and depth component
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//we dont want the texture to repeat so we clamp and set a border colour.
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
	}
	else if (shadowType == 2)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
		for (unsigned int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	while (loop)
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
		}
		UpdateScreenSize();

		if (shadowType == 1)
		{ 
			glm::mat4 lightProjection, lightView, lightSpaceMatrix;
			float near_plane = 1.0f, far_plane = 1000.0f;
			lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			lightView = glm::lookAt(-directionalLight->position, glm::vec3(0.0f), glm::vec3(0, 1, 0));
			lightSpaceMatrix = lightProjection * lightView;
			depthShader->UseShader();
			depthShader->BindMatrix("u_LightSpaceMatrix", lightSpaceMatrix);

			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glClear(GL_DEPTH_BUFFER_BIT);
			RenderScene(depthShader);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, windowWidth, windowHeight);

			shader->UseShader();
			shader->BindMatrix("u_LightSpaceMatrix", lightSpaceMatrix);
			shader->BindInt("shadowMap", 2);
			glUseProgram(0);
		}
		else if (shadowType == 2)
		{
			float aspect = (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT;
			glm::vec3 lightPos = lights.at(0)->position;

			float near_plane = 1.0f;
			float far_plane = 25.0f;
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
			std::vector<glm::mat4> shadowTransforms;
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			depthShaderPL->UseShader();
			for (int i = 0; i < 6; i++)
			{
				std::string location = "shadowMatrices[" + std::to_string(i);
				depthShaderPL->BindMatrix(location + "]", shadowTransforms.at(i));
			}
			depthShaderPL->BindFloat("far_plane", far_plane);
			depthShaderPL->BindVector3("lightPos", lightPos);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);

			RenderScene(depthShaderPL);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, windowWidth, windowHeight);

			shader->UseShader();
			shader->BindFloat("far_plane", far_plane);
			shader->BindInt("depthMap", 2);
			shader->BindVector3("lightPos", lightPos);
		}

		cam->CameraControls();
		cam->UpdateCamera();

		shader->UseShader();
		shader->BindVector3("viewPos", cam->position);
		glUseProgram(0);

		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE2);
		if (shadowType == 1)
		{
			glBindTexture(GL_TEXTURE_2D, depthMap);
		}
		else if(shadowType == 2)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
			meshes.at(6)->rotation.y += 0.1f;
			meshes.at(7)->rotation.y += 0.1f;
		}
		RenderScene();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time taken for frame is: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
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