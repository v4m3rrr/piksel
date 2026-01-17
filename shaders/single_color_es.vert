#version 300 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;

out vec2 ourTexCord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 trans;

void main()
{
  ourTexCord=aTexCord;
  gl_Position = proj*view*trans*vec4(aPos.xyz, 1.0f);
};
