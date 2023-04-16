#version 330 core

layout (location = 0) in vec3 positionOS;
layout (location = 1) in vec3 normalOS;
layout (location = 2) in vec2 uv;

out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(positionOS,1.0);
    texcoord = uv;
}