#include <map>
#include <iostream>

namespace cgl
{
	class KeyboardListener
	{
	private:
		std::map<char, bool> key;
	public:
		KeyboardListener::KeyboardListener();
		bool KeyboardListener::isKeyPressed(std::string keyPressed);
		void KeyboardListener::KeyPressed(std::string keyPressed);
		void KeyboardListener::KeyReleased(std::string keyReleased);
		void KeyboardListener::KeyPressed(char keyPressed);
		void KeyboardListener::KeyReleased(char keyReleased);
	};
}