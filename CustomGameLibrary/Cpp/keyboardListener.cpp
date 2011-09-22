#include "../Header/keyboardlistener.h"

namespace cgl
{
	KeyboardListener::KeyboardListener()
	{
		int numberOfKeys = 33;
		char allowedKeys[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z', '\t', '\n', 'x91', 'x9B', 'x86', '\b', 'esc', '0x1B' };
		//Prolly swap with VK_Escape, etc, and change the type... of the map <char..> to map<VK_Key?>...
		for(int i = 0; i < numberOfKeys; i++)
		{
			this->key[allowedKeys[i]] = false;
		}
	}

	bool KeyboardListener::isKeyPressed(std::string keyPressed)
	{
		return this->key[keyPressed[0]];
	}

	void KeyboardListener::KeyPressed(std::string keyPressed)
	{
		this->key[keyPressed[0]] = true;
	}

	void KeyboardListener::KeyReleased(std::string keyReleased)
	{
		this->key[keyReleased[0]] = false;
	}
	
	void KeyboardListener::KeyPressed(char keyPressed)
	{
		this->key[keyPressed] = true;
	}
	
	void KeyboardListener::KeyReleased(char keyReleased)
	{
		this->key[keyReleased] = false;
	}
}