#version 330 core
out vec4 FragColor;


in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

struct DirectionalLight{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
};

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

#define NUMBER_DIRECTIONAL_LIGHTS 2
uniform DirectionalLight directionalLights[NUMBER_DIRECTIONAL_LIGHTS] =
  DirectionalLight[NUMBER_DIRECTIONAL_LIGHTS](
    DirectionalLight(
      vec3(0.f, 1.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, -1.f, 0.f)
    ),
    DirectionalLight(
      vec3(0.f, 1.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, 0.f, 0.f),
      vec3(0.f, -1.f, 0.f)
    )
  );

uniform sampler2D shadowMap;

uniform vec3 viewPosition;

float ShadowCalculation(vec4 fragPosLightSpace,float bias); 

void main()
{           
    vec3 color = material.diffuse;
    vec3 normal = normalize(fs_in.Normal);

    vec3 lightColor = directionalLights[0].diffuse;
    // ambient
    vec3 ambient = 0.15 * lightColor;
    // diffuse
    vec3 lightDir = normalize(directionalLights[0].position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPosition - fs_in.FragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * lightColor;    
    
    // calculate shadow
    float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.005); 
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, bias);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}

float ShadowCalculation(vec4 fragPosLightSpace,float bias)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}