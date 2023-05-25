#include "Lights.h"

PointLight::PointLight(
  float x, float y, float z,    // position
  int number_,                  // light number
  float ar, float ag, float ab, // ambient
  float dr, float dg, float db, // diffuse
  float sr, float sg, float sb, // specular
  float ac, float al, float aq  // attenuation
) : Light(ar, ag, ab, dr, dg, db, sr, sg, sb),
    number(number_),
    position(x, y, z),
    attenuation(ac, al, aq)
{
  gizmo = new Box(
    0.1f, 0.1f, 0.1f,
    dr, dg, db
  );
  glm::mat4 model(1.f);
  model = glm::translate(model, position);
  gizmo->SetLocalTransform(model);
}

PointLight::~PointLight()
{
  delete gizmo;
}

void
PointLight::SetPosition(float x, float y, float z)
{
  position.x = x;
  position.y = y;
  position.z = z;
  glm::mat4 model(1.f);
  model = glm::translate(model, position);
  gizmo->SetLocalTransform(model);
}

void
PointLight::Draw(Shader *shader)
{
  gizmo->Draw(shader);
}

void
PointLight::SetLight(Shader *shader)
{
  if( number == 0 )
  {
    shader->SetVector3("pointLights[0].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[0].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[0].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[0].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[0].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 1 )
  {
    shader->SetVector3("pointLights[1].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[1].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[1].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[1].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[1].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 2 )
  {
    shader->SetVector3("pointLights[2].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[2].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[2].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[2].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[2].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 3 )
  {
    shader->SetVector3("pointLights[3].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[3].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[3].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[3].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[3].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 4 )
  {
    shader->SetVector3("pointLights[4].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[4].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[4].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[4].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[4].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 5 )
  {
    shader->SetVector3("pointLights[5].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[5].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[5].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[5].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[5].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 6 )
  {
    shader->SetVector3("pointLights[6].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[6].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[6].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[6].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[6].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 7 )
  {
    shader->SetVector3("pointLights[7].position", glm::value_ptr(position));
    shader->SetVector3("pointLights[7].attenuation", glm::value_ptr(attenuation));
    shader->SetVector3("pointLights[7].ambient", glm::value_ptr(ambient));
    shader->SetVector3("pointLights[7].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("pointLights[7].specular", glm::value_ptr(specular));
    return;
  }
}

DirectionalLight::DirectionalLight(
  int number_,                  // light number
  float x, float y, float z,    // direction
  float ar, float ag, float ab, // ambient
  float dr, float dg, float db, // diffuse
  float sr, float sg, float sb // specular
) : Light(ar, ag, ab, dr, dg, db, sr, sg, sb),
    number(number_),
    direction(x, y, z)
{}

void
DirectionalLight::SetDirection(float x, float y, float z)
{
  direction.x = x;
  direction.y = y;
  direction.z = z;
}

void
DirectionalLight::SetLight(Shader *shader)
{
  if( number == 0 )
  {
    shader->SetVector3("directionalLights[0].direction", glm::value_ptr(direction));
    shader->SetVector3("directionalLights[0].ambient", glm::value_ptr(ambient));
    shader->SetVector3("directionalLights[0].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("directionalLights[0].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 1 )
  {
    shader->SetVector3("directionalLights[1].direction", glm::value_ptr(direction));
    shader->SetVector3("directionalLights[1].ambient", glm::value_ptr(ambient));
    shader->SetVector3("directionalLights[1].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("directionalLights[1].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 2 )
  {
    shader->SetVector3("directionalLights[2].direction", glm::value_ptr(direction));
    shader->SetVector3("directionalLights[2].ambient", glm::value_ptr(ambient));
    shader->SetVector3("directionalLights[2].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("directionalLights[2].specular", glm::value_ptr(specular));
    return;
  }
  if( number == 3 )
  {
    shader->SetVector3("directionalLights[3].direction", glm::value_ptr(direction));
    shader->SetVector3("directionalLights[3].ambient", glm::value_ptr(ambient));
    shader->SetVector3("directionalLights[3].diffuse", glm::value_ptr(diffuse));
    shader->SetVector3("directionalLights[3].specular", glm::value_ptr(specular));
    return;
  }
}
