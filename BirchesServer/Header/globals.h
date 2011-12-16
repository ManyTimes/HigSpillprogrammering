//GLOBAL VARIABLES USED THROUGHOUT THE PROGRAM
///////////////////////////////////////
#ifndef _GLOBAL_H
#define _GLOBAL_H


#include "include.h"

//GLOBAL VARIABLES
extern std::string PORTNUMBER;
extern std::string SERVERNAME;
extern int MAXIMUMPLAYERS;
extern int PACKETSIZE;
extern int SCROLLBACK;
extern int GAMEID;
extern int DELAY;
extern int MAXPLAYERS;
extern std::string SQLSERVERNAME;
extern std::string SQLDATABASENAME;
extern std::string SQLUSER;
extern std::string SQLPASSWORD;
extern int SQLTIMEOUTSECONDS;
extern int SCREENWIDTH;
extern int SCREENHEIGHT;


//GLOBAL OBJECTS
extern cgl::NetworkServer* server;
extern cgl::Terrain* terrain;
extern cgl::Grid* grid;
extern cgl::SimpleCamera* simpleCamera;	//One for each player
extern cgl::OpenGL* opengl;
extern cgl::Image2D* imgbtnExit;		//Texture for the btnExit
extern cgl::Image2D* imgbtnExitClicked;	//Texture for the btnExit
extern cgl::Button* btnExit;			//An Exit program button
extern cgl::Time* gametime;
extern cgl::Keyboard* keyboard;
extern cgl::Mouse* mouse;
extern cgl::SqlConnection* sqlcon;
extern cgl::SqlCommand* sqlcmd;	
extern cgl::SqlResult* sqlresult;
extern cgl::Unit* unit;					//One unit per player object
extern cgl::Player* player;
extern cgl::Text* text;

//GAME/SERVER DATA
extern bool play;

#endif
