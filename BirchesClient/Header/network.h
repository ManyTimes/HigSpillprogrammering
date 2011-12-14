#ifndef _NETWORK_H
#define _NETWORK_H
#include "include.h"
#include "globals.h"

void Network();
void ConnectToServer();
void DisconnectFromServer();
<<<<<<< HEAD


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
=======
void SendPosition();
>>>>>>> 7e6b5d9d8859e1cfa0ad316f15b32a8f31be387c
#endif