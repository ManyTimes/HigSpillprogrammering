#ifndef _CGL_LIB_
#define _CGL_LIB_

//COPYRIGHT: ØYVIND, NICOLAS, THOMAS, HENRIK, KNUT, 2011-2016.
//CONTACT US AT colaoye@hotmail.com for lisence information

//Missing in CGL to be a decent library for any PC game 
//Working Camera FPS/RTS/Third Person
//Particle [missile] calculate path from one destination to another [ based on entity to be used within Grid]
//UDP networking
//Ray-picking or selection of objects throguh GLSELECTION (?)
//Fully working grid that returns entity upon "hit". (Can use grid with raypicking to effectivily get the selected unit)
//Some objects renders strangely, glPush or not glPush...
//Sprite loading of images, and rendering sprites.
//MD5
//Textbox
//Label
//Button with a working "onclick texture", it should be displayed for "5-10" frame updates (OnClickTextureDuration::Long/Short) (5 or 15)




//NETWORK
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/networkserver.h"
#include "../../CustomGameLibrary/Header/networkclient.h"
#else
#include "Header/networkserver.h"
#include "Header/networkclient.h"
#endif


//ENVIRONMENT
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/grid.h"
#include "../../CustomGameLibrary/Header/camera.h"
#include "../../CustomGameLibrary/Header/simplecamera.h"
#include "../../CustomGameLibrary/Header/sound.h"
#include "../../CustomGameLibrary/Header/terrain.h"
#include "../../CustomGameLibrary/Header/weather.h"
#include "../../CustomGameLibrary/Header/time.h"
#else
#include "Header/grid.h"
#include "Header/camera.h"
#include "Header/simplecamera.h"
#include "Header/sound.h"
#include "Header/terrain.h"
#include "Header/weather.h"
#include "Header/time.h"
#endif


//SQL
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/sqlconnection.h"
#include "../../CustomGameLibrary/Header/sqlcommand.h"
#include "../../CustomGameLibrary/Header/sqlresult.h"
#include "../../CustomGameLibrary/Header/sqlrow.h"
#else
#include "Header/sqlconnection.h"
#include "Header/sqlcommand.h"
#include "Header/sqlresult.h"
#include "Header/sqlrow.h"
#endif


//PLAYER
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/player.h"
#else
#include "Header/player.h"
#endif

//UNIT
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/projectile.h"
#include "../../CustomGameLibrary/Header/projectilebullet.h"
#include "../../CustomGameLibrary/Header/unit.h"
#include "../../CustomGameLibrary/Header/entity.h"
#else
#include "Header/projectile.h"
#include "Header/projectilebullet.h"
#include "Header/unit.h"
#include "Header/entity.h"
#endif


//UI
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/button.h"
#include "../../CustomGameLibrary/Header/text.h"
#else
#include "Header/button.h"
#include "Header/text.h"
#endif


//GRAPHICS
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/Image2d.h"
#include "../../CustomGameLibrary/Header/opengl.h"
#include "../../CustomGameLibrary/Header/model3d.h"
#include "../../CustomGameLibrary/Header/modelmd2.h"
#include "../../CustomGameLibrary/Header/model.h"
#else
#include "Header/image2d.h"
#include "Header/opengl.h"
#include "Header/model.h"
//#include "Header/model3d.h"
//#include "Header/modelmd2.h"
#endif

//OTHER
#ifdef _CGLPROGRAM
#include "../../CustomGameLibrary/Header/function.h"
#include "../../CustomGameLibrary/Header/keyboard.h"
#include "../../CustomGameLibrary/Header/mouse.h"
#else
#include "Header/function.h"
#include "Header/keyboard.h"
#include "Header/mouse.h"
#endif

#endif			//End IFNDEF _CGL_H

