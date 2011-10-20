#include "../Header/mouse.h"

namespace cgl
{
	Mouse* Mouse::instance = NULL;
	Mouse* Mouse::GetInstance(int screenWidth, int screenHeight)
	{
		if(!instance)
		{
			instance = new Mouse();
			//SET THE BUTTONCALLBACK OF THE OPENGL TO A BUILTIN FUNCTION
			glfwSetMouseButtonCallback(cgl::Mouse::ButtonCallback);
		
			//PROGRAM BUGS IF THIS IS UNCOMMENTED; STRANGE AS HELL
			glfwSetMousePosCallback(cgl::Mouse::PositionCallback);
			if(screenWidth < 1)
			{
				screenWidth = 800;
			}
			if(screenHeight < 1)
			{
				screenHeight = 600;
			}
			instance->screenHeight = screenHeight;
			instance->screenWidth = screenWidth;
			instance->enableCustomMouseCursor = false;
			instance->enableMouseFrame = false;
			instance->SetCursorPosition(screenWidth/2, screenHeight/2);
		}
		return instance;
	}

	Mouse::Mouse()
	{
		cursorx = 0;
		cursory = 0;
		conversion["LEFT"] = 0;
		conversion["RIGHT"] = 1;
		conversion["MIDDLE"] = 2;
		conversion["0"] = 0;
		conversion["1"] = 1;
		conversion["2"] = 2;
		conversion["LEFTBUTTON"] = 0;
		conversion["RIGHTBUTTON"] = 1;
		conversion["MIDDLEBUTTON"] = 2;

		for(int i = 0; i < 3; i++)
		{
			mousebutton[i] = false;
		}
	}

	void GLFWCALL Mouse::ButtonCallback( int button, int action )
	{
		if(action == 1)
		{
			instance->mousebutton[button] = true;			//Press
		}
		else
		{
			instance->mousebutton[button] = false;			//Release
		}
		//Button 0 : Left button
		//Button 1 : Right button
		//Button 2 : Middle button
		//Action 1 : Press
		//Action 0 : Release
	}
	void GLFWCALL Mouse::PositionCallback(int x, int y)
	{
		instance->cursorx = x;
		instance->cursory = y;
	}

	int Mouse::GetCursorPositionX()
	{
		return instance->cursorx;
	}

	int Mouse::GetCursorPositionY()
	{
		return instance->cursory;
	}

	void Mouse::SetCursorPosition(int x, int y)
	{
		glfwSetMousePos(x,y);
	}


	void Mouse::ShowCustomCursor(bool enable)
	{
		instance->enableCustomMouseCursor = enable;
		if(enable == true)
		{
			glfwDisable(GLFW_MOUSE_CURSOR);
		}
	}
	void Mouse::ShowWindowsCursor(bool enable)
	{
		if(enable == true)
		{
			instance->enableCustomMouseCursor = false;
			glfwEnable(GLFW_MOUSE_CURSOR);
		}
		else
		{
			glfwDisable(GLFW_MOUSE_CURSOR);
		}
	}

	bool Mouse::isButtonPressed(int buttonPressed)
	{
		return instance->mousebutton[buttonPressed];
	}

	bool Mouse::isButtonPressed(std::string buttonPressed)
	{
		return instance->mousebutton[conversion[buttonPressed]];
	}

	void Mouse::Draw(GLuint textureID)
	{
		if(instance->enableCustomMouseCursor == true)
		{
			Draw(textureID, 16,16);
		}
		else
		{
			instance->CursorFramed();
		}
	}

	void Mouse::Draw(GLuint textureID, int textureWidth, int textureHeight)
	{
		if(instance->enableCustomMouseCursor == true)
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
			glMatrixMode(GL_PROJECTION);	
			glPushMatrix();	
			glLoadIdentity();	
			glOrtho(0, instance->screenWidth, instance->screenHeight, 0, 0, 1);	
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();	
			glLoadIdentity();

			glBegin(GL_QUADS);														//Drawing the cursor								
				glTexCoord2f(1.0f, 0.0f); glVertex2i(instance->cursorx+textureWidth, instance->cursory);
				glTexCoord2f(0.0f, 0.0f); glVertex2i(instance->cursorx,	instance->cursory);
				glTexCoord2f(0.0f, 1.0f); glVertex2i(instance->cursorx,	instance->cursory+textureHeight);
				glTexCoord2f(1.0f, 1.0f); glVertex2i(instance->cursorx+textureWidth, instance->cursory+textureHeight);
			glEnd();

			glMatrixMode(GL_PROJECTION);	
			glPopMatrix();	
			glMatrixMode(GL_MODELVIEW);	
			glPopMatrix();
		}

		instance->CursorFramed();
	}

	void Mouse::Draw(Image2D& mouseImage, int textureWidth, int textureHeight)
	{
		if(instance->enableCustomMouseCursor == true)
		{
			glMatrixMode(GL_PROJECTION);	
			glPushMatrix();	
			glLoadIdentity();	
			glOrtho(0, instance->screenWidth, instance->screenHeight, 0, 0, 1);	
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();	
			glLoadIdentity();
			mouseImage.Draw(this->cursorx, this->cursory, textureWidth, textureHeight, false);
			glMatrixMode(GL_PROJECTION);	
			glPopMatrix();	
			glMatrixMode(GL_MODELVIEW);	
			glPopMatrix();
		}

		instance->CursorFramed();
	}

	void Mouse::CursorFramed()
	{
		if(instance->enableMouseFrame == true)
		{
			instance->outsideScreen = false;
			if(instance->cursorx > instance->screenWidth)
			{
				instance->cursorx = instance->screenWidth;
				instance->outsideScreen = true;
			}
			else
			{
				if(instance->cursorx < 0)
				{
					instance->cursorx = 0;
					instance->outsideScreen = true;
				}
			}
			if(instance->cursory > instance->screenHeight)
			{
				instance->cursory = instance->screenHeight;
				instance->outsideScreen = true;
			}
			else
			{
				if(instance->cursory < 0)
				{
					instance->cursory = 0;
					instance->outsideScreen = true;
				}
			}
			if(instance->outsideScreen == true)
			{
				instance->SetCursorPosition(instance->cursorx,instance->cursory);
			}
		}
	}
}