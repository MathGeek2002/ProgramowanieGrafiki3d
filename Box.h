/*
  Utworzono 26-04-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/
#ifndef BOX_H
#define BOX_H

#include "Model.h"

class Box : public Model
{
protected:
  float rx, ry, rz;
  float r, g, b;
public:
  Box(
    float rx_ = 1.f, float ry_ = 1.f, float rz_ = 1.f,
	  float r_ = 1.f, float g_ = 1.f, float b_ = 1.f,
    int type_ = COLOR
  );
  Box(
    float rx_, float ry_, float rz_,
    Material **materials_, int nMaterials_
  );
  ~Box();
protected:
  void Create();
};

#endif
