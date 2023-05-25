/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
 */
#include "Mesh.h"
#include <GL/glew.h>

Mesh::Mesh(int nVertices_, Vertex *vertices_,
	int nIndices_, unsigned int *indices_)
: nVertices(nVertices_), vertices(vertices_),
  nIndices(nIndices_), indices(indices_)
{
  // OpenGL objects
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  // Load data to OpenGL objects
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex),
	       vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    nIndices * sizeof(unsigned int),
	  indices, GL_STATIC_DRAW);
  // Configure attributes
  Vertex::ConfigureAttributes();
  // Unbind vao
  glBindVertexArray(0);
}

Mesh::~Mesh()
{
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}
