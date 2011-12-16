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
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//camera.set( SpawnPoint, LookAt, Up);
	glEnable(GL_LINE_SMOOTH);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;
	glFrontFace(GL_CW);			// Winding of elements

	glClearColor(0,0,0,1);
	opengl->StartDraw();
	opengl->CreateViewport(true, 800,500,0,100,0.0f, 500.0f);
	if(thisPlayer > -1)
	{
		simpleCamera[thisPlayer].Update(DISABLEMOUSECONTROL);
	}
	
	//terrain->Draw(0.0);
	DrawGround(imgbtnStart->ID);
	float velocity[3];
	velocity[0] = velocity[2] = cgl::GetRandomFloat(-0.1, 0.1);
	velocity[1] = cgl::GetRandomFloat(-.015, -0.03);
	float position[3];
	position[0] = cgl::GetRandomFloat(10.0, 50.0);
	position[2] = cgl::GetRandomFloat(10.0, 50.0);
	position[1] = 10;
	weather->StartOneParticle(velocity, position);


	for(int i = 0; i < MAXIMUMPLAYERS; i++)
	{
		if(player[i].ID != -1)
		{
			if(thisPlayer != i)				//Not drawing ourselves [FPS mode]
			{
				unit[i].Draw();
			}
		}
	}
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

	if(gamestate > 1)				//Viewing a menu while playing
	{
		opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 1);			//Drawing buttons requires Viewport 2D, with z far and near not equal each other
		btnCancel->Draw();	
		btnQuitGame->Draw();
	}
	opengl->EndDraw();
}



void DrawGround(GLuint textureID)
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.1f, 0.5f, 0.9f);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int w = SCREENWIDTH;
	int h = SCREENHEIGHT;
	int y = -1.0f
	for(int i = 1; i <= 2; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 0);
		glVertex3f(-w*i, y, -h*i);

		glTexCoord2i(1, 0);
		glVertex3f(w*i, y, -h*i);

		glTexCoord2i(0, 1);
		glVertex3f(-w*i, y, h*i);

		glTexCoord2i(1, 1);
		glVertex3f(w*i, y, h*i);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}