#version 330

layout(location = 0)in vec3 a_Position;
layout(location = 1)in vec2 a_TexCoords;
layout(location = 2)in vec3 a_Normal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec3 u_ALightColour;
out vec3 v_ALightColour;

uniform float u_ALightStrength;
out float v_ALightStrength;

uniform vec3 u_LightPosition;
out vec3 v_LightPos;

uniform vec3 viewPos;
out vec3 v_viewPos;

void main()
{
	texCoord = a_TexCoords;

	fragPos = vec3(u_Model * vec4(a_Position, 1.0));
	normal = a_Normal;

	v_ALightColour = u_ALightColour;
	v_ALightStrength = u_ALightStrength;
	v_LightPos = u_LightPosition;

	v_viewPos = viewPos;

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}