#version 330 core

out vec4 fragColor;

in vec2 texCoord;
in vec3 fragPos;
in vec3 fragNormal;

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 uViewPos;
uniform sampler2D uTexture;
uniform DirLight uDirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(uViewPos - fragPos);

	vec3 result = CalcDirLight(uDirLight, norm, viewDir);

	fragColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0f);
    
    vec3 ambient = light.ambient * vec3(texture(uTexture, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(uTexture, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(uTexture, texCoord));
    
    return (ambient + diffuse + specular);
}