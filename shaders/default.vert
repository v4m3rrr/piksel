#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;

out vec2 ourTexCord;

void main()
{
  ourTexCord=aTexCord;
  gl_Position = vec4(aPos.xyz, 1.0f);
};
