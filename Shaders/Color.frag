#version 330 core

// input data from previous shader stage
in vec3 fCol;

// output fragment color
out vec3 color;

void main(){
  color = fCol;
}
