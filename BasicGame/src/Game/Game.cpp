#include "Game.h"



Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height),Renderer(NULL),Player(NULL)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("src/Shader/shader_vertex.vert", "src/Shader/shader_fragment.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("src/Textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("src/Textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("src/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("src/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("src/Textures/paddle.png", GL_TRUE , "paddle");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Load levels
	GameLevel one; one.Load("src/Level/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("src/Level/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("src/Level/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("src/Level/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 3;
	// Configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt,SDL_Event& e)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat ds = PLAYER_VELOCITY * dt;
		// Move playerboard
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_a)
			{
				if (Player->Position.x >= 0)
					Player->Position.x -= ds;
			}
			if (e.key.keysym.sym == SDLK_d)
			{
				if (Player->Position.x <= this->Width - Player->Size.x)
					Player->Position.x += ds;
			}
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
		
	}
}
