#version 330 core

// input data from buffers
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
layout(location = 2) in vec3 vNor;

// uniform input data
uniform mat4 model;
uniform mat4 view;
uniform mat3 normal;

// output data from vertex shader
out vec3 fPos;
out vec3 fCol;
out vec3 fNor;

void main(){
  vec4 vert4 = model * vec4(vPos, 1.0f);
  gl_Position = view * vert4;

  fPos = vec3(vert4);
  fCol = vCol;
  fNor = normalize(vec3(normal * vNor));
}
