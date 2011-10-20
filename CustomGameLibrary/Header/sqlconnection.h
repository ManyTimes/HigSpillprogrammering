#ifndef _SQLCONNECTION_H
#define _SQLCONNECTION_H
#include "include.h"
#include <SQLAPI.h>			// main SQLAPI++ header
#include "function.h"


namespace cgl
{
	class DECLARE SqlConnection
	{
	private:
		SAConnection* con;
		//***********FUNCTIONS***********
		void SqlConnection::Initalize(std::string serv, std::string db, std::string user, std::string pwd, int timeout);
		void SqlConnection::Connect(std::string serv, std::string db, std::string user, std::string pwd);
	public:
		std::string server;
		std::string database;
		std::string username;
		std::string password;

		//***********CONSTRUCTOR***********
		SqlConnection::SqlConnection(std::string server, std::string database, std::string username, std::string password, int timeout);
		SqlConnection::SqlConnection(std::string server, std::string database, std::string username, std::string password);
		SqlConnection::~SqlConnection();
		//***********FUNCTIONS***********
		SAConnection* SqlConnection::GetSqlConnection();
		void SqlConnection::Open();
		void SqlConnection::Close();
		bool SqlConnection::isConnected();
	};
}
#endif
