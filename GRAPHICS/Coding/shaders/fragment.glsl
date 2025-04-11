#version 410 core
in vec3 fragColor;
in vec2 texCoord;  // Add this

out vec4 Color;

uniform sampler2D textureSampler;  // Add this

void main()
{
    // Mix color with texture
    vec4 texColor = texture(textureSampler, texCoord);
    Color = vec4(fragColor, 1.0) * texColor;  // Or just use texColor if you prefer
}