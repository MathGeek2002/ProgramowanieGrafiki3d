#version 330 core

struct PointLight{
  vec3 position;
  vec3 attenuation;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
#define NUMBER_POINT_LIGHTS 1
uniform PointLight pointLights[NUMBER_POINT_LIGHTS];

// input data from previous stage
in vec3 fPos;
in vec3 fCol;
in vec3 fNor;

// uniform input data
uniform vec3 ambColSce = vec3(0.1f ,0.1f, 0.1f);
uniform vec3 viewPosition;

// output color
out vec3 color;

vec3 CalculatePointLight(
  PointLight light,
  vec3 fPos,
  vec3 fCol,
  vec3 fNor,
  vec3 viewDir
);

void main(){
  vec3 norm = normalize(fNor);
  vec3 viewDirection = normalize(viewPosition - fPos);
  // scene ambient light
  vec3 result = ambColSce * fCol;
  // point lights
  result += CalculatePointLight(
    pointLights[0],
    fPos, fCol, norm,
    viewDirection
  );
  color = result;
}

vec3 CalculatePointLight(
  PointLight light,
  vec3 fPos,
  vec3 fCol,
  vec3 fNor,
  vec3 viewDir
){
  vec3 lightDirection = normalize(light.position - fPos);
  // diffuse shading
  float diff = max(dot(fNor, lightDirection), 0.0);
  vec3 ambient = light.ambient * fCol;
  vec3 diffuse = diff * light.diffuse * fCol;
  return (ambient + diffuse);
}
