#version 330 core

// input data from buffers
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
layout(location = 2) in vec3 vNor;

// uniform input data
uniform mat4 model;
uniform mat4 view;
uniform mat3 normal;
uniform float ambientStrength = 0.3;
uniform vec3 ambientColor = vec3(1.,1.,1.);
uniform vec3 lPos;
uniform vec3 dCol;

// output data from vertex shader
out vec3 fCol;

void main(){
 vec4 vert4 = model * vec4(vPos, 1.0f);
 gl_Position = view * vert4;

 vec3 norm = normalize(vec3(normal * vNor));
 vec3 vert = vec3(vert4);
 vec3 lDir = normalize(lPos - vert);
 float diffMag = max(dot(norm, lDir), 0.f);
 vec3 diffuse = diffMag * dCol;
 vec3 ambient = ambientStrength * ambientColor;
 fCol = (ambient + diffuse) * vCol;
}
