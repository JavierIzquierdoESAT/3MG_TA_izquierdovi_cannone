#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec3 aUV;
out vec3 color;

uniform vec3 position;

void main(){
    color = aCol;
    gl_Position = vec4(aPos.x + position.x, aPos.y+position.y, aPos.z + position.z, 1.0);
}
