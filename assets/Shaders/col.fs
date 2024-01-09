#version 330 core

in vec3 color;
out vec4 FragColor;

uniform vec3 initialUniform;

void main(){
    FragColor = vec4(initialUniform.x, initialUniform.y, initialUniform.z, 1.0f);
}