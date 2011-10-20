#include "include.h"
#include "const.h"
#include "function.h"

namespace cgl
{
	class DECLARE NetworkServer
	{
	private:
		int MAXCLIENTS;
		std::string SERVERNOTFULL;
		std::string SERVERISFULL;
		int receivedbytes;
		int clientactivity;
		int length;
		IPaddress serverIP;
		SDLNet_SocketSet sockets;
	public:
		int portnumber;
		char buffer[BUFFERSIZE];			//Holds received data, if any (requires a call to ReadReceivedData(int)
		TCPsocket serversocket;				//The incoming server socket
		TCPsocket* clientsocket;			//Array of client sockets
		bool* isSocketFree;
		int clientcount;					//Amount of connected clients at the moment

		//Constructor
		NetworkServer::NetworkServer(int portnumber, int maximumClients);

		//Object functions
		int NetworkServer::GetNumberOfActiveSockets();
		int NetworkServer::IsClientIncoming();
		int NetworkServer::CreateClient();
		void NetworkServer::CloseClient(int clientnumber);
		int NetworkServer::ReadReceivedData(int clientnumber);
		int NetworkServer::SendReceivedData(int toClientNumber, int fromClientNumber);
		int NetworkServer::SendData(int clientnumber, char data[]);
		void NetworkServer::Exit();
	};
}