#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragColor = vertexColor;
    gl_Position = projection * view * model * vec4(position, 1.0);
}