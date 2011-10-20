#ifndef _CGL_LIB_
#define _CGL_LIB_

//File to include in your program, client or server program.
//This file then includes all objects and functions in the library, making them
//available inside your program.


//COPYRIGHT: ØYVIND, NICOLAS, THOMAS, HENRIK, KNUT

//NETWORK
#include "../Header/networkserver.h"
#include "../Header/networkclient.h"

//ENVIRONMENT
#include "../Header/sound.h"
#include "../Header/terrain.h"
#include "../Header/weather.h"

//SQL
#include "../Header/sqlconnection.h"
#include "../Header/sqlcommand.h"
#include "../Header/sqlresult.h"
#include "../Header/sqlrow.h"

//UNIT
#include "../Header/ability.h"
#include "../Header/birch.h"
#include "../Header/entity.h"
#include "../Header/npc.h"
#include "../Header/player.h"

//UI
#include "../Header/button.h"
#include "../Header/menu.h"
#include "../Header/text.h"


#include "../Header/keyboardlistener.h"
#include "../Header/function.h"

#endif
