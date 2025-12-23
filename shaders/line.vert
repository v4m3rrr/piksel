#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 outColor;

uniform mat4 proj_view;
uniform mat4 trans;

void main()
{
  outColor=aColor;
  gl_Position = proj_view*trans*vec4(aPos.xyz, 1.0f);
};
