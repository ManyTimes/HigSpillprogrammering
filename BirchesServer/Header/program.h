//THIS IS THE MAIN GAME LOOP
///////////////////////////////////////
#ifndef _GAME_H
#define _GAME_H

#include "events.h"

extern int gamestate;

void Program();
void Update();
void Network();
void Events();
void Render();
std::string GetPlayerName();

#endif