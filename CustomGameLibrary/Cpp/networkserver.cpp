#include "../Header/networkserver.h"

namespace cgl
{
	NetworkServer::NetworkServer(int portnumber, int maximumClients)
	{
		this->CallbackOnClose = NULL;
		this->callbackClose = NULL;
		this->callbackCloseConst = NULL;
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
			cgl::Cout("Could not Initiliaze SDLNet.");
		}
		this->sockets = SDLNet_AllocSocketSet(this->MAXCLIENTS);
		if(!this->sockets)
		{
			cgl::Cout("Allocate Sockets");
		}
		for(int i = 0; i < this->MAXCLIENTS; i++)
		{
			this->clientsocket[i] = NULL;
			this->isSocketFree[i] = true;
		}
		int hostresolved = SDLNet_ResolveHost(&this->serverIP, NULL, this->portnumber);
		if(hostresolved == -1)
		{
			cgl::Cout("Resolved host");
		}
		else
		{
			cgl::CoutIP((Uint8*)&this->serverIP.host);
		}
		this->serversocket = SDLNet_TCP_Open(&this->serverIP);		//ServerIP is 0.0.0.0, hm, localhost?
		if(CGL_DEBUG_MODE == true)
		if(!this->serversocket)
		{
			cgl::Cout("Server socket closed");
		}
		else
		{
			if(CGL_DEBUG_MODE == true)
			{
				cgl::Cout("Success established a server socket");
			}
		}
		SDLNet_TCP_AddSocket(this->sockets, this->serversocket);
	}


	void NetworkServer::Initialize(std::string MessageServerIsFullToJoinedClient, std::string MessageToJoinedClient)
	{
		this->SERVERISFULL = MessageServerIsFullToJoinedClient;
		this->SERVERNOTFULL = MessageToJoinedClient;
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
			cgl::Cout("Client Added in slot : " + cgl::i2s(freeslot));
			return 1;
		}
		else
		{
			TCPsocket tempsocket = SDLNet_TCP_Accept(this->serversocket);
			strcpy(this->buffer, this->SERVERISFULL.c_str());
			this->length = strlen(this->buffer) + 1;
			SDLNet_TCP_Send(tempsocket, (void*) this->buffer, this->length);
			SDLNet_TCP_Close(tempsocket);
			if(CGL_DEBUG_MODE == true)
			{
				cgl::Cout("Maximum clients reached on the server");
			}
		}
		return 0;
	}

	//Closes the connection and emptys the socket of client number N
	void NetworkServer::CloseClient(int clientnumber)
	{
		cgl::Cout("Closing client " + cgl::i2s(clientnumber));
		SDLNet_TCP_DelSocket(this->sockets, this->clientsocket[clientnumber]);
		SDLNet_TCP_Close(this->clientsocket[clientnumber]);
		this->clientsocket[clientnumber] = NULL;
		this->isSocketFree[clientnumber] = true;
		this->clientcount = this->clientcount - 1;
		if(this->CallbackOnClose != NULL)
		{
			this->CallbackOnClose(clientnumber);
		}
	}

	void NetworkServer::CloseClient(TCPsocket* clientsocket)
	{
		int clientnumber = -1;
		for(int i = 0; i < this->MAXCLIENTS; i++)
		{
			if(this->clientsocket[i] == (TCPsocket&)clientsocket)
			{
				clientnumber = i;
				i = this->MAXCLIENTS;
			}
		}
		cgl::Cout("Closing client " + cgl::i2s(clientnumber));
		if(clientnumber > -1)
		{
			SDLNet_TCP_DelSocket(this->sockets, this->clientsocket[clientnumber]);
			SDLNet_TCP_Close(this->clientsocket[clientnumber]);
			this->clientsocket[clientnumber] = NULL;
			this->isSocketFree[clientnumber] = true;
			this->clientcount = this->clientcount - 1;
			if(this->CallbackOnClose != NULL)
			{
				this->CallbackOnClose(clientnumber);
			}
		}
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
				if(CGL_DEBUG_MODE == true)
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

	//Reads Received data from socket into buffer. Returns -1 if no data is read, returns 0 if clientsocket is closing, else returns 1
	int NetworkServer::ReadReceivedData(TCPsocket* clientsocket)
	{
		this->clientactivity = SDLNet_SocketReady(clientsocket);
		if(clientactivity != 0)
		{
			this->receivedbytes = SDLNet_TCP_Recv((TCPsocket&)clientsocket, this->buffer, BUFFERSIZE);
			if(this->receivedbytes <= 0)
			{
				if(CGL_DEBUG_MODE == true)
				{
					cgl::Cout("Client is removed");
				}
				this->CloseClient(clientsocket);									//Deletes and frees the socket
				return 0;																//Client disconnected
			}
			return 1;
		}
		return -1;
	}

	//Sends data stored in the buffer to client N
	//Returns 1 on success, 0 on no data to send/error, usually chat messages can be received and sent right to clients
	bool NetworkServer::SendReceivedData(int toClientNumber, int fromClientNumber)
	{
		this->length = strlen(this->buffer)+1;
		if(this->length > 1 && toClientNumber != fromClientNumber && this->isSocketFree[toClientNumber] == false)
		{
			SDLNet_TCP_Send(this->clientsocket[toClientNumber], (void*)this->buffer, this->length);
		}
		else
		{
			return false;
		}
		return true;
	}

	//Returns 1 on success, 0 on error. Sends data to a connected client through his socket
	bool NetworkServer::SendData(int clientNumber, char data[])
	{
		strcpy(this->buffer, data);						//Why do I copy data to buffer, when they are of the same type, above me... :)
		this->length = strlen(this->buffer) + 1;
		if(this->length > 1 && this->isSocketFree[clientNumber] == false && this->clientsocket[clientNumber] != NULL)//Data not too short and socket is in use
		{
			if(SDLNet_TCP_Send(this->clientsocket[clientNumber], (void*)this->buffer, this->length) < this->length)	//Length of data sent, less than length of data
			{																										//Something failed, send 0
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	bool NetworkServer::SendData(int clientNumber, std::string data)
	{
		return this->SendData(clientNumber, data.c_str());
	}

	//Returns true on success, 0 if error happened
	bool NetworkServer::SendData(int clientNumber, const char* data)
	{
		strcpy(this->buffer, data);
		this->length = strlen(this->buffer) +1;
		if(this->length > 1 && this->isSocketFree[clientNumber] == false && this->clientsocket[clientNumber] != NULL)
		{
			if(SDLNet_TCP_Send(this->clientsocket[clientNumber], (void*)this->buffer, this->length) < this->length)
			{
				return false;
			}
		}
		else
		{	
			return false;
		}
		return true;
	}

	bool NetworkServer::SendDataToConnectedClients(std::string data)
	{
		for(int i = 0; i < this->clientcount; i++)
		{
			this->SendData(i, data.c_str());
		}
		return true;
	}

	//Clears all sockets and closes the server socket
	void NetworkServer::Exit()
	{
		for(int i = 0; i < this->MAXCLIENTS; i++)	
		{											
			this->SendData(i, "exit");					//Informing clients that we are shutting down the server
		}
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

	void NetworkServer::CallbackOnClientClosed(void (*function)(int clientNumber))
	{
		this->CallbackOnClose = function;
	}


}