#include "RenderEngine.h"

RenderEngine::RenderEngine(
	unsigned int maGL_,// Major OpenGL version
	unsigned int miGL_, // Minor OpenGL version
	unsigned int screenWidth_,// Screen width
	unsigned int screenHeight_,// Screen height
  std::string windowTitle_
) : screenWidth(screenWidth_), screenHeight(screenHeight_),
    maGL(maGL_), miGL(miGL_),
    windowTitle(windowTitle_)
{
  fpsTimerSpan = 1.;
}

RenderEngine::~RenderEngine() {}


void
RenderEngine::InitData()
{
  UserInitData();
}


void
RenderEngine::Close(){
  UserClose();
  // Delete OpenGL context
  SDL_GL_DeleteContext( glContext );
  // Destroy window
  SDL_DestroyWindow( gameWindow );
  gameWindow = NULL;
  // Quit SDL subsystems
  SDL_Quit();
}


void
RenderEngine::Draw()
{
  // Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  UserDraw();
}


void
RenderEngine::Update(float dt){
  currKeyStates = SDL_GetKeyboardState( NULL );
  UserUpdate(dt);
}

void
RenderEngine::UpdateView(SDL_Event &event){
  screenWidth = (unsigned int)event.window.data1;
  screenHeight = (unsigned int)event.window.data2;
  std::cout << "Window resized: " << screenWidth << " x "
            << screenHeight << std::endl;
  UserUpdateView(event);
}

void
RenderEngine::UserInitData() {}

void
RenderEngine::UserClose() {}

void
RenderEngine::UserDraw() {}

void
RenderEngine::UserUpdate(float dt) {}

void
RenderEngine::UserUpdateView(SDL_Event &event) {}

bool
RenderEngine::Init(){
  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    std::cout << "SDL could not initialize! SDL Error: "
	      << SDL_GetError() << std::endl;
    return false;
  }
  // Use OpenGL 3.3
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, maGL );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, miGL );
  // Create window
  gameWindow = SDL_CreateWindow(
    windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
  if( gameWindow == NULL ){
    std::cout << "Window could not be created! SDL Error: "
		  << SDL_GetError() << std::endl;
    return false;
  }
  // Create OpenGL context
  glContext = SDL_GL_CreateContext( gameWindow );
  if( glContext == NULL ){
	  std::cout << "OpenGL context could not be created! SDL Error: "
		  << SDL_GetError() << std::endl;
	   return false;
  }
  //Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
	  std::cout << "Warning: Unable to set VSync! SDL Error: "
		  << SDL_GetError() << std::endl;
	}
  //Initialize OpenGL
  if( !InitGL() )
	{
	  std::cout << "Unable to initialize OpenGL!\n";
	  return false;
	}

  return true;
}


bool
RenderEngine::InitGL()
{
  GLenum error = GL_NO_ERROR;
  if( maGL <= 2 )
  {
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ){
      std::cout << "Error initializing OpenGL! "
	      << gluErrorString( error ) << std::endl;
      return false;
    }
    //Initialize clear color
    glClearColor( 0.3f, 0.3f, 0.3f, 1.f );
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ){
      std::cout << "Error initializing OpenGL! "
	      << gluErrorString( error ) << std::endl;
      return false;
    }
  } else {
    //Initialize clear color
    glClearColor( 0.3f, 0.3f, 1.f, 1.f );
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ){
      std::cout << "Error initializing OpenGL! "
	      << gluErrorString( error ) << std::endl;
      return false;
    }
  }
  // Initialize GLEW
  glewExperimental = true;
  if( glewInit() != GLEW_OK ){
    std::cout << "Failed to initialize GLEW.\n";
    return false;
  }
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  return true;
}


void
RenderEngine::PollEvents(){
  SDL_Event e;
  // Handle events on queue one by one
  while( SDL_PollEvent( &e ) ){
    switch( e.type ){
      case SDL_QUIT:// Application requests quit
        quit = true;
      break;// case SDL_QUIT:
      case SDL_WINDOWEVENT:// Window state change
        switch(e.window.event){
          case SDL_WINDOWEVENT_RESIZED:
            UpdateView(e);
          break;
        }
      break;
      case SDL_KEYDOWN:
        switch( e.key.keysym.sym ){
          case SDLK_ESCAPE:// Escape terminates game
	          quit = true;
	        break;
          case SDLK_LSHIFT:
	          lShift = true;
	        break;
          case SDLK_v:
	          if( lShift == true ){
	            if( SDL_GL_SetSwapInterval( 0 ) < 0 ){
	              std::cout << "Warning: Unable to switch off VSync! SDL Error: "
		              << SDL_GetError() << std::endl;
	            } else {
	              std::cout << "VSync off" << std::endl;
	            }
	          } else {
	            if( SDL_GL_SetSwapInterval( 1 ) < 0 ){
	              std::cout << "Warning: Unable to switch on VSync! SDL Error: "
		              << SDL_GetError() << std::endl;
	            } else {
	              std::cout << "VSync on" << std::endl;
	            }
	          }
	        break;// case SDLK_v:
          case SDLK_p:
            if( !timePaused ){
              timePaused = true;
              std::cout << "Pause ON" << std::endl;
            } else {
              timePaused = false;
              std::cout << "Pause OFF" << std::endl;
            }
          break;
          case SDLK_l:
            if( !wireDraw ){
              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
              wireDraw = true;
              std::cout << "Wireframe" << std::endl;
            } else {
              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
              wireDraw = false;
              std::cout << "Solid" << std::endl;
            }
          break;
        }// switch( e.key.keysym.sym )
      break;//case SDL_KEYDOWN:
      case SDL_KEYUP:
        switch( e.key.keysym.sym ){
          case SDLK_LSHIFT:
            lShift = false;
	        break;
        }
      break;// case SDL_KEYUP:
    }
  }
}


void
RenderEngine::Run(){
  InitData();
  hiResFreq = SDL_GetPerformanceFrequency();
  hiResTick = 1. / (double)hiResFreq;
  currentTime = SDL_GetPerformanceCounter();
  lastTime = currentTime;
  std::cout << "Hi-resolution tick: " << hiResTick << " sec." << std::endl;
  SDL_Delay( 1 );// Wait 1 milisecond
  /*
    The game loop
  */
  fpsTimer = 0.;
  while( !quit ){
    // Timing
    currentTime = SDL_GetPerformanceCounter();
    elapsedTime = currentTime - lastTime;
    lastTime = currentTime;
    dt = (double)elapsedTime * hiResTick;
    fpsTimer += dt;
    if( fpsTimer > fpsTimerSpan )
    {
	    fpsTimer -= 1.;
	    fps = 1. / dt;// Frame per second
	    std::cout << "FPS = " << fps << std::endl;
	  }
    PollEvents();// Event processing
    if( !timePaused ){
      Update((float)dt);// Update game: collisions, physics, AI, etc. ...
    }
    Draw();// Render scene (frame)
    SDL_GL_SwapWindow( gameWindow );// Swap buffers
  }// while( !quit )
  Close();
}
