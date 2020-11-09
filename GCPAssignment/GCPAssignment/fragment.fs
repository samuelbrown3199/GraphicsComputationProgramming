#version 330

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 lightPosition;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

in vec2 texCoord;
uniform sampler2D ourTexture;

in vec3 normal;
in vec3 fragPos;
in vec3 v_viewPos;

void main()
{
    //ambient light
    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, texCoord));
	
    //diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.lightPosition - fragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCoord)));

    //specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(v_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (vec3(texture(material.specular, texCoord)) * spec) * light.specular;

    vec3 result = diffuse + ambientLight + specular;
    gl_FragColor = vec4(result, 1.0);
}