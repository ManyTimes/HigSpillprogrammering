#include "../Header/main.h"
#include "../Header/include.h"
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //Disable CMD-window

int x = 800;
int y = 600;
int w = 800;
int h = 600;
static GLfloat LightPos[] = {10.0,2.0,20.0,0.0};
static GLfloat MatSpec[] = {1.0,1.0,1.0,1.0};
static GLfloat MatShininess[] = {70.0};

void Display();
void DrawFloor(GLuint textID);
void initGL();
void Reshape();
void InitializeLighting();
void Drawgr();
cgl::Image2D* img;
cgl::Image2D* unitText;
cgl::ModelMD2* model2;
cgl::Projectile** pro;

class Projectile 
{
private:
	float yaw;
	float pitch;
	cgl::Vector3f move;
public:
	float PIdiv180;
	int playerID;					//Owner of projectile, getting "the kill"
	int damage;						//Damage of projectile upon hit
	cgl::Vector3f position;			//It should also prolly have a boundingbox, for collision detection (grid, knut!)
	cgl::Vector3f viewdirection;
	cgl::Model* model;
	float speed;
	float missileArc;
	int lifespan;					//Number of frames ("Draw()")
	Projectile::Projectile(int lifespan)
	{
		this->PIdiv180 = 3.14159265 / 180.0;
		this->lifespan = lifespan;
		this->speed = 0.6;
		this->missileArc = 0.25;
	}

	void Projectile::Fire(cgl::Vector3f startPosition, cgl::Vector3f viewdirection, cgl::Model* model, int damage, int playerID)
	{
		this->speed = 0.6;
		this->position.x = startPosition.x;
		this->position.y = startPosition.y;
		this->position.z = startPosition.z;
		//this->viewdirection = viewdirection;
		this->viewdirection.x = viewdirection.x;
		this->viewdirection.y = viewdirection.y;
		this->viewdirection.z = viewdirection.z;
		this->model = model;
		this->playerID = playerID;
		this->damage = damage;
		this->lifespan = 250;
		std::cout << " FORE xy " << this->position.x << " , " << this->position.y << ", " << this->position.z << std::endl;
		std::cout << " View xy " << this->viewdirection.x << " , " << this->viewdirection.y << ", " << this->viewdirection.z << std::endl;
	}

	void Projectile::Move()
	{
		this->move.x = this->viewdirection.x * -this->speed;
		this->move.y = this->viewdirection.y * -this->speed;
		this->move.z = this->viewdirection.z * -this->speed;
		this->position.x += this->move.x;
		this->position.y += this->move.y;
		this->position.z += this->move.z;
		//MoveCamera();
		//MoveCameraUp();
	}

	//Angle is in celsius, need radians
	void Projectile::MoveCamera()
	{
		float radian=yaw * PIdiv180;//Forward
		position.x-=sin(radian)*this->speed;	//calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
		position.z-=cos(radian)*this->speed;	//and try to calculate the new coorinate with trigonometric functions, that should help
	}

	void Projectile::MoveCameraUp()
	{
		//the the same, only this time we calculate the y coorinate
		float radian = pitch * PIdiv180;
		position.y+=sin(radian) * this->speed;
	}


	void Projectile::Draw()
	{
		/*if(this->lifespan > 0)
		{
			this->Move();
			this->lifespan --;
			glColor3f(1.0, 1.0, 0.5);
			glPushMatrix();
			glScalef(1.5,1.5, 1.5);
			glTranslatef(this->position.x, this->position.y, this->position.z);
			glRotatef(-yaw,1.0,0.0,0.0);	//rotate the camera (more precisly move everything in the opposit direction)
			glRotatef(-pitch,0.0,1.0,0.0);
			this->model->Draw();
			glPopMatrix();

		}*/
		this->Move();
		glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		glScalef(0.4,0.4, 0.4);
		float bulletMaterial[] = { 0.2, 0.6, 0.30, 1};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bulletMaterial);
		glutSolidSphere(0.5, 20, 20);
		this->position.Cout();
		glPopMatrix();
	}

};

cgl::SimpleCamera* cam = new cgl::SimpleCamera();
int angle = 50;

void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++)
	{
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}
	for (int zc = 0; zc < LinesX; zc++)
	{
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}
	glEnd();
}

class CamTest
{
	//Youtube video tutorial camera, movement, mouse, nice
public:
	float x,y,z;
	float camYaw;
	float camPitch;
	float PIdiv180;
	cgl::Mouse* mousept;
	CamTest::CamTest(cgl::Mouse* m)
	{
		this->mousept = m;
		PIdiv180 =  3.1415926535/180;
		x = y = z = 0.0;
		z = 5.0;
		camYaw = 0.0;
		camPitch = 0.0;
	}
	void CamTest::LockCamera()
	{
		//set campitch between -90 and 90 and set camyaw between 0 and 360 degrees
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;

	}

	//Angle is in celsius, need radians
	void CamTest::MoveCamera(float distance, float direction)
	{
		float radian=(camYaw+direction)*PIdiv180;	//convert the degrees into radians
		x-=sin(radian)*distance;	//calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
		z-=cos(radian)*distance;	//and try to calculate the new coorinate with trigonometric functions, that should help

	}

	void CamTest::MoveCameraUp(float distance, float direction)
	{
		//the the same, only this time we calculate the y coorinate
		float radian=(camPitch+direction)*PIdiv180;
		y+=sin(radian)*distance;

	}

	void CamTest::Control(float movevel, float mousevelocity, bool mouseIn)
	{
		if(mouseIn)
		{
			int midx = 400;	//Half of screen sizes
			int midy = 300;
			int tmpx, tmpy;
			tmpx = this->mousept->cursorx;
			tmpy = this->mousept->GetCursorPositionY();
	
			if(midx-tmpx > 2 || midx-tmpx < -1)
			{
				camYaw += mousevelocity * (midx-tmpx);
			}

			if(midy-tmpy > 2 || midy-tmpy < -1)
			{
				camPitch += mousevelocity * (midy-tmpy);
			}

			LockCamera();
			this->mousept->SetCursorPosition(midx, midy);	//Reset to middle
		//	std::cout << " X , Y " << this->mousept->cursorx << " , " << this->mousept->cursory << std::endl;
			if(keyboard->isKeyPressed("W") == true)
			{
				if(camPitch != 90 && camPitch != -90)
				{
					MoveCamera(movevel, 0.0);
				}
				MoveCameraUp(movevel, 0.0);
			}
			else
			{
				if(keyboard->isKeyPressed("S") == true)
				{
					if(camPitch != 90 && camPitch != -90)
					{
						MoveCamera(movevel,180.0);
					}
					MoveCameraUp(movevel,180.0);
				}
			}
			if(keyboard->isKeyPressed("A") == true)
			{
				MoveCamera(movevel,90);
			}
			else
			{
				if(keyboard->isKeyPressed("D") == true)
				{
					MoveCamera(movevel,270);
				}
			}
		}
		glRotatef(-camPitch,1.0,0.0,0.0);	//rotate the camera (more precisly move everything in the opposit direction)
		glRotatef(-camYaw,0.0,1.0,0.0);
	}

	void CamTest::UpdateCamera()
	{
		glTranslatef(-x, -y, -z);
	}

	//Outside the class
	//p (pause) toggles on off the mouseIn (mouse in, if app is in focus)
/*	void Display()
	{
		Control(0.2, 0.2, mousein);
		UpdateCamera();
	}*/
};

void UpdateMouse();
cgl::Vector3f SpawnPoint(-0,5,-5);			// Where camera spawns
cgl::Vector3f LookAt(5,0,5);					// Where camera points at
cgl::Vector3f Up(0,1,0);						// Cameras up direction.
cgl::Camera *tp_camera;

int main(int argc, char *argv[])
{
	cgl::CGLInitialize();	//Library Initialize
	initGL();
	InitializeLighting();
	Initialize();			//Initialize game objects
	cam->Initialize(keyboard, mouse, 800, 600);
	cam->Initialize(0.4, 0.4);
	cam->MoveForward( -1.0);

	cam->AllowMovement = true;
//	x1 = x2 = y1 = y2 = 0.0;
//	x1 = mouse->cursorx;
//	y1 = mouse->cursory;

	cgl::Image2D* uu = new cgl::Image2D();
	uu->LoadBMP("Data/snake.bmp");
	cgl::Model* mod = new cgl::Model("Data/banana.md2", uu->ID, 0.0025, MD2Normals);
	mod->EnableNormals(true);
	delete uu;
	mouse->enableMouseFrame = true;
	//mouse->EnableMouseFrame(true);
	mouse->ShowWindowsCursor(false);
	CamTest* ct = new CamTest(mouse);
	Projectile* pp = new Projectile(10000);	//10.k frames

	cgl::ProjectileBullet* tempb = new cgl::ProjectileBullet();
	tempb->SetModel(mod);
	tempb->SetScale(1,1,1);
	cgl::Vector3f ballpos(1,1,1);

	bool b = true;
	bool mousein = false;
	float pitch, yaw;
	pitch = yaw = 0.0;
	bool shooting = false;
	while(b)
	{
		if(keyboard->isKeyPressed("P") == true)
		{
			if(mousein)
			{
				//mousein = false;
				mouse->ShowWindowsCursor(true);
			}
			else
			{
				mousein = true;
				mouse->ShowWindowsCursor(false);
			}
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		opengl->StartDraw();
		opengl->CreateViewport(true, 800,600,0,100,0.001f, 1000.0f);
		cam->Update(mousein);
		terrain->Draw(0.0);


		if(keyboard->isKeyPressed("SPACE") == true)
		{
			if(shooting == false)
			{
				shooting = true;
			}
			tempb->Shoot(cam->position, cam->GetViewDirection(), 1000);

		}


		if(shooting == true)
		{
			tempb->Draw();
		}

		GLfloat size = 2.0;
		GLint LinesX = 30;
		GLint LinesZ = 30;

		GLfloat halfsize = size / 2.0;
		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
			glTranslatef(0.0,-halfsize ,0.0);
			DrawNet(size,LinesX,LinesZ);
			glTranslatef(0.0,size,0.0);
			DrawNet(size,LinesX,LinesZ);
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
		glPushMatrix();
			glTranslatef(-halfsize,0.0,0.0);	
			glRotatef(90.0,0.0,0.0,halfsize);
			DrawNet(size,LinesX,LinesZ);
			glTranslatef(0.0,-size,0.0);
			DrawNet(size,LinesX,LinesZ);
		glPopMatrix();
		glColor3f(1.0,0.0,0.0);
		glPushMatrix();
			glTranslatef(0.0,0.0,-halfsize);	
			glRotatef(90.0,halfsize,0.0,0.0);
			DrawNet(size,LinesX,LinesZ);
			glTranslatef(0.0,size,0.0);
			DrawNet(size,LinesX,LinesZ);
		glPopMatrix();


		if(keyboard->isKeyPressed("W") == true)
		{
			cam->MoveForward(-0.1);
		}
		if(keyboard->isKeyPressed("S") == true)
		{
			cam->MoveForward(0.1);
		}

	//	x1 = mouse->cursorx;
	//	y1 = mouse->cursory;

	//	x1 = (100 * (mouse->cursorx - (400)) / 400);

		/*if(x1-x2 > 3)
		{
			cam->RotateY(1.0);
		}
		else
		{
			if(x1-x2 < -3)
			{
				cam->RotateY(-1.0);
			}
		}*/
		//std::cout << "X: " << x1 << " - x2 " << x2  << " = " << (x1-x2) <<std::endl;
		/*if(mouse->cursorx < 390)		//Half of x - 10
		{
			cam->RotateY(0.4);
			std::cout << "X: " << mouse->cursorx << " < 390 " << std::endl;
			//mouse->cursorx = 400;
		}
		else
		{
			if(mouse->cursorx > 410)
			{
				std::cout << "X: " << mouse->cursorx << " > 410 " << std::endl;
				cam->RotateY(-0.4);
			}
		}*/

		if(keyboard->isKeyPressed("Q") == true)
		{
			b = false;
		}

		//mouse->SetCursorPosition(400, 300);
		/*if(keyboard->isKeyPressed("A") == true)
		{
			cam->RotateY(1);
		}
		if(keyboard->isKeyPressed("D") == true)
		{
			cam->RotateY(-1);
		}*/


		//glTranslatef(0.0, 0.0, -30.0);
		//cam->x = -30.0f;
		//cam->



		float velocity[3];
		velocity[0] = velocity[2] = cgl::GetRandomFloat(-0.05, 0.07);
		velocity[1] = cgl::GetRandomFloat(-.015, -0.03);
		float position[3];
		position[0] = cgl::GetRandomFloat(-5.0, 5.0);
		position[2] = cgl::GetRandomFloat(-5.0, 5.0);
		position[1] = 10;
		weather->StartOneParticle(velocity, position);
		weather->Draw();
		opengl->EndDraw();
		cgl::Sleep(150);
	}
	//InitializeLighting();
	//GameLoop();				//Starts the program/Server/game loop
	return 0;
}


void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_NORMALIZE);
	glEnable(GL_FOG);
	glShadeModel(GL_SMOOTH);	//OR GL_FLAT
	glClearColor(0.8f, 0.8f, 0.8f, 1);
	//FOG EFFEC
	glFogf(GL_FOG_DENSITY, 0.04f);		//GL_EXP, GL_EXP2
}

void InitializeLighting()
{
	//Add ambient light
    GLfloat ambientColor[] = {0.66f, 0.67f, 0.68f, 1.0f}; //Color(0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		//Add positioned light
    GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 0.9f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {1.0, 10.0f, 1., 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add positioned light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.7f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos1[] = {1., 25.0f, 1., 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	//Add positioned light
    GLfloat lightColor2[] = {0.1f, 0.2f, 0.7f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos2[] = {1., 20.0f, 1., 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	
	//Add positioned light
    GLfloat lightColor3[] = {0.5f, 0.9f, 0.1f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos3[] = {1, 5.0f, 1., 1.0f};			//Positioned light
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
}

void UpdateMouse()		// Function to control mouse [TP_CAMERA]
{
	static bool first = true;							// First time mouse enters screen.
	static int old_x = 0, old_y = 0;
	int pos_x, pos_y;
	int x = mouse->GetCursorPositionX();
	int y = mouse->GetCursorPositionY();

	glfwGetWindowSize( &pos_x, &pos_y);
	pos_x /= 2;
	pos_y /= 2;

	if(first)											// First time, center the mouse.
	{
		mouse->SetCursorPosition(pos_x,pos_y);
		old_x = pos_x;
		old_y = pos_y;
		first = false;
		return;
	}

	if((x-old_x) != 0)
		tp_camera->ThirdPersonRotateYaw((old_x-x)/15.0f);
		
	if((y-old_y) != 0)
			tp_camera->ThirdPersonRotatePitch((old_y-y)/15.0f);

	if(x != old_x || y != old_y)
	{
		mouse->SetCursorPosition(pos_x,pos_y);
        x = old_x=pos_x;
        y = old_y=pos_y;
	}

	old_x = x;
	old_y = y;
}