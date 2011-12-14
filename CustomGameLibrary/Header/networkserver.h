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
		void (*CallbackOnClose)(int);
	public:
		void (NetworkServer::*callbackClose)(int clientNumber);                // C++
		void (NetworkServer::*callbackCloseConst)(int) const;     // C++
		int portnumber;
		char buffer[BUFFERSIZE];			//Holds received data, if any (requires a call to ReadReceivedData(int)
		TCPsocket serversocket;				//The incoming server socket
		TCPsocket* clientsocket;			//Array of client sockets
		bool* isSocketFree;
		int clientcount;					//Amount of connected clients at the moment

		//Constructor
		NetworkServer::NetworkServer(int portnumber, int maximumClients);
		//NetworkServer automatically sends back "OK" or "FULL" messages, these can be changed here by Initialize();
		void NetworkServer::Initialize(std::string MessageServerIsFullToJoinedClient, std::string MessageToJoinedClient);
		//Object functions
		int NetworkServer::GetNumberOfActiveSockets();
		int NetworkServer::IsClientIncoming();
		int NetworkServer::CreateClient();
		void NetworkServer::CloseClient(int clientnumber);
		void NetworkServer::CloseClient(TCPsocket* clientsocket);
		int NetworkServer::ReadReceivedData(int clientnumber);
		int NetworkServer::ReadReceivedData(TCPsocket* clientsocket);
		bool NetworkServer::SendReceivedData(int toClientNumber, int fromClientNumber);
		bool NetworkServer::SendData(int clientnumber, char data[]);
		bool NetworkServer::SendData(int clientNumber, const char* data);
		bool NetworkServer::SendData(int clientNumber, std::string data);
		bool NetworkServer::SendDataToConnectedClients(std::string data);
		void NetworkServer::Exit();
		void NetworkServer::CallbackOnClientClosed(void (*function)(int clientNumber));
	};
}