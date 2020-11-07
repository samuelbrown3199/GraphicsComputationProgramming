#version 330

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec3 normal;
in vec3 fragPos;

in vec3 v_ALightColour;
in float v_ALightStrength;

in vec3 v_LightPos;

void main()
{
	vec3 ambientLight = v_ALightColour * v_ALightStrength;
	
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(v_LightPos - fragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(1, 1, 1) * diff;
    vec3 lighting = min(diffuse + ambientLight, vec3(1, 1, 1));

    vec4 tex = texture2D(ourTexture, texCoord);
    gl_FragColor = tex * vec4(lighting, 1.0);
}