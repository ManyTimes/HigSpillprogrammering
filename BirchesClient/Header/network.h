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

//Helper functions
int GetIntValue(char end);
int GetFloatValue(char end);
std::string GetStringValue(char end);
#endif