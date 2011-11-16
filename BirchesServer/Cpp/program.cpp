#include "../Header/program.h"

using namespace std;

void Program()
{
	int programtime = 1;					//Example of a game loop
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
		SDL_Delay(10);					//10 sleep, each case is ran at "25 fps " (25 times a second)
	}
	std::cout << std::endl << "PROGRAM EXITS" << std::endl;
	opengl->Exit();
	server->Exit();
}

void Render()
{
	opengl->StartDraw();
	btnExit->Draw();
	opengl->CreateViewport2D(SCREENWIDTH,SCREENHEIGHT,0, 0, -0, 0);			//Drawing text requires viewport 2D, with Z far and Z near to be 0
	text->Draw("Players Playing", -300,550);
	text->Draw("Kills", 400,550);
	text->Draw("Deaths", 600,550);
	btnExit->Draw();
	char temp[10];
	for(int i = 0; i < MAXIMUMPLAYERS; i++)
	{
		text->Draw((char*)player[i].playername.c_str(), -300, 500 - (35*i));
		cgl::i2c(temp, player[i].kills);
		text->Draw(temp, 400,  500 - (35*i));
		cgl::i2c(temp, player[i].deaths);
		text->Draw(temp, 600,  500 - (35*i));
	}
	btnExit->Draw();
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
	if(server->IsClientIncoming() != 0)			//If not 0, a client tries to join the server
	{
		server->CreateClient();					//New client arrived
		//New client, placing new player randomly on the map
		player[server->clientcount-1].SetPosition(cgl::GetRandomFloat(-5.0, 5.0), 1, cgl::GetRandomFloat(-5.0, 5.0));
		std::string serverData = cgl::i2s(MAXIMUMPLAYERS) + "|";			//Send data of all players to joining player
		for(int i = 0; i < server->clientcount; i++)
		{
			cgl::Vector3f& ref = player[i].GetPositionRef();
			serverData += player[i].playername
				+ "?" + cgl::i2s(player[i].kills)
				+ "?" + cgl::i2s(player[i].deaths)
				+ "?" + cgl::f2s(ref.x)
				+ "?" + cgl::f2s(ref.y)
				+ "?" + cgl::f2s(ref.z) + "?|";
		}
		server->SendData(server->clientcount-1, serverData.c_str());

	}
	for(int i = 0; i < server->clientcount; i++)
	{
		if(server->ReadReceivedData(i) == 1)	//Data from client/player i has arrived
		{
			
			//Data received from Clients
			//0 - Playername only, init
			//1 - XYZ
			//2 - Action - shooting in direction with what ability/damage
			//3 - Player kills someone, kills are updated
			//4 - Player dies, death is updated
			//5 - Client sends exit, reseting the player at this position and closing socket
			std::string col[] = { "ID" };
			switch(server->buffer[0])
			{
			case '0':
				sqlcmd->Execute("SELECT ID FROM [Player] WHERE playername = '" + GetPlayerName() + "';",col, 1);
				if(sqlcmd->totalRows < 1)
				{
					sqlcmd->Execute("INSERT INTO [Player] (playername, kills, deaths) VALUES ('" + GetPlayerName() + "', 0,0);");
				}
				player[i].playername = GetPlayerName();
				break;
			case '1':							//new player position incomming
				{
					for (int i = 0; i < server->clientcount; i++)	//Sends the position data back out to all players connected
					{
						server->SendData(i, server->buffer);
					}
					break;
				}
			case '2':
				

				break;
			case '3':
				{
					for (int i = 0; i < server->clientcount; i++)
					{
						server->SendData(i, server->buffer);
					}
					break;
				}
			case '4':
				{
					for (int i = 0; i < server->clientcount; i++)
					{
						server->SendData(i, server->buffer);
					}
				}
				break;
			case '5':	//Client has left the game
				player[i].playername = "<Empty Slot>";
				server->CloseClient(i);
				break;
			default:
				break;
			}
		}
	}
}

//Returns the value except for the 
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