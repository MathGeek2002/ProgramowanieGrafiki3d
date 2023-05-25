/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/
#include "Plane.h"


Plane::Plane(
  int nx_, int nz_,
  float dx_, float dz_,
  int type_,
  float r_, float g_, float b_
)
: nx(nx_), nz(nz_),
  dx(dx_), dz(dz_),
  r(r_), g(g_), b(b_)
{
  type = type_;
  Create();
  isMaterial = false;
  if( type == MATERIAL ){
    Material *material = new UniformMaterial(
      r, g, b, // diffuse
      128.f,    // shininess
      r, g, b,  // ambient
      0.2f, 0.2f, 0.2f
    );
    materials = new Material* [nMeshes];
    for( int i = 0; i < nMeshes; i++ )
      materials[i] = material;
    isMaterial = true;
  }
}

Plane::Plane(
  int nx_, int nz_,
  float dx_, float dz_,
  Material *material_
)
: nx(nx_), nz(nz_),
  dx(dx_), dz(dz_)
{
  type = MATERIAL;
  r = 0.f;
  g = 0.f;
  b = 0.f;
  Create();
  materials = new Material* [1];
  materials[0] = material_;
  isMaterial = false;
}

Plane::~Plane()
{
  delete meshes[0];
  delete [] meshes;
  if( isMaterial )
    delete materials[0];
  delete [] materials;
}

void
Plane::Create()
{
  nMeshes = 1;
  meshes = new Mesh* [1];

  int nVertices = (nx + 1) * (nz + 1);
  int nIndices = 6 * nx * nz;

  Vertex *vertices =
    new Vertex [nVertices];
  unsigned int *indices =
    new unsigned int [nIndices];

  float rx = 0.5f * dx * nx;
  float rz = 0.5f * dz * nz;
  int nzz = nz + 1;
  float y = 0.f;
  for( int i = 0; i <= nx; i++ ){
    int inz1 =  i * (nz + 1);
    float x = dx * i - rx;
    for( int j = 0; j <= nz; j++ ){
      int k = inz1 + j;
      float z = dz * j - rz;
      vertices[k].position = glm::vec3(x, y, z);
      if( type == RANDOM )
      {
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
      }
      vertices[k].color = glm::vec3(r, g, b);
      vertices[k].normal = glm::vec3(0.f, 1.f, 0.f);
      float s = (float)i;
      float t = (float)j;
      vertices[k].texcoord = glm::vec2(s, t);
    }
  }

  for( int i = 0; i < nx; i++ ){
    for( int j = 0; j < nz; j++ ){
      int k = i * nz + j;
      indices[k*6+0] = i * nzz + j;
      indices[k*6+1] = i * nzz + j + 1;
      indices[k*6+2] = (i + 1) * nzz + j + 1;
      indices[k*6+3] = i * nzz + j;
      indices[k*6+4] = (i + 1) * nzz + j + 1;
      indices[k*6+5] = (i + 1) * nzz + j;
    }
  }

  meshes[0] = new Mesh(nVertices,
    vertices, nIndices, indices);

  delete [] vertices;
  delete [] indices;
}
