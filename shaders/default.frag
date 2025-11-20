#version 330 core

in vec3 ourColor;
in vec2 ourTexCord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
  FragColor=mix(texture(texture0,ourTexCord),texture(texture1,ourTexCord),0.5);
};
