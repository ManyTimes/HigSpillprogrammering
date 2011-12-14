#include "../Header/main.h"
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
int main(int argc, char *argv[])
{
	cgl::CGLInitialize();	//Library Initialize
	Initialize();			//Initialize game objects
	//InitializeLighting();
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