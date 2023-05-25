#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Camera {
 public:
  enum {
    FPS_CAMERA = 0,
    MDL_CAMERA = 1
  };

  enum {
    PERSPECTIVE_PROJECTION = 0,
    ORTHO_PROJECTION = 1
  };

  unsigned int cameraType;
  unsigned int projectionType;
  glm::vec3 eyePos;
  glm::vec3 lookAt;
  glm::vec3 up;
  glm::vec3 vel;
  float viewAngle, ratio, near, far;
  float yaw, pitch;
  float pitchMax, pitchMin;
  float mouseXScale, mouseYScale;
  glm::vec3 dir;
  glm::vec3 forward;
  glm::vec3 right;

  Camera(
	  float = 0.f, float = 0.f, float = 2.f, // Camera position
	  float = 0.f, float = 0.f, float = 0.f, // Look at position
    float = 1.f, float = 1.f, float = 1.f, // Camera velocity
	  float = 0.f, float = 1.f, float = 0.f, // Up vector
	  float = 50.f, float = 4.f/3.f, float = 0.1f, float = 100.f,
	  // View angle, ratio, near, far
    unsigned int = FPS_CAMERA, // Camera type
	  unsigned int = PERSPECTIVE_PROJECTION // Projection type
  );
  ~Camera();
  glm::mat4 GetLook();
  void SetLook(Shader*);
  void MoveNX(float);
  void MovePX(float);
  void MoveNY(float);
  void MovePY(float);
  void MoveNZ(float);
  void MovePZ(float);
  void SetRatio(float);
  void UpdatePitchYaw(int, int);
  void SetMouseScale(float, float);
  void MoveForward(float);
  void MoveBackward(float);
  void MoveRight(float);
  void MoveLeft(float);
  void Update();
};

#endif
