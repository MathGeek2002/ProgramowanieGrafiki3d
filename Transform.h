#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform 
{
public:
  glm::mat4 localTransform;

  Transform(const glm::mat4& localTransform_ = glm::mat4(1.f));
  void SetLocalTransform(const glm::mat4& localTransform_);
  const glm::mat4& GetLocalTransform() const;
};

#endif