#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "View.h"
#include "Plane.h"
#include "Box.h"
#include "Lights.h"
#include "Materials.h"
#include "Image.h"

class MyRenderer : public RenderEngine
{
public:
  // 2.1 for old OpenGL and 3.3 for new OpenGL
  // or higher if your hardware supports it
  MyRenderer(unsigned int ma = 3, unsigned int mi = 3)
  : RenderEngine(ma,mi) {}

  // Overloaded methods called automaticaly by RenderEngine
  void UserInitData();// Prepare data
  void UserUpdate(float dt_);// Update data
  void UserDraw();// Draw frame
  void UserClose();// Clean if necessary
  void UserUpdateView(SDL_Event &);

  // View & camera
  View *view;
  // Shader program
  Shader *shader0, *shader1, *shader2, *shader3;

  Shader * depthShader,* shadowShader;
  
  Material * grass;

  // objects
  Model *plane;

  DirectionalLight * directionalLight0;
  DirectionalLight * directionalLight1;

  AmbientLight * ambientLight;

  PointLight * pointLight0;
  PointLight * pointLight1;

  float angle = 0.f;

  Model * box;
  Model * box2;

  UniformMaterial * gold = new UniformMaterial( UniformMaterial::GOLD );

  unsigned int depthMapFBO;
  unsigned int depthMap;
  const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
};

void MyRenderer::UserInitData()
{
  glEnable(GL_DEPTH_TEST);

  view = new View(screenWidth, screenHeight);
  view->camera->eyePos = glm::vec3(0.f, 2.f, 10.f);
  view->camera->lookAt = glm::vec3(0.f, 1.f, 0.f);
  view->camera->vel = glm::vec3(5.f, 5.f, 5.f);
  view->camera->Update();

  shader0 = new Shader(
    "Shaders/ViewTransform5.vert",
    "Shaders/Color.frag"
  );

  shader1 = new Shader(
    "Shaders/ViewTransform5.vert",
    "Shaders/PhongModel3.frag"
  );

  shader2 = new Shader(
    "Shaders/ViewTransform5.vert",
    "Shaders/PhongModel5.frag"
  );

  shader3 = new Shader(
    "Shaders/ViewTransform6.vert",
    "Shaders/PhongModel6.frag"
  );

  depthShader = new Shader(
    "Shaders/DepthShader.vert",
    "Shaders/DepthShader.frag"
  );

  grass = new TextureMaterial(
    "images/grass1_256x256.jpg", 64.f,
    "images/grass1_specular_256x256.jpg",
    "images/grass1_256x256.jpg"
  );

  shadowShader = new Shader(
    "Shaders/ShadowShader.vert",
    "Shaders/ShadowShader.frag"
  );

  ambientLight = new AmbientLight(0.1f,0.1f,0.1f);

  directionalLight0 = new DirectionalLight(
    0,
    0.f, -1.f, -1.f,
    0.08f,0.08f, 0.08f,
    0.8f, 0.8f, 0.8f,
    0.8f, 0.8f, 0.8f
  );

  directionalLight1 = new DirectionalLight(
    1,
    0.f, 1.f, 0.f,
    0.03f,0.03f, 0.03f,
    0.3f, 0.3f, 0.3f,
    0.5f, 0.5f, 0.5f
  );

  pointLight0 = new PointLight(
    0.f,0.f,0.f,
    0,
    0.1f,0.f,0.f,
    0.8f, 0.f,0.f,
    0.8f,0.f,0.f,
    1.f,0.1f,0.f);
  
  pointLight1 = new PointLight(
    0.f,0.f,0.f,
    1,
    0.1f,0.1f,0.f,
    0.f, 0.f,0.8f,
    0.f,0.f,0.8f,
    1.f,0.1f,0.05f);

  plane = new Plane(
    100, 100, 1.f, 1.f, Model::MATERIAL, 0.1f, 0.9f, 0.1f
  );
  glm::mat4 model(1.f);
  model = glm::scale(model, glm::vec3(10.f, 1.f, 10.f));
  plane->SetLocalTransform(model);

  Material * materials[6] = {gold,gold,gold,gold,gold,gold};

  box = new Box(1.f,1.f,1.f, materials, 6);

  model = glm::mat4(1.f);
  model = glm::translate(model,glm::vec3(0.f,0.9f,0.f));
  box->SetLocalTransform(model);

  box2 = new Box(1.f,1.f,1.f, materials, 6);

  model = glm::mat4(1.f);
  model = glm::translate(model,glm::vec3(0.2f,1.7f,3.f));
  box2->SetLocalTransform(model);

  glGenFramebuffers(1, &depthMapFBO);  

  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
              SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

void MyRenderer::UserClose()
{
  delete view;
  delete shader0;
  delete shader1;
  delete shader2;
  delete shader3;
  delete depthShader;
  delete shadowShader;
  delete plane;
  delete directionalLight0;
  delete directionalLight1;
  delete ambientLight;
  delete pointLight0;
  delete pointLight1;
  delete box;
  delete box2;
  delete gold;

  glDeleteTextures(1, &depthMap);
}

void MyRenderer::UserUpdate(float dt_)
{
  int mouseX, mouseY;
  if( SDL_GetRelativeMouseState(&mouseX, &mouseY) &
      SDL_BUTTON(SDL_BUTTON_RIGHT) ){
    //std::cout << "Right mouse button pressed\n";
    //std::cout << "Mouse position: (" << mouseX << "," << mouseY << ")\n";
    view->camera->UpdatePitchYaw(mouseX,mouseY);
  }

  if( currKeyStates[ SDL_SCANCODE_W ] ) view->camera->MoveForward(dt_);
  if( currKeyStates[ SDL_SCANCODE_S ] ) view->camera->MoveBackward(dt_);
  if( currKeyStates[ SDL_SCANCODE_A ] ) view->camera->MoveLeft(dt_);
  if( currKeyStates[ SDL_SCANCODE_D ] ) view->camera->MoveRight(dt_);
  if( currKeyStates[ SDL_SCANCODE_Z ] ) view->camera->MovePY(dt_);
  if( currKeyStates[ SDL_SCANCODE_C ] ) view->camera->MoveNY(dt_);

  angle += 15.f * dt_;

  if(angle >= 360.f ) angle -= 360.f;

  float x = 0.f;
  float y = sin(glm::radians(angle + 270.f));
  float z = cos(glm::radians(angle + 270.f));
  directionalLight0->SetDirection(x,y,z);
}

void MyRenderer::UserDraw()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  depthShader->Use();
  directionalLight0->SetLightViewMatrix(depthShader);
  
  glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

  glClear(GL_DEPTH_BUFFER_BIT);

  glDisable( GL_CULL_FACE );
  box->Draw(depthShader);
  box2->Draw(depthShader);
  plane->Draw(depthShader);
  glEnable( GL_CULL_FACE );

  glBindFramebuffer(GL_FRAMEBUFFER, 0);



  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shadowShader->Use();
  directionalLight0->SetLightViewMatrix(shadowShader);
  view->SetView(shadowShader);

  directionalLight0->SetLight(shadowShader);

  shadowShader->SetScalar1("shadowMap", 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, depthMap);


  box->Draw(shadowShader);
  box2->Draw(depthShader);
  plane->Draw(shadowShader);

  // shader2->Use();
  // view->SetView(shader2);
  // ambientLight->SetLight(shader2);
  // directionalLight0->SetLight(shader2);
  // box->Draw(shader2);

  // // Draw textured objects
  // shader3->Use();
  // view->SetView(shader3);
  // ambientLight->SetLight(shader3);
  // directionalLight0->SetLight(shader3);
  // plane->Draw(shader3);
}

void MyRenderer::UserUpdateView(SDL_Event &)
{
  view->SetScreen(screenWidth, screenHeight);
}

int main(int argc, char *argv[]){
  MyRenderer *myEngine = new MyRenderer(3,3);

  if( ! myEngine->Init() ){
    std::cout << "Unable to initialize game!\n";
  } else {
    myEngine->Run();
  }

  return 0;
}
