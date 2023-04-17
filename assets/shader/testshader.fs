#version 330 core

out vec4 fragColor;

in vec2 texcoord;
in vec3 positionWS;
in vec3 normalWS;
in vec3 lightPosWS;

uniform vec3 viewPos;
uniform sampler2D texture1;
void main()
{
    vec3 lightDir = normalize(lightPosWS - positionWS);
    vec3 norm = normalize(normalWS);
    vec3 viewDir = normalize(viewPos - positionWS);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
    float diffuse = max(0, dot(lightDir, norm));
    vec3 objectColor =  texture(texture1, texcoord).rgb;
    fragColor = vec4((diffuse + spec) * objectColor, 1.0f);
}