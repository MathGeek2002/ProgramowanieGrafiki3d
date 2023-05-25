#version 330 core

// input data from buffers
layout(location = 0) in vec3 vPos;

// uniform input data
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
 gl_Position = projection * view * model * vec4(vPos, 1.0f);
}
