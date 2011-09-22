#include "include.h"
#include "const.h"
#include "function.h"

namespace cgl
{
	class DECLARE NetworkClient
	{
		public:
			IPaddress serverIP;
			TCPsocket clientsocket;
			SDLNet_SocketSet sockets;
			std::string serveraddress;	//IP, localhost, or an address
			int portnumber;				//Port to connect on
			const char *host;			//Holds the host name
			char buffer[BUFFERSIZE];
			bool shutdown;

			//Costructor
			NetworkClient::NetworkClient(std::string serveraddress, int portnumber);

			//Functions
	};

}