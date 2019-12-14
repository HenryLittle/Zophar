#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
out vec3 EyePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 eyePos;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // pass to fragment shader
    // this operation is very costly !!!
    Normal = mat3(transpose(inverse(model))) * aNormal;
    // the light and the vertex both need to be in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    // when the light was passed to the shader it's already in world space
    EyePos = eyePos;
    LightPos = lightPos;
}