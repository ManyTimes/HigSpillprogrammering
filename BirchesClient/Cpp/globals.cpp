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
int MAXIMUMPLAYERS;
int playerNumber;					//Clients' player number
int SLEEPTIME = 2;
bool play = true;	
std::string messageFeedback = "";
bool SERVERRESPONSE = false;		//When we join, we wait for a response from server
									//before a player can play/move/draw/render/send network stuff
//GLOBAL OBJECTS
cgl::ModelMD2* rock;
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
cgl::Image2D* imgbtnQuitGame;			//Image 
cgl::Image2D* imgbtnQuitGameClicked;	//Image
cgl::Button* btnStart;				//Joins server and starts drawing game
cgl::Button* btnExit;				//An Exit program button
cgl::Button* btnCancel;				//An Exit program button
cgl::Button* btnQuitGame;
cgl::Time* gametime;
cgl::Keyboard* keyboard;
cgl::Mouse* mouse;
cgl::Player* player;				//Recieves xyz, playernames, etc from server when joining
cgl::Text* text;					//Drawing some text, chat? All text drawn through this obj.
cgl::Text* textFeedback;	
cgl::Sound* music;					//Background music...always runs, or "F10" to start stop...
cgl::Sound* soundAttack;				//Sound played when you attack (throw)
cgl::Sound* soundHit;				//Sound played when you are hit
cgl::Weather* weather;
cgl::Image2D* weatherTexture;			

//GAME/SERVER DATA
 int gamestate;						//0 = mainmenu, 1 = game, 2 = game + menu drawn above it (cancel/exit)

