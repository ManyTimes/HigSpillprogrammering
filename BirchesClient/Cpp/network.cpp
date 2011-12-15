#include "../Header/network.h"

void ReadData();
void ReadServerData();

std::string data = "";
std::string temp = "";
int playernumber = 0;
int i = 0;
int ii = 0;
float x,y,z;
bool hasSent[5];

//Called each game-loop sequence
void Network()
{
	for(i = 0 ; i < 5; i++)
	{
		hasSent[i] = false;
	}
	i = 0;
	if(gamestate == 1)					//Game playing
	{
		if(SERVERRESPONSE == false)		//We sent "0" + playername to server. Need response from server  before continuing. Need two responses before continuing
		{
			ReadServerData();			//Waiting on server to respond with how many players are playing
		}								//Their names, stats and position
		else
		{
			ReadData();					//Start listening to actions, player left, player moves, etc
		}
	}
}

//Sends all data needed to the server when it is required to send new data
void SendDataForward()
{
	if(hasSent[0] == false)				//Even if events, click action fires multiple times, we send only once per game-loop-sequence
	{
		client->SendData("1z1" + cgl::i2s(thisPlayer));		//Moving Z positive Player
		
		//That is basically it, sending action and position.
		//And from the server we get position of others (and our own HP if it dropped, we were damaged.)
		//And if it dropped below 0 , we died and got a whole new position, and text of who killed us:
		//format: case|2|playerKilling|x|y|z (new position)
		//If player[thisPlayer].action != 0, send playernumber, xyz, action
		//else send playernumber, xyz
			//Send Playernumber, X,Y,Z
		hasSent[0] = true;
	}
}

void SendDataBackward()
{
	if(hasSent[1] == false)	
	{	
		client->SendData("1z0" + cgl::i2s(thisPlayer));		//Moving Z negative Player
		hasSent[1] = true;
	}
}

void SendDataLeft()
{
	if(hasSent[2] == false)	
	{
		client->SendData("1x0" + cgl::i2s(thisPlayer));		//Moving X negative Player
		hasSent[2] = true;
	}
}

void SendDataRight()
{
	if(hasSent[3] == false)	
	{
		client->SendData("1x1" + cgl::i2s(thisPlayer));		//Moving X positive Player
		hasSent[3] = true;
	}
}

void SendDataShoot()
{
	if(hasSent[4] == false)	
	{
		hasSent[4] = true;
	}
}

//Reads all players currently playing's information, stats and position
void ReadServerData()
{
	data = client->ReadReceivedData();
	if(data == "0")
	{
	}
	else
	{
		std::string temp ="";
		i = 0;
		do
		{
			temp += data[i];
			i++;
		}while(data[i] != '|' && i < data.length());
		MAXIMUMPLAYERS = cgl::s2i(temp);				//MAX PLAYERS IS SET
		i++;											//Skip "|" character
		temp = "";
		do
		{
			temp += data[i];
			i++;
		}while(data[i] != '|' && i < data.length());
		SERVERNAME = temp;
		unit = new cgl::Unit[MAXIMUMPLAYERS];
		player = new cgl::Player[MAXIMUMPLAYERS];
		opengl->SetWindowTitle(GAMENAME + ", Playing at: " + SERVERNAME);
		for(int a = 0; a < MAXIMUMPLAYERS; a++)
		{
			player[a].ID = -1;
		}
		if(data.length() < i + 5)
		{
		}
		else
		{
			temp = "";
			i++;										//Skip "|" character
			int value = 0;
			int playernumber = 0;
			for(; i < data.length(); i++)
			{
				if(data[i] == '|')
				{
					//One player has been read fully
					temp = "";			//Prepare for next player
					value = 0;
					playernumber ++;
				}
				else
				{
					if(data[i] != '?')	//Still at same value to read
					{
						temp += data[i];
					}
					else				//New value to be read
					{
						switch(value)
						{
						case 0:
							player[playernumber].ID = playernumber;
							player[playernumber].playername = temp;
							temp = "";
							break;
						case 1:
							player[playernumber].kills = cgl::s2i(temp);
							temp = "";
							break;
						case 2:
							player[playernumber].deaths = cgl::s2i(temp);
							temp = "";
							break;
						case 3:
							x = cgl::c2f((char*)temp.c_str());
							break;
						case 4:
							y = cgl::c2f((char*)temp.c_str());
							temp = "";
							break;
						case 5:
							z = cgl::c2f((char*)temp.c_str());
							unit[playernumber].SetPosition(x,terrain->GetHeight(x,z),z);
							temp = "";
							break;
						default: 
							break;
						}
						value ++;
					}
				}
			}
		}
		SERVERRESPONSE = true;
		cgl::Image2D* unitTexture = new cgl::Image2D();
		unitTexture->LoadBMP("Data/snake.bmp");
		for(i = 0; i < MAXIMUMPLAYERS; i++)	//Setting all to default values
		{
			unit[i].armor = 0;
			unit[i].shield = 10;
			unit[i].mana = 10;
			unit[i].damage = 10;
			unit[i].action = 0;
			unit[i].hitpoints = 100;			//Loading the model 10 times... care ATM
			unit[i].scalingValue = 0.15;
			unit[i].flyheight = 0.0f;
			//unit[i].Load("Data/snake.md2", unitTexture->ID, 0.005f);
			unit[i].Load("Data/snake.md2", unitTexture->ID, 0.009f, MD2Normals);
		}
		delete unitTexture;
	}
}

//Reads data from server and takes action based on data received
void ReadData()
{
	data = client->ReadReceivedData();
	if(data == "" || data == "0" || data.length() < 2)					//Does nothing, nothing new happened that we need to know about
	{
	}
	else
	{
		i = 0;
		switch(data[0])
		{
		case '0':														//A new player joined, give information to us about him
			//GET PLAYER INDEX, PLAYERNUMBER
			i += 2;					//Skip '|'
			temp = "";
			do
			{
				temp += data[i];
				i++;
			}while(data[i] != '|' && i < data.length());
			playernumber = cgl::s2i(temp);
			player[playernumber].ID = playernumber;
			if(thisPlayer == -1)
			{
				thisPlayer = playernumber;								//It is you who joined!
			}
			//GET PLAYERNAME
			i++;					//Skip '|'
			temp = "";
			do
			{
				temp += data[i];
				i++;
			}while(data[i] != '|'  && i < data.length());
			player[playernumber].playername = temp;
			//GET PLAYER KILLS && DEATHS
			for(ii = 0; ii < 2; ii++)
			{
				i++;						//Skip '|'
				temp = "";
				do
				{
					temp += data[i];
					i++;
				}while(data[i] != '|' && i < data.length());
				if(ii == 0)
				{
					player[playernumber].kills = cgl::s2i(temp);
				}
				else
				{
					player[playernumber].deaths = cgl::s2i(temp);
				}
			}
			for(ii = 0; ii < 3; ii++)
			{
				i++;						//Skip '|'
				temp = "";
				do
				{
					temp += data[i];
					i++;
				}while(data[i] != '|' && i < data.length());
				switch(ii)
				{
				case 0:
					x = cgl::s2f(temp);
					break;
				case 1:
					y = cgl::s2f(temp);
					break;
				case 2:
					z = cgl::s2f(temp);
					unit[playernumber].SetPosition(x,y,z);
					break;
				default:
					break;
				}
			}
			break;
		case '1':
			//A unit has moved, for a player.
			temp = "";
			switch(data[1])						//Format: 1xPOSX|playernumber
			{
			case 'x':							//A player moved in X direction
				i = 2;
				x = GetFloatValue('|');
				i++;							//Skip '|'
				playernumber = GetIntValue('|');
				unit[playernumber].position.x = x;
				unit[playernumber].position.y = terrain->GetHeight(x, unit[playernumber].position.z);
				break;
			case 'y':
				i = 2;
				y = GetFloatValue('|');
				i++;							//Skip '|'
				playernumber = GetIntValue('|');
				unit[playernumber].flyheight = y;
				unit[playernumber].position.y = terrain->GetHeight(unit[playernumber].position.x, unit[playernumber].position.z) + unit[playernumber].flyheight;
				break;
			case 'z':
				i = 2;
				z = GetFloatValue('|');
				i++;							//Skip '|'
				playernumber = GetIntValue('|');
				unit[playernumber].position.z = z;
				unit[playernumber].position.y = terrain->GetHeight(unit[playernumber].position.x,z);
				break;
			default:
				break;
			}
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			i += 2;
			temp ="";
			do
			{
				temp += data[i];
				i++;
			}while(i < data.length());
			i = cgl::s2i(temp);
			player[i].ID = -1;
			player[i].playername = "<Empty Slot>";
			player[i].kills = 0;
			player[i].deaths = 0;
			break;
		default:
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
		std::cout << "Connecting with name: " << PLAYERNAME << std::endl;
	}
}

void DisconnectFromServer()
{
	client->SendData("5");			//Exit
	SDL_Delay(25);					//Give socket time to send "exit" to server
}

int GetIntValue(char end)
{
	temp = "";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	return cgl::s2i(temp);
}

int GetFloatValue(char end)
{
	temp = "";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	return cgl::s2f(temp);
}

std::string GetStringValue(char end)
{
	temp = "";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	return temp;
}