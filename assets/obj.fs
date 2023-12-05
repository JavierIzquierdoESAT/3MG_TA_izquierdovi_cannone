#version 330

layout(location = 0) out vec4 fragColor;
vec3 u_camera_position = vec3(40.0,0.0,0.0);

vec3 direct_light_dir = vec3(-5.0, 0.0, 10.0);
vec3 point_light_pos = vec3(2.0, 2, 2.0);

in vec3 pos;
in vec3 normal;


vec3 ambient = vec3(0.0, 0.0, 0.0);
vec3 diffuse = vec3(1.0, 0.0, 0.0);
vec3 specular = vec3(1.0, 1.0, 1.0);

float constant = 1.0;
float linear = 0.09;
float quadratic = 0.032;

void main() {
  vec3 norm_normaliz = normalize(normal);

  vec3 amb = ambient;

  //DIRECTIONAL
  //diffuse
  
  vec3 norm_pos = normalize(-direct_light_dir);
  //dot devuelve angulo entre dos vectores asi luego lo multiplicamos por el color para detectar si este se puede pintar
  float dif = max(dot(norm_normaliz,norm_pos), 0.0);
  vec3 col = diffuse * dif;

  //specular
  vec3 viewDir = normalize(u_camera_position - pos);
  vec3 reflectDir = reflect(-norm_pos, norm_normaliz);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0),32.0);
  vec3 specular = specular * spec;
  


  vec3 result1 =   ambient + col + specular;


  fragColor = vec4(1,0,0, 1.0);
}
