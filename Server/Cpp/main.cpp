#include "../Header/main.h"


//Initializes every thing into memory that needs to be loaded into memory
//Server settings, background picture...
void Initialize()
{
	ReadConfigurationFile();
}

//Server start
using namespace cgl;
int main(int argc, char *argv[])
{
	Initialize();

	//Create connection to db
	cgl::SqlConnection* sqlcon = new SqlConnection("bergpc\\sqlexpress", "Temp", "Oyvind", "123",10);				//Creates a connection and stores it in this object.
	//Creates a command object that can execute queries towards db
	cgl::SqlCommand* cmd = new SqlCommand(sqlcon);

	//Create a simple query
	std::string q = "SELECT ID, carname FROM [Car] WHERE ID < 100";
	std::string columns[] = { "ID", "carname" };
	int columnsLength = cgl::GetArrayLength(columns);
	cgl::Cout("Exeuctiny query");
	cmd->Execute(q, columns, columnsLength);
	for(int i = 0; i < cmd->totalRows; i++)
	{
		for(int ii = 0; ii < cmd->columnsLength; ii++)
		{
			std::cout << cmd->result->GetValue(i,ii) << " ";
		}
		std::cout << std::endl;
	}

	NetworkServer* net = new NetworkServer(9999,MAXIMUMPLAYERS);	//Create listener on port number
	Cout("Server is now listening on port " + net->portnumber);

	//MAIN PROGRAM
	char msg[BUFFERSIZE];
	do
	{
		std::cout << "Currently " << net->GetNumberOfActiveSockets() << " on our server" << std::endl;
		if(net->IsClientIncoming() != 0)			//A client is incoming
		{
			net->CreateClient();					//Adds a new client upon incoming client
													//Returns 0 on not successfully created client
		}

		for(int i = 0; i < net->clientcount; i++)	//Loop through all connected clients
		{
			if(net->ReadReceivedData(i) == 1)		//If we got data from client N, store it in buffer
			{
				//do whatever we want with buffer (net->buffer), but as this is a "send text chat server-client"
				//we send the buffer data back to all active sockets, simply by calling the below function
				for(int ii = 0; ii < MAXIMUMPLAYERS; ii++)//Maxplayers because, some client might have disconnected
				{									//hence net->clientcount cannot be used, cause of a socket might be null
													//at the first player...
				//	net->SendReceivedData(ii, i);	//Sends data recieved from one client, to all others
													//First parameter; all players, second is the author of the message, 
													//just display the authors msg at his own screen, no need to get it back from server
					net->SendData(ii, "Hello world");//Send a single data to a fixed user (in this case all users connected...)	
													//But it can be just a single data to one user... Example:
												//user clicks "View stats", and sends "viewstats" to server, server goes through a 
												//switch statement (or so) and based on the input, it performs a function.. In this case
												//It will "view stats", so it will take client number, his playername, search playername
												//up in the database and return his stats.
												//When stats is returned at client, we will draw the stats on screen. simple? :)
												//Is this fast? Hm, no?
												//All playing players at a time, should keep the stats of all other players in memory
												//The database shall only be to view "total stats", or so, when "not playing",
											//as in "viewing a profile" in sc2...or such... :)
				}
			}
		}
		SDL_Delay(DELAY);
	}while(true);

	SDLNet_Quit();
	return(0);
}
