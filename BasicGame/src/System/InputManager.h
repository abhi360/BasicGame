#pragma once

#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void presskey(unsigned int keyId);
	void releasekey(unsigned int keyId);

	bool isKeyPressed(unsigned int keyId);

private:
	std::unordered_map<unsigned int, bool> keyMap;
};

