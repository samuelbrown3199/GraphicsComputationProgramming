#pragma once

#include <string>

#include <GL/glew.h>

class Texture
{
	private:

	public:

		std::string resourcePath;
		GLuint textureID;

		void OnLoad();
};