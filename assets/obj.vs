#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec3 aUV;
out vec3 color;
uniform float u_time;

mat4 Model() {
  return mat4(1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 1.0, 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 InitAsTranslate(float tx, float ty, float tz) {
  return mat4(1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 1.0, 0.0,
              tx,  ty,  tz,  1.0);
}

mat4 InitAsEscalado(float ex, float ey, float ez) {
  return mat4(ex, 0.0, 0.0, 0.0,
              0.0, ey, 0.0, 0.0,
              0.0, 0.0, ez, 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 InitAsRatationX(float angle) {
  return mat4(0.0, 0.0, 0.0, 0.0,
              0.0, cos(angle), sin(angle), 0.0,
              0.0, -sin(angle), cos(angle), 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 InitAsRatationY(float angle) {
  return mat4(cos(angle), 0.0, -sin(angle), 0.0,
              0.0, 0.0, 0.0, 0.0,
              sin(angle), 0.0, cos(angle), 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 InitAsRatationZ(float angle) {
  return mat4(cos(angle), sin(angle), 0.0, 0.0,
              -sin(angle), cos(angle), 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 ViewMatrix(vec3 pos,vec3 cam_pos){
    vec3 up = vec3(0.0 ,1.0, 0.0);

    vec3 fwd = normalize(pos - cam_pos);
    vec3 left = normalize(cross(fwd,up));
    vec3 update_up = normalize(cross(left,fwd));

    float dot_left = dot(left,cam_pos);
    float dot_up = dot(update_up,cam_pos);
    float dot_fwd = dot(fwd,cam_pos);

    return mat4(left.x, update_up.x, -fwd.x, 0.0,
                left.y, update_up.y, -fwd.y, 0.0,
                left.z, update_up.z, -fwd.z, 0.0,
                -dot_left, -dot_up, dot_fwd, 1.0);
}

mat4 Projection(float fv,float zn, float zf){

    float aspect = 640 / 480;
    float r = tan(fv * 0.5);

    return mat4(1.0/(aspect*r), 0.0, 0.0, 0.0,
                0.0, 1.0/r, 0.0, 0.0,
                0.0, 0.0, -((zn+zf) / (zf-zn)), -1.0,
                0.0, 0.0, -((2.0*zf*zn) / (zf-zn)), 0.0);
}


void main(){
  mat4 viw = ViewMatrix( vec3(0.0,0.0,0.0) ,vec3(5.0,-5.0,-5.0));
  float fv = 90.0 * 3.14 / 180.0;
  mat4 porj = Projection(fv,1,10);
  mat4 rot = InitAsRatationY((u_time* -0.001));
  mat4 model = Model();
  gl_Position = porj * viw * model  * vec4(aPos, 1.0);
}
