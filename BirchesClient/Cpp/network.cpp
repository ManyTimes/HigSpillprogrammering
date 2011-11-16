#include "../Header/network.h"
#include <string>

void ReadData();
void SendPosition();
void SendKill();
void SendDeath();
void ReadServerData();
cgl::Vector3f FindPosFromString(std::string Datastring);

void Network()
{
	if(gamestate == 1)					//Game playing
	{
		if(SERVERRESPONSE == false)
		{
			ReadServerData();			//Waiting on server to respond with how many players are playing
		}								//Their names, stats and position
		else
		{
			ReadData();
		}
	}
}

//Sends players position
void SendPosition()
{
	std::string Datastring = "1";			//1 because it's position being sendt

	cgl::Vector3f pPos = player->GetPositionRef();; //Should this be position ref?
	
	Datastring += cgl::i2s(player->ID)
		+ "?" + cgl::f2s(pPos.x)
		+ "?" + cgl::f2s(pPos.y)
		+ "?" + cgl::f2s(pPos.z) + "?|";


	client->SendData(Datastring);
}
//TODO, As of now, this function only sends which player gets the kill, which is ok for stats alone,
//but we probably want some kind of ingame visual as to who kills who, then this function has to be expanded.
void SendKill()
{
	std::string Datastring = "3"
		+ cgl::i2s(player->ID);
	
	client->SendData(Datastring);
}

void SendDeath()
{
	std::string Datastring = "4"
		+ cgl::i2s(player->ID);

	client->SendData(Datastring);
}
	
//Reads all players currently playing's information, stats and position
void ReadServerData()
{
	std::string data = client->ReadReceivedData();
	if(data == "0")
	{
	}
	else
	{	
		std::string temp = "";
		std::cout << data << std::endl;
		int i = 0;					//Character number in the "data"
		do
		{
			temp += data[i];
			i++;
		}while(data[i] != '|' && i < data.length());//Exit at first |, maximumplayers is read
		MAXIMUMPLAYERS = cgl::s2i(temp);
		player = new cgl::Player[MAXIMUMPLAYERS];	//Får fra serveren hvor mange sspillere smo kan MAX spille... oppretter da en array så stor.. :P

		float x;
		float y;
		float z;
		i ++;						//Adding 1, skipping the '|' character

		if(i == data.length())
		{
			std::cout << "Error; could not retreive data from server" << std::endl;
		}
		else
		{
			//Start converting data from server, to client, create player objects
			temp = "";
			int value = 0;
			int playernumber = 0;
			for(; i < data.length()-1; i ++)//Lfast character is '|', hence -1
			{
				if(data[i] == '|')
				{
					std::cout << "Player " << playernumber << " XYZ " << x << " " << y << " " << z << std::endl;
					temp = "";			//Reset, new player read
					value = 0;
					playernumber ++;	//Next player
				}
				else
				{
					if(data[i] != '?')
					{
						temp += data[i];
					}
				}
				if(data[i] == '?')		//Value to insert into player
				{
					switch(value)
					{
					case 0:				//Playername is read
						player[playernumber].playername = temp;
						temp = "";
						break;
					case 1:				//A players kills is read
						player[playernumber].kills = cgl::s2i(temp);
						temp = "";
						break;
					case 2:				//A players deaths is read
						player[playernumber].kills = cgl::s2i(temp);
						temp = "";
						break;
					case 3:				//Position X
						x = cgl::c2f((char*)temp.c_str());
						temp = "";
						break;
					case 4:				//Position Y
						y = cgl::c2f((char*)temp.c_str());
						temp = "";
						break;
					case 5:				//Position Z
						z = cgl::c2f((char*)temp.c_str());
						player[playernumber].SetPosition(x,y,z);
						temp = "";
						break;
					default: 
						break;
					}
					value++;
				}
			}

			SERVERRESPONSE = true;		//Ready to play, got all data we need
		}
		for(i = 0; i < MAXIMUMPLAYERS; i++)
		{
		//	std::cout << "Player " << i << " name: " << player[i].playername << " XYZ " << player[i].position.x << "," << player[i].position.y << std::endl;
		//	player[i].SetModel("Data/TestModel.3ds");
		}
	}
}

//Reads data from server
void ReadData()
{	
	std::string Datastring = client->ReadReceivedData();
	if(Datastring[1] != '\0')		//Server data is incomming. TODO not quite sure about is one, check with the others, problem because 
									//ReadReceivedData returnes 0 on fail, but 0 may also be a valid value at the start of the array
	{
		//Data comming from server:
		//0 - Playername only, init
		//1 - XYZ
		//2 - Action - shooting in direction with what ability/damage
		//3 - Player kills someone, kills are updated
		//4 - Player dies, death is updated
		switch (Datastring[0])
		{
		case '0': 
			{
				std::string pName; 
				for (int i = 1; Datastring[i] != '?'; i++)
				{
					pName += Datastring[i];
				}
				player[Datastring[1]].playername = pName;
			}

			break;
		case '1':							//new position comming
			{
			int playerID;
			playerID = Datastring[1];

			cgl::Vector3f PlayerPos = FindPosFromString(Datastring);
			player[playerID].SetPosition(PlayerPos);
			break;
			}
		case '2':
			break;
		case '3':
			player[Datastring[1]].kills +=1;
			break;
		case '4':
			player[Datastring[1]].deaths +=1;
			break;
		}

	}
}
void ConnectToServer()
{
	if(client->Connect(1000) == false)
	{
		messageFeedback = "Could not connect to server. Server might be down, try again later";
	}
	else
	{
		//Data is split at server:
		//0 - Playername only, init
		//1 - XYZ
		//2 - Action - shooting in direction with what ability/damage
		//3 - Player kills someone, kills are updated
		//4 - Player dies, death is updated
		client->SendData("0" + PLAYERNAME);
	}
}

void DisconnectFromServer()
{
	client->SendData("5");			//Exit
	SDL_Delay(25);					//Give socket time to send "exit" to server
}
///TODO, update and clean up this function
cgl::Vector3f FindPosFromString(std::string Datastring)		//turns a postion string into 3 floats and puts with into a vector
{															//would be easier with a stirng but there is currently no s2f function so this is done with a char array
		int teller = 0;					
		cgl::Vector3f PlayerPos;

		char temp[5];					//used to turn the positions back into floats
											
		for (int i = 2; Datastring[i] != '?'; i++)	//i starting at 2 because the first char of the first position is always there
		{
			temp[i] = Datastring[i];
			teller++;								//keeps track of how far into the string we are
		}
		teller++;									//add one more to skip the '?'
		PlayerPos.x = cgl::c2f(temp);	
	
		for (int i = 2+teller; Datastring[i] != '?'; i++)
		{
			temp[i] = Datastring[i];
			teller++;
		}
		teller++;
		PlayerPos.y = cgl::c2f(temp);

		for (int i = 2+teller; Datastring[i] != '?'; i++)
		{
			temp[i] = Datastring[i];
			teller++;
		}

		PlayerPos.z = cgl::c2f(temp);
		
		return PlayerPos;
}