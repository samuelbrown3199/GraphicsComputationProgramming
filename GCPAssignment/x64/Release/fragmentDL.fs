#version 330

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

uniform Material material;
in vec2 texCoord;

in vec3 normal;
in vec3 fragPos;
in vec3 v_viewPos;
in vec4 fragPosLightSpace;

uniform sampler2D shadowMap;

float CalculateShadow(float lightNormal)
{
    //get the position of the fragment in world space
    vec3 pos = fragPosLightSpace.xyz * 0.5 + 0.5;

    //small bias used in the shadow calculation
    float bias = 0.00007;
    //the shadow value
    float shadow = 0.0;
    //used for smoothing the shadows
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float depth = texture(shadowMap, pos.xy + vec2(x,y) * texelSize).r; //calculate the depth with the shadow map
            shadow += (depth + bias) < pos.z ? 0.0 : 1.0; //work out the shadow value as either 1 or 0
        }
	}

    return shadow / 9.0; //returns the shadow value / 9.0 for a smoother shadow
}

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    float shadow = CalculateShadow(diff);
    return (shadow * (diffuse + specular) + ambient);
}

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(v_viewPos - fragPos);

    vec3 result = CalculateDirLight(dirLight, norm, viewDir);

    gl_FragColor = vec4(result, 1.0);
}