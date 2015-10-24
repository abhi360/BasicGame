#pragma once

#include <vector>

#include <GL/glew.h>
#include <SDL.h>
#include <ResourceManager.h>
#include <SpriteRenderer.h>

#include <GameLevel.h>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

class Game
{
private:
	// Game-related State data
	SpriteRenderer  *Renderer;
	GameObject *Player;

public:
	// Game state
	GameState  State;
	GLboolean  Keys[1024];
	GLuint	   Width, Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt,SDL_Event& e);
	void Update(GLfloat dt);
	void Render();
};




