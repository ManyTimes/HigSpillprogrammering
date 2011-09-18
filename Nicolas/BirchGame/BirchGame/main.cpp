#define WIN32_LEAN_AND_MEAN
#include "GL/glew.h"
#include <iostream>
#include "camera.h"
#include "glfw_callbacks.h"
#include "shader.h"
#include "common.h"
#include "m_3ds.h"
#include "player.h"
/*

#include "md3.h"
#include "camera.h"
*/

// Declerations =======================
void initOpenGL();
void MovementHandle();
void Fps();
void TestRenderScene();

// Global variables ===================
bool Running;							// Game running true/false
unsigned int frame;
float w = 800.0f, h = 600.0f;			// width and height of the screen.
Point3 SpawnPoint(500,500,500);			// Where camera spawns
Point3 LookAt(0,0,0);					// Where camera points at
Point3 Up(0,1,0);						// Cameras up direction.
float FPS = 60.0f;						// Game current FPS
#define MOVEMENT_SPEED 100.0f			// Camera movement speed.

// Objects ============================
// Cameras
Camera camera;

// Shaders
//Shader *mainShader;

// Programs
//Program mainProgram;

//M_3DS model;
//M_3DS model2;
//M_3DS model3;
Player player;

int main()
{
	glfwInit();
	GLenum initReturn;

//	glfwOpenWindowHint(GLFW_FSAA_SAMPLES,8);
	glfwOpenWindow((int)w,(int)h,0,0,0,0,24,0,GLFW_WINDOW);//GLFW_FULLSCREEN);
	glfwSetWindowPos(0,0);
	glfwSetWindowTitle("BirchGame");	// Placeholder name.
	//glfwSetWindowPos();

	//Callbacks
	glfwSetWindowSizeCallback(Size);
	glfwSetWindowCloseCallback(CloseWindow);
	glfwSetKeyCallback(Keyboard);
	glfwSetCharCallback(Text);
	glfwSetMouseButtonCallback(MouseButton);
	glfwSetMousePosCallback(MousePosition);

	glfwSwapInterval(0); // VSync off.

	if((initReturn = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(initReturn);
		return 1;
	}

	// Initialize openGL
	initOpenGL();

	// Remove mouse cursor.
	glfwDisable( GLFW_MOUSE_CURSOR );

	// Load assets
	//M_3DS model("TestModel.3ds");
	/*model.Load("TestModel.3ds");
	model2.Load("TestModel2.3ds");
	model3.Load("TestModel3.3ds");*/
	player.SetModel("TestModel3.3ds");

	// Game loop
	Running = true;
	while(Running)
	{
		frame++;
		MovementHandle();
		Fps();
		TestRenderScene();
	}


	return 0;
}

/*
	Sets up the initial scene.
*/
void initOpenGL()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	camera.setShape(50.0f,w/h,0.1f,4000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.set( SpawnPoint, LookAt, Up);

	glEnable(GL_DEPTH_TEST);	// Gives depth testing
	glEnable(GL_CULL_FACE);		// Don't draw the backside
	glEnable(GL_LIGHTING);		// Enables fixed pipeline lighting
	glEnable(GL_LIGHT0);		// Enables light0
//	glEnable(GL_TEXTURE_2D);	// Enables use of 2D textures
	glEnable(GL_NORMALIZE);		// Normals automaticially normalized

	//glEnable(GL_LINE_SMOOTH);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;

	glFrontFace(GL_CW);			// Winding of elements

	//glShadeModel(GL_SMOOTH);
}


char szTitle[256]={0};
double oldTime = 0;
double markTime = 0;
double currentTime = 0;
void Fps()
{
	currentTime = glfwGetTime();
	if(currentTime - markTime >= 1.0f)
	{
		markTime = currentTime;
		sprintf( szTitle, "BirchGame, FPS: %f FrameTime: %f", FPS, (currentTime - oldTime));
		glfwSetWindowTitle(szTitle);
	}

	FPS = 1.0f/(float)(currentTime - oldTime);
	oldTime = currentTime;
}

void MovementHandle()
{
	if(keys[KEY_FORWARD])
		camera.slide(0,0,-MOVEMENT_SPEED/FPS, 1);
	if(keys[KEY_BACK])
		camera.slide(0,0,MOVEMENT_SPEED/FPS, 1);
	if(keys[KEY_LEFT])
		camera.slide(-MOVEMENT_SPEED/FPS,0,0, 1);
	if(keys[KEY_RIGHT])
		camera.slide(MOVEMENT_SPEED/FPS,0,0, 1);
	if(keys[KEY_UP])
		camera.slide(0,MOVEMENT_SPEED/FPS,0, 0);
	if(keys[KEY_DOWN])
		camera.slide(0,-MOVEMENT_SPEED/FPS,0, 0);
}

void TestRenderPlane();
void TestRenderPlayer();

void TestRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static float angle = 0;

	float light[] = {45, 45, 45, 0};
	float ambience[] = { 0.9f, 0.5f, 0.5f };
	float lightCol[] = {0.5, 1.0, .5, .5}; // white light

	glLightfv(GL_LIGHT0, GL_POSITION, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightCol);
	glLightfv(GL_LIGHT0,GL_AMBIENT, ambience);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);


	TestRenderPlane();
	TestRenderPlayer();


	angle += (100/FPS);
	
	glPushMatrix();
		glRotatef(angle,0,1,0);
//		glRotatef((frame/FPS)/10.0f,0,1,0);
//		std::cout << frame*(1/FPS)/10.0f << std::endl;
		glScalef(5,5,5);
		glScalef(1,1,1);
		player.Draw();
		//model.Draw();
		//model2.Draw();
		//model3.Draw();
	glPopMatrix();
	glfwSwapBuffers();
}

void TestRenderPlane()
{
	glColor3f(0,1,0);

	glBegin(GL_QUADS);
		glNormal3f(0,1,0);
//		glTexCoord2f(0.0, 0.0);
		glVertex3f(0,0,0);
//		glTexCoord2f(1.0/SAMPLE, 0.0);
		glVertex3f(w,0,0);
//		glTexCoord2f(1.0/SAMPLE, 1.0/SAMPLE);
		glVertex3f(w,0,h);
//		glTexCoord2f(0.0,1.0/SAMPLE);
		glVertex3f(0,0,h);
	glEnd();
}

void setMatrix(Vector3 *Look, Vector3 *Right, Vector3 *Up, Vector3 *Pos, float m[16]);
void TransposeRotation(float matrix[16]);
void MatrixMultiply(float matrix[16], float v[4]);
void TestRenderPlayer()
{
	Vector3 Pos(5,5,5);
		float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
//	Vector3 Eye(modelview[12],modelview[13],modelview[14]);
	Vector3 v = camera.getV();
//	Vector3 v2(modelview[1], modelview[5], modelview[9]);

//	float _eye[4] = { Eye.x, Eye.y, Eye.z, 0};
//	modelview[12] = modelview[13] = modelview[14] = 0;
//	TransposeRotation(modelview);
//	MatrixMultiply(modelview, _eye);
//	Eye.x = _eye[0];
//	Eye.y = _eye[1];
//	Eye.z = _eye[2];
	Vector3 Eye = camera.getEye()*-1;

	//Vector3 look3 = camera.getEye();

	//Vector3 Look = (camera.getEye() - Point3(Pos.x, Pos.y, Pos.z));
	Vector3 Look = (Eye - Pos);
	Look.normalize();
	Vector3 Right = v.cross(Look);//Look.cross(v2);//
//	Right.normalize();
	Vector3 Up = Look.cross(Right);
//	Up.normalize();
	float m[16];

	int i,j;


	// undo all rotations
	// beware all scaling is lost as well 
	for( i=0; i<3; i++ ) 
	    for( j=0; j<3; j++ ) {
		if ( i==j )
		    modelview[i*4+j] = 1.0;
		else
		    modelview[i*4+j] = 0.0;
	    }

	// set the modelview with no rotations

	//Right.x = 1;
	//Right.y = 0;
	//Right.z = 0;
	setMatrix(&Look, &Right, &Up, &Pos, m);
	glPushMatrix();
	{
		//glMatrixMode(GL_MODELVIEW);
		//glLoadMatrixf(m);//Load OpenGLs modelview-matrise	
		glMultMatrixf(m);
		//glLoadMatrixf(modelview);
		glColor3f(0,0,1);
/*		glBegin(GL_QUADS);
	//		glTexCoord2f(0.0, 0.0);
			glVertex3f(0,1,0);
	//		glTexCoord2f(1.0/SAMPLE, 0.0);
			glVertex3f(20,1,0);
	//		glTexCoord2f(1.0/SAMPLE, 1.0/SAMPLE);
			glVertex3f(20,1,20);
	//		glTexCoord2f(0.0,1.0/SAMPLE);
			glVertex3f(0,1,20);
		glEnd();//*/
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(10, -12, 0);
		glVertex3f(10, 12, 0);
		glVertex3f(-10, 12, 0);
		glVertex3f(-10, -12, 0);
		glEnd();//*/
	}glPopMatrix();
}

void setMatrix(Vector3 *Look, Vector3 *Right, Vector3 *Up, Vector3 *Pos, float m[16])
{
	m[0] = Right->x; 
	m[1] = Right->y;
	m[2] = Right->z;
	m[12] = -Pos->dot(*Right);
	m[4] = Up->x;
	m[5] = Up->y;
	m[6] = Up->z;
	m[13] = -Pos->dot(*Up);
	m[8] = Look->x; 
	m[9] = Look->y;
	m[10] = Look->z;
	m[14] = -Pos->dot(*Look);
	m[3] = 0;//Pos->x; 
	m[7] = 0;//Pos->y;
	m[11] = 0;//Pos->z;
	m[15] = 1.0;
}

void TransposeRotation(float matrix[16])
{
	float	temp[16];
	// copy this into temp
	memcpy(temp, matrix, sizeof(float) * 16);
	matrix[1] = temp[4];	matrix[4] = temp[1];
	matrix[2] = temp[8];	matrix[8] = temp[2];
//	matrix[3] = temp[12];	matrix[12] = temp[3];
	matrix[6] = temp[9];	matrix[9] = temp[6];
//	matrix[7] = temp[13];	matrix[13] = temp[7];
//	matrix[11] = temp[14];	matrix[14] = temp[11];
}

void MatrixMultiply(float matrix[16], float v[4])
{
	float	r[4];
	r[0] = matrix[0] * v[0] + matrix[4] * v[1] + matrix[8] * v[2] + matrix[12] * v[3];
	r[1] = matrix[1] * v[0] + matrix[5] * v[1] + matrix[9] * v[2] + matrix[13] * v[3];
	r[2] = matrix[2] * v[0] + matrix[6] * v[1] + matrix[10] * v[2] + matrix[14] * v[3];
	r[3] = matrix[3] * v[0] + matrix[7] * v[1] + matrix[11] * v[2] + matrix[15] * v[3];
	memcpy(v, r, sizeof(float) * 4);
}