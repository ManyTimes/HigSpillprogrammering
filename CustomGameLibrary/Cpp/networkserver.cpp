#include "../Header/networkserver.h"

namespace cgl
{
	NetworkServer::NetworkServer(int portnumber, int maximumClients)
	{
		this->length = 0;
		this->SERVERISFULL = "FULL";
		this->SERVERNOTFULL = "OK";
		this->MAXCLIENTS = maximumClients;
		this->clientcount = 0;
		this->portnumber = portnumber;
		this->clientsocket = new TCPsocket[this->MAXCLIENTS];
		this->isSocketFree = new bool[this->MAXCLIENTS];
		if(SDLNet_Init() == -1)
		{
			cgl::Error("Could not INIT");
		}
		this->sockets = SDLNet_AllocSocketSet(this->MAXCLIENTS);
		if(!this->sockets)
		{
			cgl::Error("Allocate Sockets");
		}
		for(int i = 0; i < this->MAXCLIENTS; i++)
		{
			this->clientsocket[i] = NULL;
			this->isSocketFree[i] = true;
		}
		int hostresolved = SDLNet_ResolveHost(&this->serverIP, NULL, this->portnumber);
		if(hostresolved == -1)
		{
			cgl::Error("Resolved host");
		}
		else
		{
			cgl::CoutIP((Uint8*)&this->serverIP.host);
		}
		this->serversocket = SDLNet_TCP_Open(&this->serverIP);		//ServerIP is 0.0.0.0, hm, localhost?
		if(!this->serversocket)
		{
			cgl::Error("Server socket closed");
		}
		else
		{
			cgl::Cout("Success established a server socket");
		}
		SDLNet_TCP_AddSocket(this->sockets, this->serversocket);
	}

	//Returns 0 if no activity, returns more than 0 if serversocket got activity (incoming clients)
	int NetworkServer::IsClientIncoming()
	{
		return SDLNet_SocketReady(this->serversocket);
	}

	//Returns 0 if client could not be added (max clients reached...)
	//Else returns 1 and client has been added and a socket created
	int NetworkServer::CreateClient()
	{
		if(this->clientcount < this->MAXCLIENTS)
		{
			int freeslot = -1;
			for(int i = 0; i < this->MAXCLIENTS; i++)
			{
				if(this->isSocketFree[i] == true)
				{
					this->isSocketFree[i] = false;
					freeslot = i;
					break;
				}
			}
			this->clientsocket[freeslot] = SDLNet_TCP_Accept(this->serversocket);
			SDLNet_TCP_AddSocket(this->sockets, this->clientsocket[freeslot]);
			this->clientcount++;
			
			strcpy(this->buffer, this->SERVERNOTFULL.c_str());
			this->length = strlen(this->buffer) + 1;
			SDLNet_TCP_Send(this->clientsocket[freeslot], (void*)this->buffer, this->length);
			cgl::Cout("Client added " + freeslot);
			return 1;
		}
		else
		{
			TCPsocket tempsocket = SDLNet_TCP_Accept(this->serversocket);
			strcpy(this->buffer, this->SERVERISFULL.c_str());
			this->length = strlen(this->buffer) + 1;
			SDLNet_TCP_Send(tempsocket, (void*) this->buffer, this->length);
			SDLNet_TCP_Close(tempsocket);
			cgl::Cout("Maximum clients reached on the server");
		}
		return 0;
	}

	//Closes the connection and emptys the socket of client number N
	void NetworkServer::CloseClient(int clientnumber)
	{
		SDLNet_TCP_DelSocket(this->sockets, this->clientsocket[clientnumber]);
		SDLNet_TCP_Close(this->clientsocket[clientnumber]);
		this->clientsocket[clientnumber] = NULL;
		this->isSocketFree[clientnumber] = true;
		this->clientcount = this->clientcount - 1;
	}

	//Reads data sent from client N, stores data in the buffer (member variable)
	//Returns -1 on inactive client, 0 on disconnected client, 1 on success
	int NetworkServer::ReadReceivedData(int clientnumber)
	{
		this->clientactivity = SDLNet_SocketReady(this->clientsocket[clientnumber]);		//Client is active (sends data to server)
		if(clientactivity != 0)
		{
			this->receivedbytes = SDLNet_TCP_Recv(this->clientsocket[clientnumber], this->buffer, BUFFERSIZE);
			if(this->receivedbytes <= 0)
			{
				if(DEBUG == true)
				{
					std::string temp = "Client number " + clientnumber;
					temp = temp + " is removed";
					cgl::Cout(temp);
				}
				this->CloseClient(clientnumber);										//Deletes and frees the socket
				return 0;																//Client disconnected
			}
			return 1;
		}
		return -1;
	}

	//Sends data stored in the buffer to client N
	//Returns 1 on success, 0 on no data to send/error
	int NetworkServer::SendReceivedData(int toClientNumber, int fromClientNumber)
	{
		this->length = strlen(this->buffer)+1;
		if(this->length > 1 && toClientNumber != fromClientNumber && this->isSocketFree[toClientNumber] == false)
		{
			SDLNet_TCP_Send(this->clientsocket[toClientNumber], (void*)this->buffer, this->length);
		}
		else
		{
			return 0;
		}
		return 1;
	}

	//Returns 1 on success, 0 on error. Sends data to a connected client through his socket
	int NetworkServer::SendData(int clientnumber, char data[])
	{
		strcpy(this->buffer, data);
		this->length = strlen(this->buffer) + 1;
		if(this->length > 1 && this->isSocketFree[clientnumber] == false && this->clientsocket[clientnumber] != NULL)
		{
			if(SDLNet_TCP_Send(this->clientsocket[clientnumber], (void*)this->buffer, this->length) < this->length)
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		return 1;
	}

	//Clears all sockets and closes the server socket
	void NetworkServer::Exit()
	{
		SDLNet_FreeSocketSet(this->sockets);
		SDLNet_TCP_Close(this->serversocket);
		delete []isSocketFree;
		delete []clientsocket;
	}

	//Number of active sockets, active clients currently on the server
	int NetworkServer::GetNumberOfActiveSockets()
	{
		//Waiting time in MS, 0 means no wait, -1 means waiting time of 49 days.
		return SDLNet_CheckSockets(this->sockets, 0);
	}

}