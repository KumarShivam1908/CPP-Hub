#version 410 core
in vec3 fragColor;

out vec4 Color;

void main()
{
    Color = vec4(fragColor.r, fragColor.g, fragColor.b, 1.0f);
}