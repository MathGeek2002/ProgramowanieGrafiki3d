/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/
#ifndef PLANE_H
#define PLANE_H

#include "Model.h"

class Plane : public Model
{
private:
  int nx, nz;
  float dx, dz;
  float r, g, b;
public:
  Plane(
    int nx_ =  1, int nz_ = 1,
    float dx_ = 1.f, float dz_ = 1.f,
    int type_ = RANDOM,
    float r_ = 1.f, float g_ = 1.f, float b_ = 1.f
  );
  Plane(
    int nx_, int nz_,
    float dx_, float dz_ ,
    Material *material_
  );
  ~Plane();
protected:
  void Create();
};

#endif
