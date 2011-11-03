#ifndef _SQLCOMMAND_H
#define _SQLCOMMAND_H
#include "sqlconnection.h"
#include "SQLAPI.h"
#include "sqlresult.h"

namespace cgl
{
	class DECLARE SqlCommand		//Connect, Disconnect, Execute
	{
	private:
		SAConnection* con;
	public:
		int columnsLength;
		int totalRows;
		SqlResult* result;
		std::string query;
		//***********CONSTRUCTOR***********
		SqlCommand::SqlCommand(SqlConnection* sqlcon);

		//***********FUNCTIONS***********
		//Runs a non-select query against the database
		void SqlCommand::Execute(std::string query);
		//Runs select query against the database
		void SqlCommand::Execute(std::string query, std::string selectColumns[], int lengthOfColumns);
		void SqlCommand::SetConnection(SqlConnection* sqlcon);
		//Remove result set and the query form the memory
		void SqlCommand::ClearResult();
	};
}

#endif
