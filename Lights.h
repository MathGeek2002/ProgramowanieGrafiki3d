#ifndef LIGHTS_H
#define LIGHTS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Box.h"

class AmbientLight
{
public:
  glm::vec3 ambient; // ambient color intensity

  AmbientLight(
    float ar = 0.1f, float ag = 0.1f, float ab = 0.1f // ambient
  ) : ambient(ar, ag, ab)
  {}

  void SetLight(Shader* shader)
  {
    shader->SetVector3("ambColSce", glm::value_ptr(ambient));
  }
};

class Light : public AmbientLight
{
public:
  glm::vec3 diffuse; // diffuse color intensity
  glm::vec3 specular; // specular color intensity

  Light(
    float ar = 0.0f, float ag = 0.0f, float ab = 0.0f, // ambient
    float dr = 0.5f, float dg = 0.5f, float db = 0.5f, // diffuse
    float sr = 0.5f, float sg = 0.5f, float sb = 0.5f  // specular
  ) : AmbientLight(ar, ag, ab),
      diffuse(dr, dg, db),
      specular(sr, sg, sb)
  {}
};

class PointLight : public Light
{
public:
  int number; // light number
  glm::vec3 position; // light position
  glm::vec3 attenuation; // light attenuation
  Model *gizmo; // light gizmo

  PointLight(
    float x = 0.0f, float y = 5.0f, float z = 0.0f,    // position
    int number_ = 0,                                   // light number
    float ar = 0.1f, float ag = 0.1f, float ab = 0.1f, // ambient
    float dr = 1.0f, float dg = 0.0f, float db = 0.0f, // diffuse
    float sr = 1.0f, float sg = 1.0f, float sb = 1.0f, // specular
    float ac = 1.0f, float al = 0.0f, float aq = 0.0f  // attenuation
  );
  ~PointLight();
  void SetPosition(float = 0.f, float = 0.f, float = 0.f);
  void Draw(Shader*);
  void SetLight(Shader*);
};

class DirectionalLight : public Light
{
public:
  int number; // light number
  glm::vec3 direction; // light direction
  glm::vec3 position;
  float near_plane = 0.5f, far_plane = 100.f;

  DirectionalLight(
    int number_ = 0,                                   // light number
    float x = 0.0f, float y = -1.0f, float z = 0.0f,    // direction
    float ar = 0.1f, float ag = 0.1f, float ab = 0.1f, // ambient
    float dr = 1.0f, float dg = 1.0f, float db = 1.0f, // diffuse
    float sr = 1.0f, float sg = 1.0f, float sb = 1.0f // specular
  );
  void SetDirection(float = 0.f, float = -1.f, float = 0.f);
  void SetLight(Shader*);
  void SetLightViewMatrix(Shader *);
};

#endif
