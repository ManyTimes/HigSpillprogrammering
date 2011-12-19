#include "../Header/network.h"

void ReadData();
void ReadServerData();
void CoutVec(cgl::Vector3f vec)
{
	std::cout << " Vector: " << vec.x << " ," << vec.y << " " << vec.z << std::endl;
}

void CoutVec(cgl::Vector3f vec, std::string msg)
{
	std::cout << msg;
	CoutVec(vec);
}

std::string data = "";
cgl::Vector3f tempvec;
cgl::Vector3f tempvec2;
std::string temp = "";
int playernumber = 0;
int i = 0;
int ii = 0;
int cc = 0;
float x,y,z;
bool hasSent[6];
float yaw;

//Called each game-loop sequence
void Network()
{
	tempvec = 0.0f;
	tempvec2  = 0.01f;
	for(i = 0 ; i < 6; i++)
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
	if(ISCONNECTED == false)
	{
		return;
	}
	if(!THIRDPERSONCAMERA)
		simpleCamera[thisPlayer].MoveForward(0.25);
	else
	{
		unit[thisPlayer].AddPosition((unit[thisPlayer].GetMatrix()->GetForwardVector())*-1);//*-MOVEMENT_SPEED);
		simpleCamera[thisPlayer].position = unit[thisPlayer].GetPosition();
	}
	if(hasSent[0] == false)				//Even if events, click action fires multiple times, we send only once per game-loop-sequence
	{
		//Send pos XZ to server
		if(!THIRDPERSONCAMERA)
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.x) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.z));
		else 
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(unit[thisPlayer].position.x) + "|" + cgl::f2s(unit[thisPlayer].position.z));
		//client->SendData("1W" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].GetYaw()));
		hasSent[0] = true;
	}
}

void SendDataBackward()
{
	if(ISCONNECTED == false)
	{
		return;
	}
	if(!THIRDPERSONCAMERA)
		simpleCamera[thisPlayer].MoveBackwards(0.25);
	else
	{
		unit[thisPlayer].AddPosition((unit[thisPlayer].GetMatrix()->GetForwardVector()));//*-MOVEMENT_SPEED);
		simpleCamera[thisPlayer].position = unit[thisPlayer].GetPosition();
	}
	if(hasSent[1] == false)
	{	
		if(!THIRDPERSONCAMERA)
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.x) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.z));
		else 
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(unit[thisPlayer].position.x) + "|" + cgl::f2s(unit[thisPlayer].position.z));
	//client->SendData("1S" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].GetYaw()));
		hasSent[1] = true;
	}
}

void SendDataLeft()
{
	if(ISCONNECTED == false)
	{
		return;
	}
	if(!THIRDPERSONCAMERA)
		simpleCamera[thisPlayer].MoveStrafeLeft(0.25);
	else 
	{
		unit[thisPlayer].AddPosition((unit[thisPlayer].GetMatrix()->GetRightVector())*-1);//*-MOVEMENT_SPEED);
		simpleCamera[thisPlayer].position = unit[thisPlayer].GetPosition();
	}
	if(hasSent[2] == false)	
	{
		if(!THIRDPERSONCAMERA)
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.x) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.z));
		else 
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(unit[thisPlayer].position.x) + "|" + cgl::f2s(unit[thisPlayer].position.z));
		//client->SendData("1A" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].GetYaw()));		//Moving X negative Player
		hasSent[2] = true;
	}
}

void SendDataRight()
{
	if(ISCONNECTED == false)
	{
		return;
	}
	if(!THIRDPERSONCAMERA)
		simpleCamera[thisPlayer].MoveStrafeRight(0.25);
	else 
	{
		unit[thisPlayer].AddPosition((unit[thisPlayer].GetMatrix()->GetRightVector()));//*-MOVEMENT_SPEED);
		simpleCamera[thisPlayer].position = unit[thisPlayer].GetPosition();
	}
	if(hasSent[3] == false)	
	{
		if(!THIRDPERSONCAMERA)
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.x) + "|" + cgl::f2s(simpleCamera[thisPlayer].position.z));
		else 
			client->SendData("1" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(unit[thisPlayer].position.x) + "|" + cgl::f2s(unit[thisPlayer].position.z));
		//client->SendData("1D" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].GetYaw()));
		hasSent[3] = true;
	}
}

void SendDataShoot(int type)
{
	if(ISCONNECTED == false)
	{
		return;
	}
	if(hasSent[4] == false)	
	{
		//projectileBanana[playernumber].Shoot(simpleCamera[playernumber].position, simpleCamera[playernumber].GetViewDirection(), 500);
		temp = "";
		if(!THIRDPERSONCAMERA)
			tempvec = simpleCamera[thisPlayer].GetViewDirection();
		else tempvec = camera->GetTPMatrix()->GetForwardVector()*-1;
		if(type == 0)
		{
			temp = "2b" + cgl::i2s(thisPlayer) + "|" +
				cgl::f2s(simpleCamera[thisPlayer].position.x) + "|" +
				cgl::f2s(simpleCamera[thisPlayer].position.y) + "|" +
				cgl::f2s(simpleCamera[thisPlayer].position.z) + "|" +
				cgl::f2s(tempvec.x) + "|" +
				cgl::f2s(tempvec.y) + "|" +
				cgl::f2s(tempvec.z);
			client->SendData(temp);
		}else if (type == 1)
		{
			cgl::Vector3f position;
			if(THIRDPERSONCAMERA)
				position = unit[thisPlayer].GetPosition();
			else position = simpleCamera[thisPlayer].position;

			tempvec *= 0.01;

			temp = "2c" + cgl::i2s(thisPlayer) + "|" +
				cgl::f2s(position.x) + "|" +
				cgl::f2s(position.y) + "|" +
				cgl::f2s(position.z) + "|" +
				cgl::f2s(tempvec.x) + "|" +
				cgl::f2s(tempvec.y) + "|" +
				cgl::f2s(tempvec.z) + "|" + 
				cgl::i2s(0); // arc
			client->SendData(temp);
		}
		//client->SendData("2b" + cgl::i2s(thisPlayer) + "|" + cgl::f2s(simpleCamera[thisPlayer].GetYaw()));
		hasSent[4] = true;
		temp = "";
	}
}

void SendHasLeftTheGame()
{
	if(ISCONNECTED == false)
	{
		return;
	}
	if(hasSent[5] == false)
	{
		ISCONNECTED = false;
		client->Exit();			//Sends exit message to server
		hasSent[5] = true;
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
		simpleCamera = new cgl::SimpleCamera[MAXIMUMPLAYERS];
		projectileBanana = new cgl::ProjectileBullet[MAXIMUMPLAYERS];
		projectileArc = new cgl::ProjectileArc[MAXIMUMPLAYERS];
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
			i++;										//Skip "|" character after servername
			int value = 0;
			int playernumber = 0;
			std::cout << " DATA GOTTEN: " << data << std::endl << std::endl;
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
					else				//Char read is '?', value read fully, store and reset
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
							temp = "";
							break;
						case 4:
							y = cgl::c2f((char*)temp.c_str());
							temp = "";
							break;
						case 5:
							z = cgl::c2f((char*)temp.c_str());
							unit[playernumber].SetPosition(x,y,z);
							simpleCamera->position = unit[playernumber].position;
							//simpleCamera->position.Cout();
							temp = "";
							break;
						default: 
							break;
						}
						value ++;			//each value, increase by '?'
					}
				}
			}
		}
		SERVERRESPONSE = true;
		cgl::Image2D* unitTexture = new cgl::Image2D();
		unitTexture->LoadBMP("Data/snake.bmp");
		for(i = 0; i < MAXIMUMPLAYERS; i++)	//Setting all to default values
		{
			projectileBanana[i].size = 0.005f;
			projectileBanana[i].speed = 5.0f;
			projectileBanana[i].SetModel(bananaModel);
			simpleCamera[i].Initialize(keyboard, mouse, SCREENWIDTH, SCREENHEIGHT);
			simpleCamera->Initialize(0.5, 0.5);
			simpleCamera->AllowMovement = false;	//Disable built in "WASD" movement
			unit[i].armor = 0;
			unit[i].shield = 10;
			unit[i].mana = 10;
			unit[i].damage = 10;
			unit[i].action = 0;
			unit[i].hitpoints = 100;			//Loading the model 10 times... care ATM
			unit[i].scalingValue = 2.;
			unit[i].flyheight = 0.55f;
			//unit[i].Load("Data/snake.md2", unitTexture->ID, 0.005f);
			unit[i].Load("Data/snake.md2", unitTexture->ID, 0.009f, MD2Normals);
			unit[i].scalingValue = 0.25f;
			unit[i].SetAngleOffsets(-90, 90, 0);	// The model isn't loaded with head facing forward. So fixing that with an angle offset

			projectileArc[i].SetModel(headModel);
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
				camera->SetThirdPersonTarget(&unit[thisPlayer]);
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
					simpleCamera[playernumber].position = unit[playernumber].position;
					break;
				default:
					break;
				}
			}
			break;
		case '1':								//A player has moved, we have recieved his positionvector

			i = 1;
			playernumber = GetIntValue('|');
			i++;
			x = GetFloatValue('|');
			i++;
			z = GetFloatValue('|');
			if(thisPlayer != playernumber)
			{
				simpleCamera[playernumber].position.x = x;
				simpleCamera[playernumber].position.z = z;	
			}
			//unit[playernumber].position = simpleCamera[playernumber].position;
			if(!THIRDPERSONCAMERA) // Is already updated if we have a thirdperson camera active.
				unit[playernumber].SetPosition(simpleCamera[playernumber].position);



			//i = 1;
			//std::cout << "DATA GOTTEN FROM SERVER: " << data << std::endl << std::endl;
			//playernumber = GetIntValue('|');
			//i++;								//Skip '|' character
			//x = GetFloatValue('|');				//Reading X position
			//i++;								//Skip '|'
			//z = GetFloatValue('|');				//Reading Z pos
			//unit[playernumber].position.x = x;
			//unit[playernumber].position.z = z;	

			//Y is read upon drawing, to add 2
			//unit[playernumber].position.y = terrain->GetHeight(unit[playernumber].position.x, unit[playernumber].position.z);
			//simpleCamera[playernumber].position = unit[playernumber].position;
			//i = 2;								//Playernumber starts from 2
			//playernumber = GetIntValue('|');
			//i++;								//Skip char '|'
			//yaw = GetFloatValue('|');			//Yaw of the player
			//if(playernumber == thisPlayer)
			//{
			//	simpleCamera[playernumber].SetYaw(yaw);
			//}
			//if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
			//{
			//	switch(data[1])
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
			//	unit[playernumber].position.y = 5 + terrain->GetHeight(unit[playernumber].position.x, unit[playernumber].position.z);
			//	std::cout << std::endl << " POSITION FRO PLAYER: " << playernumber << " is : ";
			//	unit[playernumber].position.Cout();
			//	//std::cout << " UnitNETW: ";
			//	//unit[playernumber].position.Cout();
			//	//std::cout << " CAmitNETW: ";
			//	//simpleCamera[playernumber].position.Cout();
			//}
			break;
		case '2':
			//A player has done some action (shooting/ability...)
			switch(data[1])
			{
			case 'b':					//Shooting Banana
				i = 2;
				playernumber = GetIntValue('|');
				i++;
				if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
				{
					tempvec.x = GetFloatValue('|');
					i++;
					tempvec.y = GetFloatValue('|');
					i++;
					tempvec.z =	GetFloatValue('|');
					i++;
					//View Direction
					tempvec2.x = GetFloatValue('|');
					i++;
					tempvec2.y = GetFloatValue('|');
					i++;
					tempvec2.z = GetFloatValue('|');
					projectileBanana[playernumber].Shoot(tempvec, tempvec2, 500);
					//projectileBanana[playernumber].position =tempvec;
				}
	/*			i = 2;
				playernumber = GetIntValue('|');
				if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
				{
					projectileBanana[playernumber].Shoot(simpleCamera[playernumber].position, simpleCamera[playernumber].GetViewDirection(), 500);
					std::cout << "Player shooting: " << playernumber;
					projectileBanana[playernumber].position.Cout();
				}*/
				break;
			case 'c':				// Shooting stormtrooper head
				i = 2;
				playernumber = GetIntValue('|');
				i++;
				if(playernumber > -1 && playernumber < MAXIMUMPLAYERS)
				{
					tempvec.x = GetFloatValue('|');
					i++;
					tempvec.y = GetFloatValue('|');
					i++;
					tempvec.z =	GetFloatValue('|');
					i++;
					//View Direction
					tempvec2.x = GetFloatValue('|');
					i++;
					tempvec2.y = GetFloatValue('|');
					i++;
					tempvec2.z = GetFloatValue('|');
					i++;
					projectileArc[playernumber].Initialize(tempvec, tempvec2, (cgl::projectileType)GetIntValue('|'));
					//projectileBanana[playernumber].position =tempvec;
				}
			default:
				break;
			}
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			i = 1;
			playernumber = GetIntValue('|');
			player[playernumber].ID = -1;
			player[playernumber].playername = "<Empty Slot>";
			player[playernumber].kills = 0;
			player[playernumber].deaths = 0;
			std::cout << "Player nr has left: " << playernumber << std::endl;
			break;
		default:
			break;
		}
	}
}

void ConnectToServer()
{
	if(client->Connect(5000) == false)
	{
		ISCONNECTED = false;
		messageFeedback = "Could not connect to server. Server might be down, try again later";
	}
	else
	{
		ISCONNECTED = true;
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

//OLD way of disconnecting, now, there's a callback in the server class for leaving players
//Simply send client->Exit();
void DisconnectFromServer()
{
	//client->SendData("5");			//Exit
	//SDL_Delay(25);					//Give socket time to send "exit" to server
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

float GetFloatValue(char end)
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


void GetVector3fValue(char end)
{
	temp = "";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	tempvec.x = cgl::s2f(temp);
	i++;							//Skip 'end' character
	temp ="";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	tempvec.y = cgl::s2f(temp);
	i++;							//Skip 'end' character
	temp = "";
	do
	{
		temp += data[i];
		i++;
	}while(data[i] != end && i < data.length());
	tempvec.z = cgl::s2f(temp);
}