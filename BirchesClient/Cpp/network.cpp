#include "../Header/network.h"

void ReadData();
void SendData();
void ReadServerData();

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
			SendData();
		}
	}
}

//Sends all data needed to the server when it is required to send new data
void SendData()
{
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
		player = new cgl::Player[MAXIMUMPLAYERS];

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
			//std::cout << "Player " << i << " name: " << player[i].playername << " XYZ " << player[i].position.x << "," << player[i].position.y << std::endl;
			//player[i].SetModel("Data/TestModel.3ds");
		}
	}
}

//Reads data from server
void ReadData()
{

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