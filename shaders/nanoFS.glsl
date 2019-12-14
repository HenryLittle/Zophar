#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPos - FragPos);
    float lightDiffuse = max(dot(norm, lightDirection), 0.15);
    FragColor = lightDiffuse * texture(texture_diffuse1, TexCoords);
    // used for debug normal
    //FragColor = vec4(norm, 1.0);
}