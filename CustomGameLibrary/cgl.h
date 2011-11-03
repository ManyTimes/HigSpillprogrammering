#ifndef _CGL_LIB_
#define _CGL_LIB_

//COPYRIGHT: ØYVIND, NICOLAS, THOMAS, HENRIK, KNUT, 2011-2016.
//CONTACT US AT colaoye@hotmail.com for lisence information


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
#include "../../CustomGameLibrary/Header/sound.h"
#include "../../CustomGameLibrary/Header/terrain.h"
#include "../../CustomGameLibrary/Header/weather.h"
#include "../../CustomGameLibrary/Header/time.h"
#else
#include "Header/grid.h"
#include "Header/camera.h"
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
#include "../../CustomGameLibrary/Header/birch.h"
#include "../../CustomGameLibrary/Header/entity.h"
#else
#include "Header/projectile.h"
#include "Header/birch.h"
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
#else
#include "Header/Image2d.h"
#include "Header/opengl.h"
#include "Header/model3d.h"
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

