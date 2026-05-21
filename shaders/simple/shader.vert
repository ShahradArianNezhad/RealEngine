#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec4 color;
layout(location = 3) in mat4 model;

uniform mat4 projection;
uniform mat4 view;

out vec4 oColor;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  oColor=color;
}
