#pragma once

#include <vector>
#include <algorithm>
#include <sstream>
//#include <tuple>
#include <GL/glew.h>
#include <SDL.h>
#include <ResourceManager.h>
#include <SpriteRenderer.h>
#include <BallObject.h>
#include <GameLevel.h>
#include <ParticleGenerator.h>
#include <PostProcessor.h>
#include <PowerUp.h>
#include <TextRenderer.h>
#include <irrKlang.h>
#include <InputManager.h>
#include <SDL.h>
using namespace irrklang;

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Represents the four possible (collision) directions
enum Direction 
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;
// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(600.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

class Game
{
private:
	// Game-related State data
	ParticleGenerator   *Particles;
	SpriteRenderer  *Renderer;
	GameObject *Player;
	BallObject     *Ball;
	PostProcessor     *Effects;
	GLfloat            ShakeTime ;
	TextRenderer  *Text;

public:
	// Game state
	GameState  State;
	GLboolean  Keys[1024];
	GLuint	   Width, Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	std::vector<PowerUp>   PowerUps;
	GLuint                 Lives;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt,SDL_Event& e, InputManager& input);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();

private:
	GLboolean CheckCollision(GameObject &one, GameObject &two);
	Collision CheckCollision(BallObject &one, GameObject &two);
	inline float clamp(float value, float min, float max) { return std::max(min, std::min(max, value)); }
	Direction VectorDirection(glm::vec2 target);
	// Reset
	void ResetLevel();
	void ResetPlayer();
	// Powerups
	void SpawnPowerUps(GameObject &block);
	void UpdatePowerUps(GLfloat dt);
	void ActivatePowerUp(PowerUp &powerUp);
};




