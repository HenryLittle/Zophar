#version 330 core

// in vec3 color;
in vec2 TexCoord;

out vec4 frag_Color;

// uniform sampler2D texture1;
// uniform sampler2D texture2;
void main()
{
    //frag_Color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2); // sampler, texture coordinate
    frag_Color = vec4(1.0f, 1.0f ,1.0f, 1.0f);
}