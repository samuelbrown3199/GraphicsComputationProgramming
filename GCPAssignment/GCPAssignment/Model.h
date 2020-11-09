#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>

struct Face
{
	float posX, posY, posZ;
	float texA, texB, texC;
	float normX, normY, normZ;
};

class Model
{
public:

	std::string filename;
	int drawCount;

	GLuint OnLoad()
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<Face> faces;

		std::ifstream file(filename.c_str());
		if (!file.is_open())
		{
			std::cout << "Couldn't find file: " << filename << std::endl;
			throw std::exception();
		}

		std::string currentLine;
		while (!file.eof())
		{
			std::getline(file, currentLine);
			if (currentLine.length() < 1) continue;
		}
	}
};

