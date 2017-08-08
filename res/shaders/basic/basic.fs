#version 420

out vec4 frag_color;

uniform sampler2D u_diffuse;

in VS_OUT {
  vec2 uv;
  vec3 normal;
} vs_out;

void main()
{
  //frag_color = vec4(vs_out.uv, 1.0, 1.0);
  frag_color = texture(u_diffuse, vec2(vs_out.uv.x, 1.0-vs_out.uv.y));
}