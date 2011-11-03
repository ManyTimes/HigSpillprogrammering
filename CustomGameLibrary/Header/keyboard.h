#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "include.h"				//All classes, objects within the library requires this include.
#include "function.h"
#include <map>
#include <iostream>
#include "includegl.h"

namespace cgl
{
	class DECLARE Keyboard
	{
	private:
		int numberOfKeys;
		std::map<int, bool> key;							//From 0 - 320, 320 is "the last button" on a keyboard; the numlock on/off
		std::map<std::string, int> conversion;				//Maps string to integer
		static Keyboard* instance;
		static void GLFWCALL Keyboard::KeyboardCallback(int key, int action);
		static void Keyboard::SetKeyPressed(char keyPressed);
		static void Keyboard::SetKeyReleased(char keyReleased);
		bool Keyboard::isKeyAllowed(int keyPressed);
		Keyboard::Keyboard();
		//GLFWCALL Keyboard::KeyboardCallback(int key, int action);
		//void Keyboard::KeyboardCallback(int key, int action);
	public:
		//Returns a Keyboard objectasdasd
		static Keyboard* GetInstance();
		bool Keyboard::isKeyPressed(std::string keyPressed);
		bool Keyboard::isKeyPressed(char keyPressed);
	/*	void Keyboard::KeyPressed(std::string keyPressed);
		void Keyboard::KeyReleased(std::string keyReleased);
		void Keyboard::KeyPressed(char keyPressed);
		void Keyboard::KeyReleased(char keyReleased);*/
	};
}

#endif