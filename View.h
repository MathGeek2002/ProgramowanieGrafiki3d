#ifndef VIEW_H
#define VIEW_H

#include "Camera.h"

class View {
 public:

  unsigned int screenWidth, screenHeight;
  float x, y;
  float width, height;
  Camera *camera;

  View(
    unsigned int, unsigned int, // screen widht, screen height
	  float = 0.f, float = 0.f, // position of lower left corner of viewport
    float = 1.f, float = 1.f // width and height of viewport
	);
  ~View();
  void SetScreen(unsigned int, unsigned int);
  glm::mat4 GetView();
  void SetView(Shader*);
};

#endif
