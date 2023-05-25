#include "Transform.h"

Transform::Transform(const glm::mat4& localTransform_)
  : localTransform(localTransform_)
{}

void
Transform::SetLocalTransform(const glm::mat4& localTransform_)
{
  localTransform = localTransform_;
}

const glm::mat4&
Transform::GetLocalTransform() const
{
  return localTransform;
}