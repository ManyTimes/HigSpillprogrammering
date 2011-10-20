#include "../Header/sqlconnection.h"


namespace cgl
{
	//***********PRIVATE FUNCTIONS***********
	void SqlConnection::Initalize(std::string serv, std::string db, std::string user, std::string pwd, int timeout)
	{
		try
		{
			this->con = new SAConnection();
			con->setOption("DBPROP_INIT_TIMEOUT") = cgl::i2s(timeout).c_str();
			if(serv.length() < 2 || db.length() < 2)
			{
				cgl::Error("Cannot initialize SQL connection, too short db/server name");
			}
			else
			{
				this->Connect(serv, db, user, pwd);
			}
		}
		catch(SAException &e)
		{
			cgl::Error((std::string)e.ErrText());
		}
		this->server = serv;
		this->database = db;
		this->username = user;
		this->password = pwd;
	}

	void SqlConnection::Connect(std::string serv, std::string db, std::string user, std::string pwd)
	{
		std::string temp = serv + "@" + db;
		try
		{
			con->Connect(temp.c_str(), user.c_str(), pwd.c_str(), SA_SQLServer_Client);
		}
		catch(SAException &e)
		{
			try
			{
				con->Rollback();
			}
			catch(SAException &)
			{
			}
			cgl::Error((std::string)e.ErrText());
		}
	}

	//***********CONSTRUCTOR***********
	SqlConnection::SqlConnection(std::string server, std::string database, std::string username, std::string password, int timeout)
	{
		this->Initalize(server, database, username, password, timeout);
	}
	SqlConnection::SqlConnection(std::string server, std::string database, std::string username, std::string password)
	{
		this->Initalize(server, database, username, password, 0);
	}

	SqlConnection::~SqlConnection()
	{
		delete [] this->con;
	}
	
	//***********FUNCTIONS***********
	//Returns the SqlConnection object
	SAConnection* SqlConnection::GetSqlConnection()
	{
		return this->con;
	}

	void SqlConnection::Open()
	{
		this->Connect(this->server, this->database, this->username, this->password);
	}
	void SqlConnection::Close()
	{
		this->con->Disconnect();
	}

	bool SqlConnection::isConnected()
	{
		return this->con->isConnected();
	}
}


