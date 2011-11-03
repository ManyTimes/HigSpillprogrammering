#include "include.h"
#include "const.h"
#include "function.h"

namespace cgl
{
	class DECLARE NetworkClient
	{
		private:
			std::string messageOnShutdown;
			std::string messageOnSERVERISFULL;		//Server says FULL to the client, maximum clients allowed on the server has been reached
			std::string messageOnSERVEROK;			//Server says OK to the client, lets establish a connection socket
			char buffer[BUFFERSIZE];
		public:
			IPaddress serverIP;
			TCPsocket clientsocket;
			SDLNet_SocketSet sockets;
			std::string serveraddress;	//IP, localhost, or an address
			int portnumber;				//Port to connect on
			const char *host;			//Holds the host name
			bool shutdown;

			//Costructor
			NetworkClient::NetworkClient(std::string serveraddress, int portnumber);	//Sets up IP and host and initialises network for TCP
			//Functions
			void NetworkClient::Initialize(std::string messageOnShutdown, std::string messageOnSERVERISFULL, std::string messageOnSERVEROK);//If server has set its custom messages, call this
			bool NetworkClient::Connect(int timeoutSeconds);			//Connect to the server, returns true if everything went ok, else false
			bool NetworkClient::SendData(std::string data);
			bool NetworkClient::ReadReceivedDataToBuffer(void);
			std::string NetworkClient::ReadReceivedData();
			void NetworkClient::Exit();
	};

}