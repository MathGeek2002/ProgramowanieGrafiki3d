#include "Camera.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(
  float px, float py, float pz, // Camera position
  float ax, float ay, float az, // Look at position
  float vx, float vy, float vz, // Camera velocity
  float ux, float uy, float uz,  // Up vector
  float va, float r, float n, float f, // View angle, ratio,
  // near, far
  unsigned int ct, // Camera type
  unsigned int pt // Projection type
)
: cameraType(ct), projectionType(pt),
  eyePos(px,py,pz), lookAt(ax,ay,az), up(ux,uy,uz), vel(vx,vy,vz),
  viewAngle(va), ratio(r), near(n), far(f)
{
  mouseXScale = 0.5f;
  mouseYScale = 0.5f;
  dir = lookAt - eyePos;
  float l = glm::length(dir);
  pitch = asinf( dir.y / l );
  pitch = glm::degrees(pitch);
  //std::cout << "pitch: " << pitch << "\n";
  float dirl = sqrt( dir.x*dir.x + dir.z*dir.z );
  yaw = asinf( dir.z / dirl );
  yaw = glm::degrees(yaw);
  //std::cout << "yaw: " << yaw << "\n";
  pitchMax = 89.f;
  pitchMin = -89.f;

  forward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  forward.y = 0.f;
  forward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  forward = glm::normalize(forward);
  right = glm::cross(forward,glm::vec3(0.f,1.f,0.f));
}

Camera::~Camera()
{}

glm::mat4
Camera::GetLook(){
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(viewAngle),
    ratio, near, far);
  glm::mat4 view;
  view = glm::lookAt(eyePos, lookAt, up);
  return projection * view;
}

void
Camera::SetLook(Shader* shader_)
{
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(viewAngle),
    ratio, near, far);
  glm::mat4 view;
  view = glm::lookAt(eyePos, lookAt, up);
  view = projection * view;
  shader_->SetMatrix4("view", glm::value_ptr(view));
  shader_->SetVector3("viewPosition", glm::value_ptr(eyePos));
}

void
Camera::MoveNX(float dt)
{
  float ds = vel.x * dt;
  eyePos.x -= ds;
  lookAt.x -= ds;
}

void
Camera::MovePX(float dt)
{
  float ds = vel.x * dt;
  eyePos.x += ds;
  lookAt.x += ds;
}

void
Camera::MoveNY(float dt)
{
  float ds = vel.y * dt;
  eyePos.y -= ds;
  lookAt.y -= ds;
}

void
Camera::MovePY(float dt)
{
  float ds = vel.y * dt;
  eyePos.y += ds;
  lookAt.y += ds;
}

void
Camera::MoveNZ(float dt)
{
  float ds = vel.z * dt;
  eyePos.z -= ds;
  lookAt.z -= ds;
}

void
Camera::MovePZ(float dt)
{
  float ds = vel.z * dt;
  eyePos.z += ds;
  lookAt.z += ds;
}

void
Camera::SetRatio(float ratio_)
{
  ratio = ratio_;
}

void
Camera::UpdatePitchYaw(int mouseX_, int mouseY_)
{
  yaw += mouseXScale * (float)mouseX_;
  if( yaw > 360.f ) yaw -= 360.f;
  if( yaw < 0.f ) yaw += 360.f;
  pitch -= mouseYScale * (float)mouseY_;
  if( pitch > pitchMax) pitch = pitchMax;
  if( pitch < pitchMin) pitch = pitchMin;

  dir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  dir.y = sin(glm::radians(pitch));
  dir.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

  lookAt.x = eyePos.x + dir.x;
  lookAt.y = eyePos.y + dir.y;
  lookAt.z = eyePos.z + dir.z;

  forward.x = dir.x;
  forward.y = 0.f;
  forward.z = dir.z;
  forward = glm::normalize(forward);
  right = glm::cross(forward,glm::vec3(0.f,1.f,0.f));
}

void
Camera::SetMouseScale(float mouseXScale_, float mouseYScale_)
{
  mouseXScale = mouseXScale_;
  mouseYScale = mouseYScale_;
}

void
Camera::MoveForward(float dt)
{
  float ds = vel.z * dt;
  eyePos += forward * ds;
  lookAt += forward * ds;
}

void
Camera::MoveBackward(float dt)
{
  float ds = vel.z * dt;
  eyePos -= forward * ds;
  lookAt -= forward * ds;
}

void
Camera::MoveRight(float dt)
{
  float ds = vel.x * dt;
  eyePos += right * ds;
  lookAt += right * ds;
}

void
Camera::MoveLeft(float dt)
{
  float ds = vel.x * dt;
  eyePos -= right * ds;
  lookAt -= right * ds;
}

void Camera::Update() {
  dir = lookAt - eyePos;
  float l = glm::length(dir);
  pitch = asinf( dir.y / l );
  pitch = glm::degrees(pitch);
  //std::cout << "pitch: " << pitch << "\n";
  float dirl = sqrt( dir.x*dir.x + dir.z*dir.z );
  yaw = asinf( dir.z / dirl );
  yaw = glm::degrees(yaw);
  //std::cout << "yaw: " << yaw << "\n";
  forward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  forward.y = 0.f;
  forward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  forward = glm::normalize(forward);
  right = glm::cross(forward,glm::vec3(0.f,1.f,0.f));
}
