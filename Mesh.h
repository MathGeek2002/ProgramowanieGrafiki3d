/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
 */
#ifndef MESH_H
#define MESH_H

#include "Vertex.hpp"
#include "Transform.h"

class Mesh : public Transform
{
public:
  int nVertices;// number of vertices
  Vertex *vertices;// table of vertices
  int nIndices;// number of indices
  unsigned int *indices;// table of indices
  unsigned int vao, vbo, ebo;

  Mesh(
    int nVertices_, Vertex *vertices_,
	  int nIndices_, unsigned int *indices_
  );
  ~Mesh();
};

#endif
