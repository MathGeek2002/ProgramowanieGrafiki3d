#pragma once

#include "Model.h"
#include <glm/glm.hpp>

class Sphere : public Model
{
private:
    int nx, nz;
    float radius;
    glm::vec3 color;

    glm::vec3 GetPointOnSphere(float phi, float theta);

    int getId(int x,int z);

    float theta(int i);
    float phi(int i);

    glm::vec2 CalculateUV(glm::vec3 pos);

    void Create();

public:
    Sphere(int nx_ =  1, int nz_ = 1, float radius_ = 1.f,glm::vec3 color_ = glm::vec3(1,1,1));
    ~Sphere();
};