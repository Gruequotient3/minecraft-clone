#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 fragColor;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
vec3 lightPos = vec3(200, 1000, 0);

uniform sampler2D atlas;

void main(){

    // Calculate light
    int i;
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 lColor = lightColor * (ambient + diffuse);
    
    // Calculate Texture color
    vec4 texColor = texture(atlas, TexCoord); 
    
    fragColor = vec4(lColor, 1.0) * texColor;
}