#ifndef _NETWORK_H
#define _NETWORK_H
#include "include.h"
#include "globals.h"

void Network();
void ConnectToServer();
void DisconnectFromServer();


//Move Events
void SendDataForward();
void SendDataBackward();
void SendDataLeft();
void SendDataRight();
void SendDataShoot();
void SendHasLeftTheGame();

//Helper functions
int GetIntValue(char end);
float GetFloatValue(char end);
std::string GetStringValue(char end);
void GetVector3fValue(char end);
#endif