/*
  Utworzono 21-03-2018 na zajecia "Programowanie grafiki 3D"
  przez Tomasz Karpiuk.
*/
#include "Model.h"

Model::Model()
{
  nMeshes = 0;
  meshes = NULL;
  materials = nullptr;
  isMaterial = false;
}

void
Model::Draw(Shader* shader_)
{
 //std::cout << materials << std::endl;
  if( type == MATERIAL ){
    for( int i = 0; i < nMeshes; i++ ){
      glm::mat4 model = localTransform * meshes[i]->localTransform;
      shader_->SetMatrix4("model", glm::value_ptr(model));
      glm::mat3 normal = glm::mat3(glm::inverse(glm::transpose(model)));
      shader_->SetMatrix3("normal", glm::value_ptr(normal));
      materials[i]->SetMaterial(shader_);
      //std::cout << materials[i] << std::endl;
      glBindVertexArray(meshes[i]->vao);
      glDrawElements(GL_TRIANGLES, meshes[i]->nIndices, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  } else {
    for( int i = 0; i < nMeshes; i++ ){
      glm::mat4 model = localTransform * meshes[i]->localTransform;
      shader_->SetMatrix4("model", glm::value_ptr(model));
      glm::mat3 normal = glm::mat3(glm::inverse(glm::transpose(model)));
      shader_->SetMatrix3("normal", glm::value_ptr(normal));
      glBindVertexArray(meshes[i]->vao);
      glDrawElements(GL_TRIANGLES, meshes[i]->nIndices, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  }
}
