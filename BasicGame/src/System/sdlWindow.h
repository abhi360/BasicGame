#pragma once
#define GLEW_STATIC
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream> 

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class sdlWindow
{
public:
	sdlWindow();
	~sdlWindow();
	
private:
	//The window we'll be rendering to
	SDL_Window* mWindow = NULL;
	//OpenGL context
	SDL_GLContext mContext;
	 

public:
	SDL_Window* sdlwindow() { return mWindow; }
	bool Initialize();
	void Close();
	//Handles window events
	void HandleEvent(SDL_Event& e);

	//Window dimensions
	int GetWidth();
	int GetHeight();

	//Window focii
	bool HasMouseFocus();
	bool HasKeyboardFocus();
	bool IsMinimized();

private:
	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
};

