attribute vec3 a_Position;
attribute vec4 a_Colour;


uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

varying vec4 v_Colour;

void main()
{
	v_Colour = a_Colour;
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}