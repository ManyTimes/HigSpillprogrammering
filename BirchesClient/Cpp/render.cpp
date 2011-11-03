#include "../Header/render.h"
void Draw2D(GLuint textureID, int x, int y);
void DrawGround(GLuint textureID);
//Calls a render function based on gamestate
void Render()
{
	if(gamestate == 0)
	{
		RenderMainMenu();
	}	
	else
	{
		RenderGame();
	}
}

void RenderMainMenu()
{
	opengl->StartDraw();
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 0);			//Drawing text requires viewport 2D, with Z far and Z near to be 0//equal each other
	text->SetFontSize(24);
	text->Draw("Welcome to Birches", -800,550);
	text->SetFontSize(16);
	text->Draw("Drink or die!", -800,500);
	if(messageFeedback != "")
	{
		textFeedback->Draw((char*)messageFeedback.c_str(), -SCREENWIDTH,-SCREENHEIGHT+500);
	}
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 1);			//Drawing buttons requires Viewport 2D, with z far and near not equal each other
	imgBackground->Draw(0,0, SCREENWIDTH,SCREENHEIGHT, true);
	btnStart->Draw();	
	btnExit->Draw();
	opengl->EndDraw();
}

void RenderGame()
{

	opengl->StartDraw();
	opengl->CreateViewport(true, 800,500,0,100,0.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 0.0f, -25.0f);				//Sets camera
	glRotatef(30.0f, 1.0, 0.0, 0.0);
	glRotatef(-30.0f, 0.0, 1.0, 0.0);
	DrawGround(imgbtnStart->ID);
	float velocity[3];
	velocity[0] = velocity[2] = cgl::GetRandomFloat(-0.1, 0.1);
	velocity[1] = cgl::GetRandomFloat(-.02, -0.04);
	float position[3];
	position[0] = cgl::GetRandomFloat(-5.0, 5.0);
	position[2] = cgl::GetRandomFloat(-5.0, 5.0);
	position[1] = 15;
	weather->StartOneParticle(velocity, position);
	
	weather->Draw();



	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 0);			//Drawing text requires viewport 2D, with Z far and Z near to be 0//equal each other
	text->SetFontSize(16);
	text->Draw("Kills:", -SCREENWIDTH,SCREENHEIGHT-50);
	text->Draw("Deaths", -SCREENWIDTH,SCREENHEIGHT-100);
	text->Draw("Water", -SCREENWIDTH,SCREENHEIGHT-150);
	text->Draw("Leafs", -SCREENWIDTH,SCREENHEIGHT-200);
	if(messageFeedback != "")
	{																		//Center "error" message, "cannot move there", "cannot attack this object", "Died", "Killed player X"
		textFeedback->Draw((char*)messageFeedback.c_str(), -SCREENWIDTH,SCREENHEIGHT/2);
	}
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 1);			//Drawing buttons requires Viewport 2D, with z far and near not equal each other
	imgMenu->Draw(SCREENWIDTH-50,SCREENHEIGHT-50, 50,50, true);

	//imgMenu->Draw(0,0, 32, 32, true);
	//opengl->CreateViewport3D(600,600,0,0,0.1, 1000);

	
	if(gamestate > 1)				//Viewing a menu while playing
	{
		opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 1);			//Drawing buttons requires Viewport 2D, with z far and near not equal each other
		btnCancel->Draw();	
		btnQuitGame->Draw();
		//Images will not draw, what so ever?
		//imgMenu->Draw(0,0, true);
		//imgMenu->Draw(50,50, true);
		//imgMenu->Draw(0,0, false);
		//imgMenu->Draw(50,50, false);
		
	}
	opengl->EndDraw();

}



void DrawGround(GLuint textureID)
{
	//glEnable(GL_TEXTURE_2D);
	glColor3f(0.1f, 0.5f, 0.9f);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_TRIANGLE_STRIP);
	
		glTexCoord2i(0, 0);
		glVertex3f(-SCREENWIDTH, 0, -SCREENHEIGHT);

		glTexCoord2i(1, 0);
		glVertex3f(SCREENWIDTH, 0, -SCREENHEIGHT);

		glTexCoord2i(0, 1);
		glVertex3f(-SCREENWIDTH, 0, SCREENHEIGHT);

		glTexCoord2i(1, 1);
		glVertex3f(SCREENWIDTH, 0, SCREENHEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}