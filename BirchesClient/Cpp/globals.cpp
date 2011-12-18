#include "../Header/globals.h"

//CONSTANT DATA
const float _180_OVER_PI = 180/PI;
int SCREENWIDTH = 800;
int SCREENHEIGHT = 600;


//GLOBAL VARIABLES
std::string SERVERNAME;				//Received from server upon joining
std::string JOINADDRESS;
std::string JOINPORTNUMBER;
std::string PLAYERNAME;
std::string GAMENAME = "BIRCHES FIGHTING";
int MAXIMUMPLAYERS;
int thisPlayer = -1;				//Clients' player number
int SLEEPTIME = 5;
bool play = true;	
std::string messageFeedback = "";
bool ISCONNECTED = false;
bool DISABLEMOUSECONTROL = false;
bool SERVERRESPONSE = false;		//When we join, we wait for a response from server
									//before a player can play/move/draw/render/send network stuff
//GLOBAL OBJECTS
cgl::Camera* camera;
cgl::SimpleCamera* simpleCamera;
cgl::NetworkClient* client;
cgl::Terrain* terrain;
cgl::Grid* grid;
cgl::OpenGL* opengl;
cgl::Image2D* imgbtnCancel;			//Texture for the btnCancel
cgl::Image2D* imgbtnCancelClicked;	//Texture for the btnCancel
cgl::Image2D* imgbtnExit;			//Texture for the btnExit
cgl::Image2D* imgbtnExitClicked;	//Texture for the btnExit
cgl::Image2D* imgbtnStart;			//Texture for the btnStart
cgl::Image2D* imgbtnStartClicked;	//Texture for the btnStart
cgl::Image2D* imgMenu;				//Image that is displayed top right/left, "Menu (F10)" while playing
cgl::Image2D* imgBackground;		//Background image for our game
cgl::Image2D* imgbtnQuitGame;		//Image 
cgl::Image2D* terrainTile;			//Terrain textrure
cgl::Image2D* imgbtnQuitGameClicked;//Image
cgl::Button* btnStart;				//Joins server and starts drawing game
cgl::Button* btnExit;				//An Exit program button
cgl::Button* btnCancel;				//An Exit program button
cgl::Button* btnQuitGame;
cgl::Time* gametime;
cgl::Keyboard* keyboard;
cgl::Mouse* mouse;
cgl::Unit* unit;						//One unit per player
cgl::Player* player;				//Recgieves xyz, playernames, etc from server when joining
cgl::Text* text;					//Drawing some text, chat? All text drawn through this obj.
cgl::Text* textFeedback;	
cgl::Sound* music;					//Background music...always runs, or "F10" to start stop...
cgl::Sound* soundAttack;				//Sound played when you attack (throw)
cgl::Sound* soundHit;				//Sound played when you are hit
cgl::Weather* weather;
cgl::Image2D* weatherTexture;		
cgl::Projectile* projectilepl1;
//cgl::ModelMD2* modd2;
cgl::Model3D mod3d;
cgl::ProjectileBullet* projectileBanana;
cgl::Model* bananaModel;
//GAME/SERVER DATA
 int gamestate;						//0 = mainmenu, 1 = game, 2 = game + menu drawn above it (cancel/exit)

 
float MD2Normals[486] =
{
	-0.525731f,  0.000000f,  0.850651f,
	 -0.442863f,  0.238856f,  0.864188f,
	 -0.295242f,  0.000000f,  0.955423f,
	 -0.309017f,  0.500000f,  0.809017f,
	 -0.162460f,  0.262866f,  0.951056f,
	  0.000000f,  0.000000f,  1.000000f,
	  0.000000f,  0.850651f,  0.525731f,
	 -0.147621f,  0.716567f,  0.681718f,
	  0.147621f,  0.716567f,  0.681718f,
	  0.000000f,  0.525731f,  0.850651f,
	  0.309017f,  0.500000f,  0.809017f,
	  0.525731f,  0.000000f,  0.850651f,
	  0.295242f,  0.000000f,  0.955423f,
	  0.442863f,  0.238856f,  0.864188f,
	  0.162460f,  0.262866f,  0.951056f,
	 -0.681718f,  0.147621f,  0.716567f,
	 -0.809017f,  0.309017f,  0.500000f,
	 -0.587785f,  0.425325f,  0.688191f,
	 -0.850651f,  0.525731f,  0.000000f,
	 -0.864188f,  0.442863f,  0.238856f,
	 -0.716567f,  0.681718f,  0.147621f,
	 -0.688191f,  0.587785f,  0.425325f,
	 -0.500000f,  0.809017f,  0.309017f,
	 -0.238856f,  0.864188f,  0.442863f,
	 -0.425325f,  0.688191f,  0.587785f,
	 -0.716567f,  0.681718f, -0.147621f,
	 -0.500000f,  0.809017f, -0.309017f,
	 -0.525731f,  0.850651f,  0.000000f,
	  0.000000f,  0.850651f, -0.525731f,
	 -0.238856f,  0.864188f, -0.442863f,
	  0.000000f,  0.955423f, -0.295242f,
	 -0.262866f,  0.951056f, -0.162460f,
	  0.000000f,  1.000000f,  0.000000f,
	  0.000000f,  0.955423f,  0.295242f,
	 -0.262866f,  0.951056f,  0.162460f,
	  0.238856f,  0.864188f,  0.442863f,
	  0.262866f,  0.951056f,  0.162460f,
	  0.500000f,  0.809017f,  0.309017f,
	  0.238856f,  0.864188f, -0.442863f,
	  0.262866f,  0.951056f, -0.162460f,
	  0.500000f,  0.809017f, -0.309017f,
	  0.850651f,  0.525731f,  0.000000f,
	  0.716567f,  0.681718f,  0.147621f,
	  0.716567f,  0.681718f, -0.147621f,
	  0.525731f,  0.850651f,  0.000000f,
	  0.425325f,  0.688191f,  0.587785f,
	  0.864188f,  0.442863f,  0.238856f,
	  0.688191f,  0.587785f,  0.425325f,
	  0.809017f,  0.309017f,  0.500000f,
	  0.681718f,  0.147621f,  0.716567f,
	  0.587785f,  0.425325f,  0.688191f,
	  0.955423f,  0.295242f,  0.000000f,
	  1.000000f,  0.000000f,  0.000000f,
	  0.951056f,  0.162460f,  0.262866f,
	  0.850651f, -0.525731f,  0.000000f,
	  0.955423f, -0.295242f,  0.000000f,
	  0.864188f, -0.442863f,  0.238856f,
	  0.951056f, -0.162460f,  0.262866f,
	  0.809017f, -0.309017f,  0.500000f,
	  0.681718f, -0.147621f,  0.716567f,
	  0.850651f,  0.000000f,  0.525731f,
	  0.864188f,  0.442863f, -0.238856f,
	  0.809017f,  0.309017f, -0.500000f,
	  0.951056f,  0.162460f, -0.262866f,
	  0.525731f,  0.000000f, -0.850651f,
	  0.681718f,  0.147621f, -0.716567f,
	  0.681718f, -0.147621f, -0.716567f,
	  0.850651f,  0.000000f, -0.525731f,
	  0.809017f, -0.309017f, -0.500000f,
	  0.864188f, -0.442863f, -0.238856f,
	  0.951056f, -0.162460f, -0.262866f,
	  0.147621f,  0.716567f, -0.681718f,
	  0.309017f,  0.500000f, -0.809017f,
	  0.425325f,  0.688191f, -0.587785f,
	  0.442863f,  0.238856f, -0.864188f,
	  0.587785f,  0.425325f, -0.688191f,
	  0.688191f,  0.587785f, -0.425325f,
	 -0.147621f,  0.716567f, -0.681718f,
	 -0.309017f,  0.500000f, -0.809017f,
	  0.000000f,  0.525731f, -0.850651f,
	 -0.525731f,  0.000000f, -0.850651f,
	 -0.442863f,  0.238856f, -0.864188f,
	 -0.295242f,  0.000000f, -0.955423f,
	 -0.162460f,  0.262866f, -0.951056f,
	  0.000000f,  0.000000f, -1.000000f,
	  0.295242f,  0.000000f, -0.955423f,
	  0.162460f,  0.262866f, -0.951056f,
	 -0.442863f, -0.238856f, -0.864188f,
	 -0.309017f, -0.500000f, -0.809017f,
	 -0.162460f, -0.262866f, -0.951056f,
	  0.000000f, -0.850651f, -0.525731f,
	 -0.147621f, -0.716567f, -0.681718f,
	  0.147621f, -0.716567f, -0.681718f,
	  0.000000f, -0.525731f, -0.850651f,
	  0.309017f, -0.500000f, -0.809017f,
	  0.442863f, -0.238856f, -0.864188f,
	  0.162460f, -0.262866f, -0.951056f,
	  0.238856f, -0.864188f, -0.442863f,
	  0.500000f, -0.809017f, -0.309017f,
	  0.425325f, -0.688191f, -0.587785f,
	  0.716567f, -0.681718f, -0.147621f,
	  0.688191f, -0.587785f, -0.425325f,
	  0.587785f, -0.425325f, -0.688191f,
	  0.000000f, -0.955423f, -0.295242f,
	  0.000000f, -1.000000f,  0.000000f,
	  0.262866f, -0.951056f, -0.162460f,
	  0.000000f, -0.850651f,  0.525731f,
	  0.000000f, -0.955423f,  0.295242f,
	  0.238856f, -0.864188f,  0.442863f,
	  0.262866f, -0.951056f,  0.162460f,
	  0.500000f, -0.809017f,  0.309017f,
	  0.716567f, -0.681718f,  0.147621f,
	  0.525731f, -0.850651f,  0.000000f,
	 -0.238856f, -0.864188f, -0.442863f,
	 -0.500000f, -0.809017f, -0.309017f,
	 -0.262866f, -0.951056f, -0.162460f,
	 -0.850651f, -0.525731f,  0.000000f,
	 -0.716567f, -0.681718f, -0.147621f,
	 -0.716567f, -0.681718f,  0.147621f,
	 -0.525731f, -0.850651f,  0.000000f,
	 -0.500000f, -0.809017f,  0.309017f,
	 -0.238856f, -0.864188f,  0.442863f,
	 -0.262866f, -0.951056f,  0.162460f,
	 -0.864188f, -0.442863f,  0.238856f,
	 -0.809017f, -0.309017f,  0.500000f,
	 -0.688191f, -0.587785f,  0.425325f,
	 -0.681718f, -0.147621f,  0.716567f,
	 -0.442863f, -0.238856f,  0.864188f,
	 -0.587785f, -0.425325f,  0.688191f,
	 -0.309017f, -0.500000f,  0.809017f,
	 -0.147621f, -0.716567f,  0.681718f,
	 -0.425325f, -0.688191f,  0.587785f,
	 -0.162460f, -0.262866f,  0.951056f,
	  0.442863f, -0.238856f,  0.864188f,
	  0.162460f, -0.262866f,  0.951056f,
	  0.309017f, -0.500000f,  0.809017f,
	  0.147621f, -0.716567f,  0.681718f,
	  0.000000f, -0.525731f,  0.850651f,
	  0.425325f, -0.688191f,  0.587785f,
	  0.587785f, -0.425325f,  0.688191f,
	  0.688191f, -0.587785f,  0.425325f,
	 -0.955423f,  0.295242f,  0.000000f,
	 -0.951056f,  0.162460f,  0.262866f,
	 -1.000000f,  0.000000f,  0.000000f,
	 -0.850651f,  0.000000f,  0.525731f,
	 -0.955423f, -0.295242f,  0.000000f,
	 -0.951056f, -0.162460f,  0.262866f,
	 -0.864188f,  0.442863f, -0.238856f,
	 -0.951056f,  0.162460f, -0.262866f,
	 -0.809017f,  0.309017f, -0.500000f,
	 -0.864188f, -0.442863f, -0.238856f,
	 -0.951056f, -0.162460f, -0.262866f,
	 -0.809017f, -0.309017f, -0.500000f,
	 -0.681718f,  0.147621f, -0.716567f,
	 -0.681718f, -0.147621f, -0.716567f,
	 -0.850651f,  0.000000f, -0.525731f,
	 -0.688191f,  0.587785f, -0.425325f,
	 -0.587785f,  0.425325f, -0.688191f,
	 -0.425325f,  0.688191f, -0.587785f,
	 -0.425325f, -0.688191f, -0.587785f,
	 -0.587785f, -0.425325f, -0.688191f,
	 -0.688191f, -0.587785f, -0.425325f
};


