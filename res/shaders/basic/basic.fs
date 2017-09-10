#version 420

out vec4 frag_color;

uniform sampler2D u_diffuse;

#define MAX_LIGHTS 4

struct PointLight {
  vec3 position[MAX_LIGHTS];
  vec4 color[MAX_LIGHTS];
  //float radius[MAX_LIGHTS];
};

uniform PointLight u_point_lights;

in VS_OUT {
  vec3 world_position;
  vec2 uv;
  vec3 normal;
} vs_out;

vec3 calculateAmbient(vec3 diffuse_color) {
  return diffuse_color * 0.1;
}

vec3 calculateDiffuse(vec3 diffuse_color, vec3 light_color, 
                      vec3 normal, vec3 light_dir, float radius) {
  return diffuse_color * light_color * 
         clamp(dot(normal, -light_dir), 0.0, 1.0);
}

void main() {
  vec4 diffuse_texture_color = texture(u_diffuse, vec2(vs_out.uv.x, 1.0-vs_out.uv.y));
  vec3 ambient = calculateAmbient(diffuse_texture_color.xyz);
  vec3 temp_frag_color = vec3(0.0);

  for (int i = 0; i < MAX_LIGHTS; i++) {
    vec3 light_to_frag = vs_out.world_position - u_point_lights.position[i];
    float light_dist = length(light_to_frag);
    vec3 light_dir = normalize(light_to_frag);

    vec3 diffuse = calculateDiffuse(
                        diffuse_texture_color.xyz, u_point_lights.color[i].xyz, 
                        normalize(vs_out.normal), light_dir,                      
                        //u_point_lights.radius[i]);
                        u_point_lights.color[i].w);

    float attenuation = 1.0 / (0.1 + 0.1 * light_dist + 0.1 * light_dist * light_dist);

    temp_frag_color += clamp(diffuse, vec3(0.0), vec3(1.0)) * attenuation;
  }

  frag_color = vec4(ambient + temp_frag_color, 1.0);
  //frag_color = vec4(normalize(vs_out.normal), 1.0);
}