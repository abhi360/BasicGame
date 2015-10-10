#pragma once
#define GLEW_STATIC
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class sdlWindow
{
public:
	sdlWindow();
	~sdlWindow();
	
private:
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	//OpenGL context
	SDL_GLContext gContext;

public:
	SDL_Window* sdlwindow() { return gWindow; }
	bool Initialize();
	void Close();
};

