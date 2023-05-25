#version 330 core

// input data from buffers
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;

// uniform input data
uniform mat4 model;
uniform mat4 view;

// output data from vertex shader
out vec3 fCol;

void main(){
 gl_Position = view * model * vec4(vPos, 1.0f);
 fCol = vCol;
}
