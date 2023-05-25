/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Materials.h"

class Model : public Transform
{
public:
  enum { RANDOM = 0, COLOR = 1, MATERIAL = 2};
protected:
  int type;
  int nMeshes;
  Mesh **meshes;
  Material **materials;
  bool isMaterial;

public:
  Model();
  void Draw(Shader* shader_);
};

#endif
