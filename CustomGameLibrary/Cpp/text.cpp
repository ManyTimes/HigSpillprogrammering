#include "../Header/text.h"

namespace cgl
{
	Text::Text()
	{
	}

	Text::Text(int screenWidth, int screenHeight)
	{
		this->screenWidth = screenWidth; 
		this->screenHeight = screenHeight;
		this->font = GLUT_BITMAP_HELVETICA_18;
		RGB[0] = 0.9f;
		RGB[1] = 0.9f;
		RGB[2] = 0.9f;
		x = 0;
		y = 0;
	}

	void Text::Initialize(int screenWidth, int screenHeight)
	{
		this->screenWidth = screenWidth; 
		this->screenHeight = screenHeight;
		this->font = GLUT_BITMAP_HELVETICA_18;
		RGB[0] = 0.9f;
		RGB[1] = 0.9f;
		RGB[2] = 0.9f;
		x = 0;
		y = 0;
	}

	//Sizes allowed: 10, 12, 18, 24
	void Text::SetFontSize(int size)
	{
		if(size < 12)
		{
			this->font = GLUT_BITMAP_HELVETICA_10;
		}
		else
		{
			if(size < 16)
			{
				this->font = GLUT_BITMAP_HELVETICA_12;
			}
			else
			{
				if(size > 20)
				{
					this->font = GLUT_BITMAP_TIMES_ROMAN_24;
				}
				else
				{
					this->font = GLUT_BITMAP_HELVETICA_18;
				}
			}
		}
	}


	void Text::Draw(char* text, int textX, int textY)
	{
		this->x = textX;
		this->y = textY;
		this->Draw(text);
	}

	void Text::Draw(char* text)
	{
		glPushMatrix();
		glColor3f(this->RGB[0], this->RGB[1], this->RGB[2]);
		glRasterPos2f((float)this->x/this->screenWidth,(float)this->y/this->screenHeight);
		int length = cgl::GetArrayLength(text);
		for(int i = 0; i < length; i++)
		{
			glutBitmapCharacter(font, text[i]);
		}
		glPopMatrix();
	}

	// OLD DRAWING OBJECT
	/*Text::Text(OpenGL* openglObject)
	{
		this->opengl = openglObject;
		this->screenWidth = this->opengl->width; 
		this->screenHeight = this->opengl->height;
		this->font = GLUT_BITMAP_HELVETICA_12;
		RGB[0] = 1.0f;
		RGB[1] = 1.0f;
		RGB[2] = 1.0f;
		x = 0;
		y = 0;
	}

	void Text::Draw(char* text, int textX, int textY)
	{
		this->x = ((float)textX/this->opengl->currentViewportWidth);
		this->y =  ((float)textY/this->opengl->currentViewportHeight);
		this->Draw(text);
	}

	void Text::Draw(char* text)
	{
		glColor3f(this->RGB[0], this->RGB[1], this->RGB[2]);
		glRasterPos2f(this->x,this->y);
		std::cout << "Raster pos: " << this->x << "," << this->y << std::endl;
		int length = cgl::GetArrayLength(text);
		for(int i = 0; i < length; i++)
		{
			glutBitmapCharacter(font, text[i]);
		}
	}
	/*
	void Text::DisplayText(char* text)
	{
		std::cout << "displaytext" << std::endl;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(this->RGB[0], this->RGB[1], this->RGB[2]);
		glRasterPos2f(-20, 10.0);
		int length = cgl::GetArrayLength(text);
		for(int i = 0; i < length; i++)
		{
			glutBitmapCharacter(font, text[i]);
		}
		std::cout << "displaytext" << std::endl;
	}

	void Text::StartDraw()
	{
		std::cout << " START DRAWING TEXT IDIOT" << std::endl;
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();	
		glLoadIdentity();
		gluPerspective(45.0, (float)this->screenWidth / (float)this->screenHeight, 1.0, 200.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();	
		glLoadIdentity();
	}

	void Text::EndDraw()
	{
		glMatrixMode(GL_PROJECTION);	
		glPopMatrix();	
		glMatrixMode(GL_MODELVIEW);	
		glPopMatrix();
	}*/
}