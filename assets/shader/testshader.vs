#version 330 core

layout (location = 0) in vec3 positionOS;
layout (location = 1) in vec3 normalOS;
layout (location = 2) in vec2 uv;

out vec2 texcoord;
out vec3 positionWS;
out vec3 normalWS;
out vec3 lightPosWS;

//vector
uniform vec3 lightPos;
//matrix
uniform mat4 model;
uniform mat3 normal;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(positionOS,1.0);
    positionWS = vec3(model * vec4(positionOS, 1.0));
    normalWS = normal * normalOS;
    lightPosWS = vec3(model * vec4(lightPos,1.0));
    texcoord = uv;
}