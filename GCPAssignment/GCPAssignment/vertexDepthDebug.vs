#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 texPos;

out vec2 TexCoords;

void main()
{
	TexCoords = texPos;
	gl_Position = vec4(aPos, 1.0);
}