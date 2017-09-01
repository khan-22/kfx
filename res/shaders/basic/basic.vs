#version 420

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;

out VS_OUT {
  vec2 uv;
  vec3 normal;
} vs_out;

void main()
{
  gl_Position = u_MVP * vec4(position, 1.0);  

  vs_out.uv = uv;
  vs_out.normal = normal;
}