#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::presskey(unsigned int keyId)
{
	keyMap[keyId] = true;
}
void InputManager::releasekey(unsigned int keyId)
{
	keyMap[keyId] = false;
}

bool InputManager::isKeyPressed(unsigned int keyId)
{
	auto it = keyMap.find(keyId);
	if (it != keyMap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}
