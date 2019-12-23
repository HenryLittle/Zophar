#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 LightDirection;
in vec3 ViewDirection;
in vec3 FragPos;
in vec3 LightPos;
in vec3 EyePos;

uniform sampler2D texture_diffuse1;
uniform float AmbientStrength = 0.1;
uniform float SpecularStrength = 0.1;
uniform vec3 LightColor = vec3(1, 0.9, 0.9);

void main()
{
    // ambient
    vec3 ambient = AmbientStrength * LightColor;
    // difuse
    vec3 lightDirection = normalize(LightPos - FragPos);
    // offload normal calculation to FS will result in a much smoother look
    // bur requires more power
    vec3 norm = normalize(Normal);
    float lightDiffuse = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = lightDiffuse * LightColor;

    // specular
    vec3 reflectDirection = reflect(-lightDirection, norm);
    vec3 viewDirection = normalize(EyePos - FragPos);
    float lightSpecular = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = SpecularStrength * lightSpecular * LightColor;

    // compose the final result
    FragColor = vec4((ambient + diffuse + specular), 1.0) * texture(texture_diffuse1, TexCoords);
    // used for debug normal
    //FragColor = vec4(norm, 1.0);
}