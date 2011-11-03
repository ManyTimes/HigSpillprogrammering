#include "../Header/button.h"

namespace cgl
{
	Button::Button(cgl::Mouse* mouseObject, int screenWidth, int screenHeight, int viewportWidth, int viewportHeight, int viewportStartPositionX, int viewportStartPositionY, int buttonPositionX, int buttonPositionY)
	{
		this->width = 10;
		this->height = 10;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		this->positionX = buttonPositionX;
		this->positionY = buttonPositionY;

		//this->maxY = this->screenHeight - viewportStartPositionY - this->positionY;	//Max Y edge of the button
		//this->minY = maxY - this->height; 
		//this->minY = screenHeight - buttonPositionY;
		//this->maxY = minY - this->height;
		this->minY = viewportStartPositionY + this->positionY;
		this->maxY = this->minY + this->height;
		this->maxcursorY = screenHeight - buttonPositionY - viewportStartPositionY;
		this->mincursorY = maxcursorY - this->height;
		this->minX = viewportStartPositionX + this->positionX;
		this->maxX = this->minX + this->width;

		this->mouse = mouseObject;
		this->leftclick = true;
		this->rightclick = false;
	}

	void Button::SetSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		this->maxX = this->minX + this->width;
		//his->minY = maxY + this->height;
		this->maxY = this->minY + this->height;
		this->mincursorY = maxcursorY - this->height;
	}

	void Button::SetTexture(GLuint textureID, GLuint buttonClickedTextureID)
	{
		this->textureID = textureID;
		this->buttonClickedTextureID = buttonClickedTextureID;
	}

	bool Button::isPressed()
	{
		if(this->leftclick == true)							//Either left or right requires to be set to true
		{
			if(this->mouse->isButtonPressed(0) == true)		//Either is pushed
			{
				if(this->mouse->cursorx > this->minX && this->mouse->cursorx < this->maxX)		//X of cursor is within button
				{
					if(this->mouse->cursory > this->mincursorY && this->mouse->cursory < this->maxcursorY)
					{
						return true;
					}
				}
			}
		}
		else
		{
			if(this->rightclick == true)
			{
				if(this->mouse->isButtonPressed(1) == true)
				{
					if(this->mouse->cursorx > this->minX && this->mouse->cursorx < this->maxX)		//X of cursor is within button
					{
						if(this->mouse->cursory > this->minY && this->mouse->cursory < this->minY)
						{
							return true;
						}
					}
				}
			}
		}	
		return false;
	}

	void Button::Draw()
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
		if(this->isPressed() == true)
		{
			glBindTexture(GL_TEXTURE_2D, this->buttonClickedTextureID);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
		}
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(this->maxX, this->minY);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(this->minX, this->minY);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(this->minX, this->maxY);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(this->maxX, this->maxY);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	//NOT IN USE ANYMORE
	void Button::BeginDrawButtons()
	{
		glMatrixMode(GL_PROJECTION);	
		glPushMatrix();	
		glLoadIdentity();	
		glOrtho(0, this->screenWidth, this->screenHeight, 0, 0, 1);	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}

	//NOT IN USE ANYMORE
	void Button::EndDrawButtons()
	{
		glMatrixMode(GL_PROJECTION);	
		glPopMatrix();	
		glMatrixMode(GL_MODELVIEW);	
		glPopMatrix();
	}

	/*void Button::DrawClicked(GLuint textureID)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_QUADS);														//Drawing the cursor								
			glTexCoord2f(1.0f, 0.0f); glVertex2i(this->rangeX,		this->positionY);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(this->positionX,	this->positionY);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(this->positionX,	this->rangeY);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(this->rangeX,		this->rangeY);
		glEnd();
	}*/
}
