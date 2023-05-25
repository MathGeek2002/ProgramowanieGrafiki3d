#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>

class RenderEngine
{
protected:
  unsigned int screenWidth, screenHeight;
  const unsigned char* currKeyStates;

private:
  unsigned int maGL, miGL;
  std::string windowTitle;
  SDL_Window* gameWindow;// The window we'll be rendering to
  SDL_GLContext glContext;// OpenGL context
  bool quit;// Main game loop flag
  bool lShift;// LShift pressed
  bool timePaused = false;// pause time
  bool wireDraw = false;// draw wireframe
  unsigned long hiResFreq;
  double hiResTick;
  unsigned long currentTime;
  unsigned long lastTime;
  double fpsTimer, fpsTimerSpan;
  unsigned long elapsedTime;
  double dt, fps;

public:
  RenderEngine(
		unsigned int = 2,// Major OpenGL version
		unsigned int = 1, // Minor OpenGL version
		unsigned int = 800,// Screen width
		unsigned int = 600,// Screen height
    std::string = "Programowanie Grafiki 3D"
	);
  virtual ~RenderEngine();

  bool Init();// Starts up SDL, creates window, and initializes OpenGL
  void Run();// Run main loop

private:
  bool InitGL();// OpenGL initialization
  void InitData();// Init data
  void Close();// Shuts down SDL and OpenGL
  void PollEvents();// Poll (process) events
  void Update(float);// Update game
  void UpdateView(SDL_Event &event);// Update view on window change
  void Draw();// Render scene

public:
  virtual void UserInitData();// Init data
  virtual void UserClose();// Close data
  virtual void UserUpdate(float);// Update game
  virtual void UserUpdateView(SDL_Event &event);// Update view
  virtual void UserDraw();// Render scene
};
