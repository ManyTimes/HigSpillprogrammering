//GLOBAL VARIABLES USED THROUGHOUT THE PROGRAM
///////////////////////////////////////
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include "include.h"

//GLOBAL VARIABLES
extern std::string SERVERNAME;				//Received from server upon joining
extern std::string JOINADDRESS;
extern std::string JOINPORTNUMBER;
extern std::string PLAYERNAME;
extern int MAXIMUMPLAYERS;
extern int playerNumber;					//Received from server upon joining
extern int SCREENWIDTH;
extern int SCREENHEIGHT;
extern int SLEEPTIME;
extern bool play;	
extern std::string messageFeedback;
extern bool SERVERRESPONSE;


//GLOBAL OBJECTS
extern cgl::ModelMD2* rock;
extern cgl::NetworkClient* client;
extern cgl::Terrain* terrain;
extern cgl::Grid* grid;
extern cgl::OpenGL* opengl;
extern cgl::Image2D* imgbtnCancel;			//Texture for the btnCancel
extern cgl::Image2D* imgbtnCancelClicked;	//Texture for the btnCancel
extern cgl::Image2D* imgbtnExit;			//Texture for the btnExit
extern cgl::Image2D* imgbtnExitClicked;		//Texture for the btnExit
extern cgl::Image2D* imgbtnStart;			//Texture for the btnStart
extern cgl::Image2D* imgbtnStartClicked;	//Texture for the btnStart
extern cgl::Image2D* imgbtnQuitGame;			//Image 
extern cgl::Image2D* imgbtnQuitGameClicked;	//Image
extern cgl::Button* btnStart;				//Joins server and starts drawing game
extern cgl::Button* btnExit;				//An Exit program button
extern cgl::Button* btnCancel;				//An Exit program button
extern cgl::Button* btnQuitGame;			//Quit the game, server you joined
extern cgl::Time* gametime;
extern cgl::Keyboard* keyboard;
extern cgl::Mouse* mouse;
extern cgl::Player* player;					//Recieves xyz, playernames, etc from server when joining
extern cgl::Text* text;						//Drawing some text, chat? All text drawn through this obj.
extern cgl::Text* textFeedback;				//Drawing some text, chat? All text drawn through this obj.
extern cgl::Sound* music;					//Background music...always runs, or "F10" to start stop...
extern cgl::Sound* soundAttack;				//Sound played when you attack (throw)
extern cgl::Sound* soundHit;				//Sound played when you are hit
extern cgl::Image2D* imgMenu;	
extern cgl::Image2D* imgBackground;
extern cgl::Weather* weather;
extern cgl::Image2D* weatherTexture;			//Loads a texture from the harddrive

//GAME/SERVER DATA
extern int gamestate;						//0 = mainmenu, 1 = game, 2 = game + menu drawn above it (cancel/exit)

#endif
