#include "View.h"
#include <GL/glew.h>

View::View(
	     unsigned int sW, unsigned int sH,
	     float x_, float y_,
	     float w_, float h_
	     )
: screenWidth(sW), screenHeight(sH),
  x(x_), y(y_), width(w_), height(h_)
{
  camera = new Camera;
  camera->SetRatio((float)(sW*width)/(float)(sH*height));
}

View::~View()
{
  delete camera;
}

void
View::SetScreen(unsigned int sW, unsigned int sH)
{
  screenWidth = sW;
  screenHeight = sH;
  camera->SetRatio((float)(sW*width)/(float)(sH*height));
}

glm::mat4
View::GetView()
{
  glViewport(
    x * screenWidth, y * screenHeight,
    width * screenWidth, height * screenHeight
  );

  return camera->GetLook();
}

void
View::SetView(Shader* shader_)
{
  glViewport(
    x * screenWidth, y * screenHeight,
    width * screenWidth, height * screenHeight
  );
  camera->SetLook(shader_);
}
