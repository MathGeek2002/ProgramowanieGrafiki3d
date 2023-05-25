/*
  Utworzono 26-04-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/

#include "Box.h"
#include <iostream>

Box::Box(
  float rx_, float ry_, float rz_,
	float r_, float g_, float b_,
  int type_
)
  : rx(rx_), ry(ry_), rz(rz_),
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

Box::Box(
  float rx_, float ry_, float rz_,
  Material **materials_, int nMaterials_
)
  : rx(rx_), ry(ry_), rz(rz_)
{
  type = MATERIAL;
  r = 0.f;
  g = 0.f;
  b = 0.f;
  Create();

  materials = new Material* [nMeshes];
  if( nMaterials_ <= 0 ){
    Material *material = new UniformMaterial(
      r, g, b, // diffuse
      128.f,    // shininess
      r, g, b,  // ambient
      0.2f, 0.2f, 0.2f
    );
    for( int i = 0; i < nMeshes; i++ )
      materials[i] = material;
    isMaterial = true;
  }
  if( nMaterials_ >= nMeshes ){
    //std::cout << nMaterials_ << std::endl;
    for( int i = 0; i < nMeshes; i++ ){
      materials[i] = materials_[i];
      //std::cout << materials_[i] << std::endl;
    }
    isMaterial = false;
  }
  if( (nMaterials_ > 0) && (nMaterials_ < nMeshes) ){
    for( int i = 0; i < nMaterials_; i++ )
      materials[i] = materials_[i];
    for( int i = nMaterials_; i < nMeshes; i++ )
      materials[i] = materials_[nMaterials_-1];
    isMaterial = false;
  }
}

Box::~Box()
{
  if( meshes ) {
    for( int i = 0; i < nMeshes; i++ )
      if( meshes[i] )
        delete meshes[i];
    delete [] meshes;
  }
  if( isMaterial )
    delete materials[0];
  delete [] materials;
}

void
Box::Create()
{
  nMeshes = 6;
  meshes = new Mesh* [6];

  int nVertices = 4;
  int nIndices = 6;

  Vertex *vertices = new Vertex [nVertices];
  unsigned int *indices = new unsigned int [nIndices];

  vertices[0].position = glm::vec3(-rx, -ry, rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(0.f, 0.f, 1.f);
  vertices[0].texcoord = glm::vec2(0.f, 0.f);
  vertices[1].position = glm::vec3( rx, -ry, rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(0.f, 0.f, 1.f);
  vertices[1].texcoord = glm::vec2(1.f, 0.f);
  vertices[2].position = glm::vec3(-rx,  ry, rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(0.f, 0.f, 1.f);
  vertices[2].texcoord = glm::vec2(0.f, 1.f);
  vertices[3].position = glm::vec3( rx,  ry, rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(0.f, 0.f, 1.f);
  vertices[3].texcoord = glm::vec2(1.f, 1.f);

  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;
  indices[3] = 1;
  indices[4] = 3;
  indices[5] = 2;

  meshes[0] = new Mesh(nVertices, vertices, nIndices, indices);

  vertices[0].position = glm::vec3(rx, -ry, rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(1.f, 0.f, 0.f);
  vertices[1].position = glm::vec3(rx, -ry, -rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(1.f, 0.f, 0.f);
  vertices[2].position = glm::vec3(rx,  ry, rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(1.f, 0.f, 0.f);
  vertices[3].position = glm::vec3(rx,  ry, -rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(1.f, 0.f, 0.f);

  meshes[1] = new Mesh(nVertices, vertices, nIndices, indices);

  vertices[0].position = glm::vec3(rx, -ry, -rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(0.f, 0.f, -1.f);
  vertices[1].position = glm::vec3(-rx, -ry, -rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(0.f, 0.f, -1.f);
  vertices[2].position = glm::vec3(rx,  ry, -rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(0.f, 0.f, -1.f);
  vertices[3].position = glm::vec3(-rx,  ry, -rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(0.f, 0.f, -1.f);

  meshes[2] = new Mesh(nVertices, vertices, nIndices, indices);

  vertices[0].position = glm::vec3(-rx, -ry, -rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(-1.f, 0.f, 0.f);
  vertices[1].position = glm::vec3(-rx, -ry, rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(-1.f, 0.f, 0.f);
  vertices[2].position = glm::vec3(-rx, ry, -rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(-1.f, 0.f, 0.f);
  vertices[3].position = glm::vec3(-rx, ry, rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(-1.f, 0.f, 0.f);

  meshes[3] = new Mesh(nVertices, vertices, nIndices, indices);

  vertices[0].position = glm::vec3(-rx, ry, rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(0.f, 1.f, 0.f);
  vertices[1].position = glm::vec3(rx, ry, rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(0.f, 1.f, 0.f);
  vertices[2].position = glm::vec3(-rx, ry, -rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(0.f, 1.f, 0.f);
  vertices[3].position = glm::vec3(rx, ry, -rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(0.f, 1.f, 0.f);

  meshes[4] = new Mesh(nVertices, vertices, nIndices, indices);

  vertices[0].position = glm::vec3(-rx, -ry, -rz);
  vertices[0].color = glm::vec3(r, g, b);
  vertices[0].normal = glm::vec3(0.f, -1.f, 0.f);
  vertices[1].position = glm::vec3(rx, -ry, -rz);
  vertices[1].color = glm::vec3(r, g, b);
  vertices[1].normal = glm::vec3(0.f, -1.f, 0.f);
  vertices[2].position = glm::vec3(-rx, -ry, rz);
  vertices[2].color = glm::vec3(r, g, b);
  vertices[2].normal = glm::vec3(0.f, -1.f, 0.f);
  vertices[3].position = glm::vec3(rx, -ry, rz);
  vertices[3].color = glm::vec3(r, g, b);
  vertices[3].normal = glm::vec3(0.f, -1.f, 0.f);

  meshes[5] = new Mesh(nVertices, vertices, nIndices, indices);

  delete [] vertices;
  delete [] indices;
}
