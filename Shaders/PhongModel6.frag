#version 330 core

// input data from previous stage
in vec3 fPos;
in vec3 fCol;
in vec3 fNor;
in vec2 fTex;

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

struct PointLight{
  vec3 position;
  vec3 attenuation;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
#define NUMBER_POINT_LIGHTS 2
uniform PointLight pointLights[NUMBER_POINT_LIGHTS] =
  PointLight[NUMBER_POINT_LIGHTS](
    PointLight(
      vec3(0.f, 0.f, 0.f),
      vec3(1.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f)
    ),
    PointLight(
      vec3(0.f, 0.f, 0.f),
      vec3(1.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f)
    )
  );

struct Material {
  sampler2D ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
uniform Material material;

// Function declarations
vec3 CalculateDirectionalLight(
  DirectionalLight light,
  Material material,
  vec3 fPos,
  vec3 fNor,
  vec2 fTex,
  vec3 viewDir
);

vec3 CalculatePointLight(
  PointLight light,
  Material material,
  vec3 fPos,
  vec3 fNor,
  vec2 fTex,
  vec3 viewDir
);

// Main function
void main(){
  vec3 norm = normalize(fNor);
  vec3 viewDirection = normalize(viewPosition - fPos);
  // scene ambient light
  vec3 result = ambColSce * vec3( texture(material.ambient, fTex) );
  // point lights
  for( int i = 0; i < NUMBER_DIRECTIONAL_LIGHTS; i++ )
    result += CalculateDirectionalLight(
      directionalLights[i],
      material,
      fPos, norm,
      fTex,
      viewDirection
    );
  // point lights
  for( int i = 0; i < NUMBER_POINT_LIGHTS; i++ )
    result += CalculatePointLight(
      pointLights[i],
      material,
      fPos, norm,
      fTex,
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
  vec2 fTex,
  vec3 viewDir
){
  vec3 lightDirection = - normalize(light.direction);
  // ambient
  vec3 result = light.ambient * vec3( texture( material.ambient, fTex));
  // diffuse
  float magnitude = max(dot(fNor, lightDirection), 0.f);
  result += magnitude * light.diffuse * vec3( texture( material.diffuse, fTex));
  // specular
  vec3 refDir = reflect(-lightDirection, fNor);
  magnitude = pow(max(dot(viewDir, refDir), 0.f), material.shininess);
  result += magnitude * light.specular * vec3( texture(material.specular, fTex));
  return result;
}

vec3 CalculatePointLight(
  PointLight light,
  Material material,
  vec3 fPos,
  vec3 fNor,
  vec2 fTex,
  vec3 viewDir
){
  vec3 lightDirection = light.position - fPos;
  float lightDistance = length(lightDirection);
  lightDirection = normalize(lightDirection);
  // ambient
  vec3 result = light.ambient * vec3( texture( material.ambient, fTex));
  // diffuse shading
  float magnitude = max(dot(fNor, lightDirection), 0.f);
  result = magnitude * light.diffuse * vec3( texture( material.diffuse, fTex));
  // specular
  vec3 refDir = reflect(-lightDirection, fNor);
  magnitude = pow(max(dot(viewDir, refDir), 0.f), material.shininess);
  result += magnitude * light.specular * vec3( texture( material.specular, fTex));
  // attenuation
  magnitude = light.attenuation.x;
  magnitude += light.attenuation.y * lightDistance;
  magnitude += light.attenuation.z * lightDistance * lightDistance;
  magnitude = 1.f / magnitude;
  return magnitude * result;
}
