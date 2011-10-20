#include "include.h"
#include "const.h"
#include "function.h"

namespace cgl
{
	class DECLARE NetworkClient
	{
		private:
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
			NetworkClient::NetworkClient(std::string serveraddress, int portnumber);

			//Functions
			int NetworkClient::SendData(std::string data);
			std::string NetworkClient::ReadRecievedData();
			void NetworkClient::Exit();
	};

}