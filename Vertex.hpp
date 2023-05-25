/*
  Utworzono 22-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
 */
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex{
  glm::vec3 position; // vertex position
  glm::vec3 color;    // vertex color
  glm::vec3 normal;   // vertex normal
  glm::vec2 texcoord; // vertex texture coordinate
  static void ConfigureAttributes()
  {
    // Configure attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
      sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
      sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
      sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE,
      sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
  }
};

#endif
