#include "../Header/main.h"

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") //Disable CMD-wind
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



#include "math.h"
#define SQR(x) (x*x)
cgl::Vector3f CrossProduct(cgl::Vector3f * u, cgl::Vector3f * v)
{
	cgl::Vector3f resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;
	return resVector;
}

float GetCGLVectorLength( cgl::Vector3f * v)
{
	return (GLfloat)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

cgl::Vector3f Normalize3dVector( cgl::Vector3f v)
{
	cgl::Vector3f res;
	float l = GetCGLVectorLength(&v);
	if (l == 0.0f) return cgl::Vector3f(0,0,0);
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}



/*class Bullet
{
public:
	float PIdiv180;
	cgl::Vector3f viewdirection;
	cgl::Vector3f position;
	float xrot, yrot, zrot;
	int lifespan;
	float angle;
	float speed;
	Bullet::Bullet(float x, float z, float a)
	{
		this->PIdiv180 = 3.141592654/180;
		speed = 0.25;
		angle = a;
		lifespan = 200;
	}

	void BulletDraw()
	{
		Forward();
		glColor3f(1.0, 0.0,0.0);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(0.4,0.4, 0.4);
		float bulletMaterial[] = { 0.2, 0.6, 0.30, 1};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bulletMaterial);
		glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
		glColor3f(0.8,0.8,0.8);
		lifespan -= 1;
	}

	void Bullet::Forward()
	{
		this->position.x = this->position.x + (viewdirection.x * speed);
		this->position.y = this->position.y + (viewdirection.y * speed);
		this->position.z = this->position.z + (viewdirection.z * speed);
	}

	void Bullet::Fire(cgl::Vector3f startposition, cgl::Vector3f view)
	{
		this->viewdirection.x = view.x;
		this->viewdirection.y = view.y;
		this->viewdirection.z = view.z;
		this->position.x = startposition.x;
		this->position.y = startposition.y;
		this->position.z = startposition.z;
		CoutVec(this->position, "pos");
		CoutVec(this->viewdirection, "view");
		lifespan = 200;
	}
};*/

/*
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
		this->speed = 0.5;
		this->missileArc = 0.25;
	}

	void Projectile::Fire(cgl::Vector3f startPosition, cgl::Vector3f viewdirection, cgl::Model* model, int damage, int playerID)
	{
		this->position.x = startPosition.x;
		this->position.y = startPosition.y;
		this->position.z = startPosition.z;
		this->viewdirection = viewdirection;
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
		std::cout << " pos xy " << position.x << " , " << position.y << ", " << position.z << std::endl;
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
		if(this->lifespan > 0)
		{
			this->Move();
			this->lifespan --;
			//this->Move();					//Moving the projectile further

			glPushMatrix();
			glScalef(0.05, 0.05, 0.05);
			glRotatef(-yaw,1.0,0.0,0.0);	//rotate the camera (more precisly move everything in the opposit direction)
			glRotatef(-pitch,0.0,1.0,0.0);

			glTranslatef(this->position.x, this->position.y, this->position.z);
			this->model->Draw();
			glPopMatrix();


		}
	}

};*/

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


/*class CamTest
{
	//Youtube video tutorial camera, movement, mouse, nice
private: 
	float temp;
public:
	float x,y,z;
	float camYaw;
	float camPitch;
	float PIdiv180;
	cgl::Mouse* mousept;
	CamTest::CamTest(cgl::Mouse* m)
	{
		this->temp = 0.0;
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

	cgl::Vector3f CamTest::GetViewDirection()
	{
		cgl::Vector3f step1, step2;
		//Rotate Y-axis
		step1.x = cos((this->camYaw + 90.0) * PIdiv180);
		step1.z = -sin((this->camYaw + 90.0) * PIdiv180);
		//Rotate X-axis
		this->temp = cos(this->camPitch * PIdiv180);
		std::cout << " TEmp : " << temp;
		step2.x = step1.x * this->temp;
		step2.z = step1.z * this->temp;
		step2.y = sin(this->camPitch * PIdiv180);
		std::cout << " STEP XYZ " << step2.x << step2.y << step2.y << std::endl;
		return step2;
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
	
			camYaw += mousevelocity * (midx-tmpx);
			camPitch += mousevelocity * (midy-tmpy);
			LockCamera();
			this->mousept->SetCursorPosition(midx, midy);	//Reset to middle
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
};*/


int main(int argc, char *argv[])
{
	cgl::CGLInitialize();	//Library Initialize
	initGL();
	InitializeLighting();
	Initialize();			//Initialize game objects


	//////UNCOMMENT THE FIRST /* */ TO TEST THE SHOOTING AND CAMERA MOVING WITHOUT NETWORK
	//////----------------------------
	/*cgl::Image2D* uu = new cgl::Image2D();
	uu->LoadBMP("Data/banana.bmp");
	cgl::Model* mod = new cgl::Model("Data/banana.md2", uu->ID, 0.0025, MD2Normals);
	//cgl::Model* mod = new cgl::Model("Data/Banana.3ds");
	delete uu;
	mouse->enableMouseFrame = true;
	mouse->ShowWindowsCursor(true);
	bool b = true;
	bool shooting = false;
	bool mousein = false;
	cgl::SimpleCamera* cam = new cgl::SimpleCamera(keyboard, mouse, 800, 600);//Our camera, either FREE VIEW; FPS OR THIRD PERSON
	cam->Initialize(0.3,0.3);
	cgl::ProjectileBullet* bullet = new cgl::ProjectileBullet();
	bullet->size = 0.005f;
	bullet->speed = 5.0f;
	bullet->SetModel(mod);

	while(b)
	{
		if(keyboard->isKeyPressed("P") == true)
		{
			if(mousein)
			{
				mousein = false;
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
		cam->Update(mousein);	//Update, Place? View? ...Function name shall we use? Render? Draw()? Action()? 
		terrain->Draw(0.0);
		
		if(keyboard->isKeyPressed("Y") == true)
		{
			cam->MoveForward(1.0);
		}
				
		if(keyboard->isKeyPressed("U") == true)
		{
			cam->MoveBackwards(1.0);
		}

		if(keyboard->isKeyPressed("K") == true)
		{
			cam->MoveStrafeRight(1.0);
		}

				
		if(keyboard->isKeyPressed("J") == true)
		{
			cam->MoveStrafeLeft(1.0);
		}

		if(keyboard->isKeyPressed("SPACE") == true)
		{
			shooting = true;
			bullet->Shoot(cam->position, cam->GetViewDirection(), 1000);
		}

		if(shooting == true)
		{
			glColor3f(0.0, 1.0,0.0);
			bullet->Draw();
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

		if(keyboard->isKeyPressed("Q") == true)
		{
			b = false;
		}

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
		cgl::Sleep(55);
	}
	*/


	InitializeLighting();
	GameLoop();				//Starts the program/Server/game loop
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