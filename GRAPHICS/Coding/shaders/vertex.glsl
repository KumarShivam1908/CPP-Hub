#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 inTexCoord;  // Add this

out vec3 fragColor;
out vec2 texCoord;  // Add this

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragColor = vertexColor;
    texCoord = inTexCoord;  // Add this
    gl_Position = projection * view * model * vec4(position, 1.0);
}