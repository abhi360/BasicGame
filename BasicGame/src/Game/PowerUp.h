#pragma once

#include <GameObject.h>

const glm::vec2 POWUPSIZE(60, 20);
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
	// PowerUp State
	std::string Type;
	GLfloat     Duration;
	GLboolean   Activated;
	// Constructor
	PowerUp(std::string type, glm::vec3 color, GLfloat duration,
		glm::vec2 position, Texture2D texture)
		: GameObject(position, POWUPSIZE, texture, color, VELOCITY),
		Type(type), Duration(duration), Activated()
	{ }
};
