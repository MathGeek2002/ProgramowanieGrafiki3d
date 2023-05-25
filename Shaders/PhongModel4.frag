#version 330 core

// input data from previous stage
in vec3 fPos;
in vec3 fCol;
in vec3 fNor;

// output color
out vec3 color;

// uniform input data
uniform vec3 viewPosition;
uniform vec3 ambColSce = vec3(0.1f, 0.1f, 0.1f);

struct DirectionalLight{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
#define NUMBER_DIRECTIONAL_LIGHTS 2
uniform DirectionalLight directionalLights[NUMBER_DIRECTIONAL_LIGHTS] =
  DirectionalLight[NUMBER_DIRECTIONAL_LIGHTS](
    DirectionalLight(
      vec3(0.f, 1.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f)
    ),
    DirectionalLight(
      vec3(0.f, 1.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f)
    )
  );

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material =
  Material(
    vec3(0.1f, 0.1f, 0.1f),
    vec3(0.f, 0.f, 0.f),
    vec3(1.0f, 1.0f, 1.0f),
    32.f
  );

// Function declarations
vec3 CalculateDirectionalLight(
  DirectionalLight light,
  Material material,
  vec3 fPos,
  vec3 fNor,
  vec3 viewDir
);


// Main function
void main(){
  vec3 norm = normalize(fNor);
  vec3 viewDirection = normalize(viewPosition - fPos);
  // scene ambient light
  vec3 result = ambColSce * material.ambient;
  // point lights
  for( int i = 0; i < NUMBER_DIRECTIONAL_LIGHTS; i++ )
    result += CalculateDirectionalLight(
      directionalLights[i],
      material,
      fPos, norm,
      viewDirection
    );
  color = result;
}

// Function definitions
vec3 CalculateDirectionalLight(
  DirectionalLight light,
  Material material,
  vec3 fPos,
  vec3 fNor,
  vec3 viewDir
){
  vec3 lightDirection = - normalize(light.direction);
  // ambient
  vec3 result = light.ambient * material.ambient;
  // diffuse
  float magnitude = max(dot(fNor, lightDirection), 0.f);
  result += magnitude * light.diffuse * material.diffuse;
  // specular
  vec3 refDir = reflect(-lightDirection, fNor);
  magnitude = pow(max(dot(viewDir, refDir), 0.f), material.shininess);
  result += magnitude * light.specular * material.specular;
  return result;
}
