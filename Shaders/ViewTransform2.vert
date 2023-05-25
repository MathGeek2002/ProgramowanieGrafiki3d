#version 330 core

// input data from buffers
layout(location = 0) in vec3 vPos;

// uniform input data
uniform mat4 model;
uniform mat4 view;

void main(){
 gl_Position = view * model * vec4(vPos, 1.0f);
}
