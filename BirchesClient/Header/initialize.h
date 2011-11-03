//LOADS DATA INTO MEMORY AT PROGRAM START
///////////////////////////////////////////
#ifndef _INITIALIZE_H
#define _INITIALIZE_H

#include "include.h"
#include "globals.h"
using namespace std;

//Loads everything at program start
void Initialize(); 

//Function declarations
void ReadConfigurationFile();
string ReturnConfigurationValue(string readline);
void InitializeRender();
void InitializeGame();



#endif