#include "../Header/networkclient.h"

namespace cgl
{
	//Servername examples: localhost, http://someaddress.com, 192.168.0.1
	NetworkClient::NetworkClient(std::string serveraddress, int portnumber)
	{
		this->shutdown = true;		//Always shutting down, except if we get "OK" from server
		if(SDLNet_Init()  < 0)
		{
			cgl::Error("Failed to init SDL");
		}
		this->serveraddress = serveraddress;
		this->portnumber = portnumber;

		this->sockets = SDLNet_AllocSocketSet(1);
		if(this->sockets == NULL)
		{
			cgl::Error("Failed to allocate sockets");
		}
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
		this->clientsocket = SDLNet_TCP_Open(&this->serverIP);
		if(!this->clientsocket)
		{
			//Not reachable, wrong port, server is "full"
			cgl::Error("Failed to open a connection to the server, server might be down");
		}
		else
		{
			cgl::Cout("Connected to server");
			SDLNet_TCP_AddSocket(this->sockets, this->clientsocket);
			int activesockets = SDLNet_CheckSockets(this->sockets, 1000);
			cgl::Cout("There are currently" + activesockets, " sockets active ATM");
			int response = SDLNet_SocketReady(this->clientsocket);
			if(response != 0)
			{
				int serverresponsebytecount = SDLNet_TCP_Recv(this->clientsocket, this->buffer, BUFFERSIZE);

				cgl::Cout("Message from server:", buffer);
				if(strcmp(buffer, "OK") == 0)
				{
					this->shutdown = false;		//Connected with OK message
					cgl::Cout("Joined the server", this->host);
				}
				else
				{
					cgl::Cout("Server is full", this->host);
				}
			}
			else
			{
				cgl::Cout("No response");
			}
		}
	}
}