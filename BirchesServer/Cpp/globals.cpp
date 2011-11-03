#include "../Header/globals.h"

//CONSTANT DATA
const float _180_OVER_PI = 180/PI;
std::string PORTNUMBER;
std::string SERVERNAME;
int MAXIMUMPLAYERS;
int PACKETSIZE;
int SCROLLBACK;
int GAMEID;
int DELAY;
int MAXPLAYERS;
std::string SQLSERVERNAME;
std::string SQLDATABASENAME;
std::string SQLUSER;
std::string SQLPASSWORD;
int SQLTIMEOUTSECONDS;
int SCREENWIDTH = 800;
int SCREENHEIGHT = 600;

//OBJECT DATA
cgl::NetworkServer* server;				//Establish a server, listen on port N
cgl::Terrain* terrain;					//Heightmap
cgl::Sound* music;						//Play a music, game-theme-song
cgl::OpenGL* opengl;					//OpenGL object for creating window, viewports...
cgl::Button* btnExit;
cgl::Button* btnCancel;				
cgl::Time* gametime;					//Display current time?
cgl::Weather* weather;					//Draw weather?
cgl::Camera* camera;		
cgl::Keyboard* keyboard;
cgl::Mouse* mouse;					
cgl::SqlConnection* sqlcon;				//Connects to DB
cgl::SqlCommand* sqlcmd;				//Runs a query against the sqlcon
cgl::SqlResult* sqlresult;				//If query is a select-statement, it can be held within this object
cgl::Grid* grid;						//Grid upon the terrain
cgl::Player* player;
cgl::Image2D* imgbtnExit;
cgl::Image2D* imgbtnExitClicked;
cgl::Text* text;

//GAME/SERVER DATA
bool play = true;						//False, and server/program exits
