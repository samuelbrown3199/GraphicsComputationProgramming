#pragma once

#include <vector>
#include <iostream>
#include <exception>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:

	std::string vertexCode;
	std::string geometryCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream gShaderFile;
	std::ifstream fShaderFile;

public:

	GLuint programID;

	Shader(std::string vertexPath, std::string fragmentPath);
	Shader(std::string vertexPath, std::string geometryPath, std::string fragmentPath);
	~Shader();

	void SetupShader(const GLchar* vertexSource, const GLchar* fragmentSource);
	void SetupShader(const GLchar* vertexSource, const GLchar* geometrySource, const GLchar* fragmentSource);

	void UseShader();

	void BindAttributeLocation(int index, const GLchar* name);
	void BindMatrix(std::string location, glm::mat4 matrix);
	void BindFloat(std::string location, float value);
	void BindInt(std::string location, int value);
	void BindVector3(std::string location, glm::vec3 vector);

protected:

};


