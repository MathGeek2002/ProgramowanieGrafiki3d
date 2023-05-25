#version 330 core

// input data from previous stage
in vec3 fCol;

// uniform input data
uniform vec3 ambColSce = vec3(0.1f ,0.1f, 0.1f);

// output color
out vec3 color;

void main(){
  vec3 result = ambColSce * fCol;
  color = result;
}
