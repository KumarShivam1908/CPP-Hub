#version 410 core
in vec3 fragColor;
in vec2 texCoord;

out vec4 Color;

uniform sampler2D textureSampler;

void main()
{
    Color = texture(textureSampler, texCoord);
}