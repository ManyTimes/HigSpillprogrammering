#include "../Header/program.h"

using namespace std;

std::string col[] = { "ID", "kills", "deaths" };
cgl::Vector3f refEmpty;
cgl::Vector3f& ref = refEmpty;
std::string serverData ="";				//Data to be sent to Client/s
std::string readData = "";				//Data from a Client
std::string temp = "";
int playernumber = 0;					//Current player to work on
int ii = 0;								//Loop of data read [ii]
float yaw = 0;
float x,y,z;

void CoutVec(cgl::Vector3f vec)
{
	std::cout << " Vector: " << vec.x << " ," << vec.y << " " << vec.z << std::endl;
}

void CoutVec(cgl::Vector3f vec, std::string msg)
{
	std::cout << msg;
	CoutVec(vec);
}


//Main loop of the program
void Program()
{
	x = y = z  =0;
	server->CallbackOnClientClosed(ClientClosed);
	int programtime = 1;				//Example of a game loop
	int render = 1;
	while(play)
	{
		switch(programtime)
		{
		case 1:							//Render stuff, call <object>->Draw();
			Render();
			break;
		case 2:							//Takes input, keyboard/mouse
			Events();
			break;
		case 3:							//Do network related stuff, send, read recieved
			Network();
			break;
		case 4:							//Do calculations, collision, grid Update...etc
			Update();
			break;
		}
		programtime++;
		if(programtime > 4)
		{
			programtime = 1;
		}
		cgl::Sleep(5);					//Switch runs each 0.01 seconds, each case runs therefore each 0.04 seconds, which is 25 "fps"
		//cgl::Thread netThread = new cgl::Thread(functionNetworkLoop);, network would run on a diff thread, creating a mutex...
		//netThread.Start();
		//netThread.Exit();
	}
	std::cout << std::endl << "PROGRAM EXITS" << std::endl;
	//This should actually be something like "cgl::CGLExit();" ... And cgl::CGLInit();" starts all libs... (includes them at least...)
	opengl->Exit();
	server->Exit();
}

void Render()
{
	opengl->StartDraw();
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, -0, 0);			//Drawing text requires viewport 2D, with Z far and Z near to be 0
	text->Draw("Players Playing", -300,550);
	text->Draw("Kills", 400,550);
	text->Draw("Deaths", 600,550);
	char temp[10];
	for(int i = 0; i < MAXIMUMPLAYERS; i++)
	{
		text->Draw((char*)player[i].playername.c_str(), -300, 500 - (35*i));
		cgl::i2c(temp, player[i].kills);
		text->Draw(temp, 400,  500 - (35*i));
		cgl::i2c(temp, player[i].deaths);
		text->Draw(temp, 600,  500 - (35*i));
	}
	std::string playersplaying = "";
	//playersplaying = ;
	text->Draw("Active players: ", -400, 0);
	text->Draw( (char*)cgl::i2s(server->clientcount).c_str(), -150, 0);
	text->Draw( (char*)cgl::i2s(server->GetNumberOfActiveSockets()).c_str(), -120, 0);
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, 0, 1);			//Drawing buttons requires Viewport 2D, with z far and near not equal each other, not 0
	btnExit->Draw();
	opengl->EndDraw();
}

void Events()
{
	KeyboardClicked();
	MouseClicked();
}

void Network()
{
	serverData = "";
	if(server->IsClientIncoming() != 0)			//If not 0, a client tries to join the server
	{
		server->CreateClient();					//Create new client; Init new unit
		int index = server->clientcount-1;		//Resetting the new player, to new position, etc.
		unit[index].SetPosition(cgl::GetRandomFloat(1.0, 63.0), 0, cgl::GetRandomFloat(1.0, 63.0));
		unit[index].position.y = terrain->GetHeight(unit[index].position.x, unit[index].position.z);
		unit[index].hitpoints = 100;
		unit[index].ID = index;
		unit[index].armor = 0;
		unit[index].damage = 10;
		unit[index].mana = 10;
		unit[index].action = 0;
		player[index].playername = "<Empty Slot>";
		player[index].ID = index;
		player[index].score = 0;
		simpleCamera[index].position = unit[index].position;

		serverData = cgl::i2s(MAXIMUMPLAYERS) + "|" + SERVERNAME + "|";								//Send data of all players to joining player; 
		for(int i = 0; i < server->clientcount-1; i++)								//format: count|playername?kills?deaths?posx?posy?posz?|playername?kills?...
		{
			serverData += player[i].playername
				+ "?" + cgl::i2s(player[i].kills)
				+ "?" + cgl::i2s(player[i].deaths)
				+ "?" + cgl::f2s(unit[i].position.x)
				+ "?" + cgl::f2s(unit[i].position.y)
				+ "?" + cgl::f2s(unit[i].position.z) + "?|";
		}
		server->SendData(index, serverData);
	}
	for(int i = 0; i < server->clientcount; i++)
	{
		serverData = "";
		if(server->ReadReceivedData(i) == 1)	//Data from client/player i has arrived
		{
			readData = cgl::c2s(server->buffer);
			//Data received from Clients
			//0 - Playername only, Player connected to server with playername
			//1 - XYZ
			//2 - Action - shooting in direction with what ability/damage
			//3 - Player kills someone, kills are updated
			//4 - Player dies, death is updated
			//5 - Client sends exit, reseting the player at index and closing socket
			switch(server->buffer[0])
			{
			case '0':
				player[i].playername = GetPlayerName();
				sqlcmd->Execute("SELECT ID, kills, deaths FROM [Player] WHERE playername = '" + player[i].playername + "';",col, 3);
				if(sqlcmd->totalRows < 1)
				{
					sqlcmd->Execute("INSERT INTO [Player] (playername, kills, deaths) VALUES ('" + player[i].playername + "', 0,0);");
					player[i].deaths = 0;
					player[i].kills = 0;
				}
				else
				{
					player[i].kills = cgl::s2i(sqlcmd->result->GetValue(0, 1));			//Setting kills from DB
					player[i].deaths = cgl::s2i(sqlcmd->result->GetValue(0, 2));		//Setting deaths from DB	
				}
				serverData = "0|" + cgl::i2s(i) + "|" + player[i].playername + "|" + cgl::i2s(player[i].kills) + "|" + cgl::i2s(player[i].deaths) + "|" + cgl::f2s(unit[i].position.x) + "|"+ cgl::f2s(unit[i].position.y) + "|"+ cgl::f2s(unit[i].position.z);
				server->SendDataToConnectedClients(serverData);
				break;
			case '1':
				ii = 1;
				playernumber = GetIntValue('|');
				ii++;
				x = GetFloatValue('|');
				ii++;
				z = GetFloatValue('|');
				simpleCamera[playernumber].position.x = x;
				simpleCamera[playernumber].position.z = z;
				unit[playernumber].SetPosition(simpleCamera[playernumber].position);
				//Missing Y value, does not need that for calculating collision detection (as of v.1)

				server->SendDataToConnectedClients(server->buffer);
				//A player has moved, send it to all connected players
				//temp = "";
				//ii = 2;
				//playernumber = GetIntValue('|');	//Player that moved
				//ii++;		//Skip '|' char
				//yaw = GetFloatValue('|');
				//simpleCamera[playernumber].SetYaw(yaw);
				//if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
				//{
				//	switch(readData[1])
				//	{
				//	case 'W':
				//		simpleCamera[playernumber].MoveForward(0.25);
				//		break;
				//	case 'S':
				//		simpleCamera[playernumber].MoveBackwards(0.25);
				//		break;
				//	case 'A':
				//		simpleCamera[playernumber].MoveStrafeLeft(0.25);
				//		break;
				//	case 'D':
				//		simpleCamera[playernumber].MoveStrafeRight(0.25);
				//		break;
				//	default:
				//		break;
				//	}
				//	unit[playernumber].position = simpleCamera[playernumber].position;
				//	serverData = "1" + cgl::i2s(playernumber) + "|"
				//		+ cgl::f2s(simpleCamera[playernumber].position.x) + "|"
				//		+ cgl::f2s(simpleCamera[playernumber].position.z);
				//	server->SendDataToConnectedClients(serverData);
				//}
				//Y is gotten from heightmap, no need to send it.
				/*ii = 2;
				playernumber = GetIntValue('|');
				if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
				{
					switch(server->buffer[1])
					{
						case 'W':							//MOVES FORWARD
							simpleCamera[playernumber].MoveForward(0.25);
						case 'S':							//MOVES BACKWARDS
							simpleCamera[playernumber].MoveBackwards(0.25);
							break;
						case 'A':							//STRAFE LEFT
							simpleCamera[playernumber].MoveStrafeLeft(0.25);
							break;
						case 'D':							//STRAFE RIGHT
							simpleCamera[playernumber].MoveStrafeRight(0.25);
							break;
						default:
							break;
					}
					unit[playernumber].position.x = simpleCamera[playernumber].position.x;
					unit[playernumber].position.y = simpleCamera[playernumber].position.y;
					unit[playernumber].position.z = simpleCamera[playernumber].position.z;
					//Sends back current position of player
					serverData = "1" + cgl::f2s(unit[playernumber].position.x)
								+ "|" + cgl::f2s(unit[playernumber].position.y)
								+ "|" + cgl::f2s(unit[playernumber].position.z)
								+ "|" + temp;//Temp is playernumber
					server->SendDataToConnectedClients(serverData);
					CoutVec(unit[playernumber].position, " Unit Pos: ");*/
				break;
			case '2':			//Echoing everything out to all connected players, a player has fired a bullet
				//This is the bullet position and view direction.
				//This needs to be stored at server to use collision detection at server
				server->SendDataToConnectedClients(server->buffer);
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':	//Client has left the game
				//Why is this 5!?!?!?? Client sends "exit".
			/*	player[i].playername = "<Empty Slot>";
				player[i].ID = -1;
				player[i].score = 0;
				player[i].kills = 0;
				player[i].deaths = 0;
				server->SendDataToConnectedClients("5" + cgl::i2s(i) + "|");
				std::cout << "Player nr has left: " << i << std::endl;//Inform all players about laeving player
				server->CloseClient(i);*/
				break;
			default:
				break;
			}
		}
	}
}

//Returns playername from within the server->buffer object, only call this when a player has newly joined the server
std::string GetPlayerName()
{
	std::string temp = "";
	for(int i = 1; i < cgl::GetArrayLength(server->buffer);i++)
	{
		temp += server->buffer[i];
	}
	return temp;
}

void Update()
{
	//grid->Update();
}

void ClientClosed(int clientNumber)
{
	player[clientNumber].deaths = 0;
	player[clientNumber].kills = 0;
	player[clientNumber].playername = "<Empty Slot>";
	player[clientNumber].ID = -1;
	std::cout << "Player nr has left: " << clientNumber << std::endl;//Inform all players about laeving player
	serverData = "5" + cgl::i2s(clientNumber);
	server->SendDataToConnectedClients(serverData);
}


int GetIntValue(char end)
{
	temp = "";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	return cgl::s2i(temp);
}

int GetFloatValue(char end)
{
	temp = "";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	return cgl::s2f(temp);
}

std::string GetStringValue(char end)
{
	temp = "";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	return temp;
}

cgl::Vector3f GetVector3fValue(char end)
{
	cgl::Vector3f returnvalue;
	temp = "";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	returnvalue.x = cgl::s2f(temp);
	ii++;							//Skip 'end' character
	temp ="";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	returnvalue.y = cgl::s2f(temp);
	ii++;							//Skip 'end' character
	temp = "";
	do
	{
		temp += readData[ii];
		ii++;
	}while(readData[ii] != end && ii < readData.length());
	returnvalue.z = cgl::s2f(temp);
	return returnvalue;
}