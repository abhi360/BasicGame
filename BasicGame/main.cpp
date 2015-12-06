#include <sdlWindow.h>
#include <InputManager.h>
#include <Game.h>

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);
const GLfloat TARGET_FRAME_PER_SECOND = 60;
const GLuint AVG_FRAME_COUNT = 5;

int main(int argc, char* args[])
{
	GLuint count = 0;
	float FPS = 0;
	GLfloat startTime = 0;
	sdlWindow window;
	InputManager inputManager;
	//Start up SDL and create window
	if (!window.Initialize())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		startTime = SDL_GetTicks();
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		// Initialize game
		Breakout.Init();

		// DeltaTime variables
		GLfloat deltaTime = 0.0f;
		GLfloat lastFrame = 0.0f;
		GLuint frames = 0;
		
		// Start Game within Menu State
		Breakout.State = GAME_MENU;

		//While application is running
		while (!quit)
		{

			// Calculate delta
			GLfloat currentFrame = SDL_GetTicks();
			deltaTime = (currentFrame - lastFrame);
			lastFrame = currentFrame;
			
			//printf("%f\n", deltaTime);
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					quit = true;

				window.HandleEvent(e);
				
				if (e.type == SDL_KEYDOWN)
					inputManager.presskey(e.key.keysym.sym);

				Breakout.ProcessInput(deltaTime/1000,e,inputManager);


				if (e.type == SDL_KEYUP)
					inputManager.releasekey(e.key.keysym.sym);

				
			}

			int x = 0, y = 0;
			SDL_GetMouseState(&x, &y);
			float a = (float)x/window.GetWidth() * 2 - 1;
			float b = 1 - (float)y/window.GetHeight() * 2;
			//printf("%f , %f\n", a, b);

			// Update the game state
			

			// Update Game state
			Breakout.Update(deltaTime/1000);





			//Render
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Breakout.Render();
			//Update screen
			SDL_GL_SwapWindow(window.sdlwindow());

			//Render quad
			//render();
			frames++;

			if (SDL_GetTicks() - startTime >  1000.0f)
			{
				float fps = frames / ((SDL_GetTicks() - startTime)/1000);
				FPS += fps;
				count++;
				startTime = SDL_GetTicks();
				frames = 0;
				
				if (count == AVG_FRAME_COUNT)
				{
					FPS = FPS / count;
					printf("FPS : %f\n", fps);
					count = 0;
				}
			}
			
			if (SDL_GetTicks() - currentFrame < 1000 / TARGET_FRAME_PER_SECOND)
			{
				//printf("%f\n", deltaTime);
				//Sleep the remaining frame time
				SDL_Delay((1000 / TARGET_FRAME_PER_SECOND) - (SDL_GetTicks() - currentFrame));
			}
		}

		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	window.Close();

	return 0;
}