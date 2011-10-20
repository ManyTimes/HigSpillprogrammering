#include "../Header/keyboard.h"

namespace cgl
{
	Keyboard* Keyboard::instance = NULL;
	Keyboard* Keyboard::GetInstance()
	{
		if(!instance)
		{
			instance = new Keyboard();
			//SET THE KEYCALLBACK OF THE OPENGL TO A BUILTIN FUNCTION
			glfwSetKeyCallback(cgl::Keyboard::KeyboardCallback);
		}
		return instance;
	}

	Keyboard::Keyboard()
	{
		//LEGAL CHARACTERS/KEYBOARD CLICKS
		std::string boardkeys[] = { " ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Æ", "Ø", "Å",
								"TAB", "ESC", "RSHIFT", "LSHIFT", "RCNTRL", "LCNTRL", "CAPS", "NUMLOCK", "RETURN", "ENTER", "BACKSPACE", 
								"F1", "F2","F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", 
								"LEFT", "RIGHT", "UP", "DOWN",
								"0", "1", "2", "3", "4", "5", "6", "7", "8","9", "?"};

		//MAP THE KEYS TO AN INTEGER VALUE. INTEGER VALUE IS ALREADY DEFINED AS A BUTTON WITHIN THE GL LIBRARY
		int length = cgl::GetArrayLength(boardkeys);
		for(int i = 0; i < length; i++)
		{
			if(i < 27)									//Maps space and the english alphabet
			{
				conversion[boardkeys[i]] = boardkeys[i][0];
			}
			else
			{		
				if(i < 67 && i > 56)					//Maps numeric values 0-9
				{
					conversion[boardkeys[i]] = boardkeys[i][0];
				}	
			}
		}
		conversion["Æ"] = 198;							//Maps other words to their specified integers
		conversion["Ø"] = 216;
		conversion["Å"] = 197;
		conversion["TAB"] = 293;
		conversion["TABULATOR"] = 293;
		conversion["ESC"] = 257;
		conversion["ESCAPE"] = 257;
		conversion["RSHIFT"] = 287;
		conversion["RIGHTSHIFT"] = 287;
		conversion["LSFHIT"] = 288;
		conversion["LEFTSFHIT"] = 288;
		conversion["RCNTRL"] = 290;
		conversion["RCONTROL"] = 290;
		conversion["RIGHTCONTROL"] = 290;
		conversion["LCNTRL"] = 289;
		conversion["LCONTROL"] = 289;
		conversion["LEFTCONTROL"] = 289;
		conversion["CAPS"] = 320;
		conversion["CAPSLOCK"] = 320;
		conversion["NUMLOCK"] = 319;
		conversion["RETURN"] = 294;
		conversion["ENTER"] = 294;
		conversion["BACKSPACE"] = 295;
		conversion["F1"] = 258;
		conversion["F2"] = 259;
		conversion["F3"] = 260;
		conversion["F4"] = 261;
		conversion["F5"] = 262;
		conversion["F6"] = 263;
		conversion["F7"] = 264;
		conversion["F8"] = 265;
		conversion["F9"] = 266;
		conversion["F10"] = 267;
		conversion["F11"] = 268;
		conversion["F12"] = 269;
		conversion["LEFT"] = 285;
		conversion["RIGHT"] = 286;
		conversion["UP"] = 283;
		conversion["DOWN"] = 284;

		for(int i = 0; i < 321; i++)
		{
			key[i] = false;
		}
	}

/*	char Keyboard::LookupTable(int keyButton)			//Takes key, returns char
	{
	}

	std::string Keyboard::LookupTable(int keyButton)	//Takes button, returns string
	{
		
	}*/


	/************BUILT IN CALLBACK ****************/

	void GLFWCALL Keyboard::KeyboardCallback(int keybutton, int action)
	{
		std::cout << keybutton << std::endl;					//A key is clicked
		if(instance->isKeyAllowed(keybutton) == true)
		{
			if(action == GLFW_PRESS)
			{
				instance->key[keybutton] = true;				
			}
			else
			{
				instance->key[keybutton] = false;
			}
			/*switch (key) 
			{
				case 'A' : keys[KEY_LEFT] = action == GLFW_PRESS ? true : false; break;
				case 'D' : keys[KEY_RIGHT] = action == GLFW_PRESS ? true : false; break;
				case 'S' : keys[KEY_BACK] = action == GLFW_PRESS ? true : false; break;
				case 'W' : keys[KEY_FORWARD] = action == GLFW_PRESS ? true : false; break;
				case ' ' : keys[KEY_UP] = action == GLFW_PRESS ? true : false; break;
				case 'C' : keys[KEY_DOWN] = action == GLFW_PRESS ? true : false; break;
				case GLFW_KEY_ESC : { CloseWindow(); glfwCloseWindow(); } break;
				case GLFW_KEY_KP_ADD : keys[KEY_PLUS] = action == GLFW_PRESS ? true : false; break;
				case GLFW_KEY_KP_SUBTRACT : keys[KEY_MINUS] = action == GLFW_PRESS ? true : false; break;
			}*/
		}
	}


	bool Keyboard::isKeyAllowed(int keyPressed)
	{
		if(keyPressed < 321)
		{
			return true;
		}
	/*	if(keyPressed > 64 && keyPressed < 91)				//alphabet a-z
		{
			return true;
		}
		if(keyPressed > 47 && keyPressed < 58)				//numeric 0-9
		{
			return true;
		}
		//				space			questionmark			escape
		if(keyPressed == 32 || keyPressed == 43 || keyPressed == 257)		
		{
			return true;
		}
		if(keyPressed > 292 && keyPressed < 295)			//tab, enter/return, backspace
		{
			return true;
		}
		if(keyPressed > 286 && keyPressed < 291)			//Left or right shift, left or right cntrl
		{
			return true;
		}
		if(keyPressed > 301 && keyPressed < 312)			//numpad numbers
		{
			return true;
		}
		if(keyPressed == 320)								//capslock
		{
			return true;
		}
		if(keyPressed > 282 && keyPressed < 287)			//Arrow keys
		{
			return true;
		}
		if(keyPressed > 257 && keyPressed < 270)			//F1 - F12
		{
			return true;
		}
		if(keyPressed == 197 || keyPressed == 198 || keyPressed == 216)	//Æ Ø Å
		{
			return true;
		}
		if(keyPressed > 43 && keyPressed < 47)				// , . -
		{
			return true;
		}*/
		return false;
	}

	/*void Keyboard::SetKeyPressed(char keyPressed)
	{
		instance->key[keyPressed] = true;
	}

	void Keyboard::SetKeyReleased(char keyReleased)
	{
		instance->key[keyReleased] = true;
	}*/

	
	bool Keyboard::isKeyPressed(std::string keyPressed)
	{
		return instance->key[conversion[keyPressed]];			//Maps a string to an int, which again maps to either true (if pressed) or false (not pressed)
	}

	/*bool Keyboard::isKeyPressed(char keyPressed)
	{
		return instance.key[keyPressed];
	}*/

	/*void Keyboard::KeyPressed(std::string keyPressed)
	{
		instance.key[keyPressed[0]] = true;
	}

	void Keyboard::KeyReleased(std::string keyReleased)
	{
		instance.key[keyReleased[0]] = false;
	}
	
	void Keyboard::KeyPressed(char keyPressed)
	{
		instance.key[keyPressed] = true;
	}*/
	
	/*void Keyboard::KeyReleased(char keyReleased)
	{
		instance.key[keyReleased] = false;
	}*/
}