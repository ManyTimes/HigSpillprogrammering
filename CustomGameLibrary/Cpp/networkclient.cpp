#include "../Header/networkclient.h"

namespace cgl
{
	//Servername examples: localhost, http://someaddress.com, 192.168.0.1
	NetworkClient::NetworkClient(std::string serveraddress, int portnumber)
	{
		this->shutdown = true;		//Always shutting down, except if we get "OK" from server
		if(SDLNet_Init()  < 0)
		{
			cgl::Cout("Failed to init SDL");
		}
		else
		{
			this->serveraddress = serveraddress;
			this->portnumber = portnumber;

			int hostresolved = SDLNet_ResolveHost(&this->serverIP, this->serveraddress.c_str(), this->portnumber);
			if(hostresolved == -1)
			{
				cgl::Cout("Could not resolve the servername");
			}
			else
			{
				Uint8* dotQuad = (Uint8*)&this->serverIP.host;
				std::cout << "Success resolving host to IP: " << 
					(unsigned short)dotQuad[0] << "." <<
					(unsigned short)dotQuad[1] << "." <<
					(unsigned short)dotQuad[2] << "." <<
					(unsigned short)dotQuad[3] << std::endl; 
			}
			if((host = SDLNet_ResolveIP(&this->serverIP)) == NULL)
			{
				cgl::Cout("Failed to resolve IP");
			}
			else
			{
				cgl::Cout("Successfully resolved IP", host);
			}
			this->messageOnSERVERISFULL = "FULL";
			this->messageOnSERVEROK = "OK";
			this->messageOnShutdown = "exit";
			this->clientsocket = NULL;
		}
	}

	//Returns a string response from the server if it could connect, else an error
	bool NetworkClient::Connect(int timeoutSeconds)
	{
		this->sockets = SDLNet_AllocSocketSet(1);
		if(this->sockets == NULL)
		{
			cgl::Cout("Failed to allocate sockets");
		}
		this->clientsocket = SDLNet_TCP_Open(&this->serverIP);
		if(!this->clientsocket)
		{
			cgl::Cout("Failed to establish a connection. Server might be down, IP and port combo is wrong or server is full");
			return false;
		}
		else
		{
			SDLNet_TCP_AddSocket(this->sockets, this->clientsocket);
			int activesockets = SDLNet_CheckSockets(this->sockets, timeoutSeconds);
			int response = SDLNet_SocketReady(this->clientsocket);
			if(response != 0)
			{
				int serverresponsebytecount = SDLNet_TCP_Recv(this->clientsocket, this->buffer, BUFFERSIZE);
				cgl::Cout("Message from server:", buffer);
				if(strcmp(buffer, this->messageOnSERVEROK.c_str()) == 0)
				{
					this->shutdown = false;						//We are connected, do not shutdown the socket connection
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				cgl::Cout("No response from server");
				return false;
			}
		}
	}

	//Set the messages that can come from the server upon different states: Shutdown, Full and Ok (client could join alright)
	void NetworkClient::Initialize(std::string messageOnShutdown, std::string messageOnSERVERISFULL, std::string messageOnSERVEROK)
	{
		this->messageOnShutdown = messageOnShutdown;
		this->messageOnSERVERISFULL = messageOnSERVERISFULL;
		this->messageOnSERVEROK = messageOnSERVEROK;
	}

	//Returns true if data was sent successfully, returns false otherwise
	bool NetworkClient::SendData(std::string data)
	{
		strcpy(this->buffer, data.c_str());
		int msglength = strlen(buffer) +1;
		if(SDLNet_TCP_Send(this->clientsocket, (void*)buffer, msglength) < msglength)
		{
			return false;				//Could not send message
		}
		return true;
	}	

	//Returns data Received from server if any, else returns "0"
	//Returns "exit" if server is shutting down.
	std::string NetworkClient::ReadReceivedData()
	{
		int socketactive = SDLNet_CheckSockets(this->sockets, 0);
		if(socketactive != 0)					//Current socket is alive
		{
			socketactive = SDLNet_SocketReady(this->clientsocket);
			if(socketactive != 0)				//Current socket got message from server?
			{
				//int responsebytes =
				SDLNet_TCP_Recv(this->clientsocket, buffer, BUFFERSIZE);
				if(strcmp(buffer, "exit") == 0)	//Message from server is exit, 0 difference, hardcoded in on both client and server
				{
					return this->messageOnShutdown;	//Sends "exit" as in return or a defined custom message, to check against
				}	
				return cgl::c2s(buffer);
			}
			return "0"; 
		}
		return "0";
	}

	//Reads Received data from server,if any, to this->buffer, returns true if new data has arrived, else false
	bool NetworkClient::ReadReceivedDataToBuffer()
	{
		int socketactive = SDLNet_CheckSockets(this->sockets, 0);
		if(socketactive != 0)					//Current socket is alive
		{
			socketactive = SDLNet_SocketReady(this->clientsocket);
			if(socketactive != 0)				//Current socket got message from server?
			{
				//int responsebytes =			//SDLNetTCPRecv returns response in bytes, int
				SDLNet_TCP_Recv(this->clientsocket, buffer, BUFFERSIZE);
				return true;
			}
		}
		return false;
	}


	//Call this when closing your application. This also sends a "exit" to the server, if connection to server is still up, freeing the slot at server.
	void NetworkClient::Exit()
	{
		if(this->sockets != NULL)
		{
			SDLNet_FreeSocketSet(this->sockets);
		}
		if(!this->clientsocket)
		{
		}
		else
		{
			SDLNet_TCP_Close(this->clientsocket);
		}
		this->shutdown = true;
		//delete []host;
		//delete []isSocketFree;
		//delete []clientsocket;
	}

}