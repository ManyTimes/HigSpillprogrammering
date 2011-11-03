#include "../Header/sqlcommand.h"

namespace cgl
{
	SqlCommand::SqlCommand(SqlConnection* sqlcon)
	{
		this->con = sqlcon->GetSqlConnection();
	}

	//***********FUNCTIONS***********
	//Runs query against the database
	//Query returns nothing. Preferably either a update, create, delete or drop query.
	void SqlCommand::Execute(std::string query)
	{
		this->query = query;
		try
		{
			SACommand cmd(this->con, query.c_str());
			cmd.setConnection(this->con);
			cmd.setCommandText(query.c_str());
			cmd.Execute();
			cmd.Close();
			cmd.Destroy();
		}
		catch(SAException &e)
		{
			cgl::Error((std::string)e.ErrText());
		}
	}

	//Runs query against the database
	//Result is stored within the member "result", if any result exists
	void SqlCommand::Execute(std::string query, std::string selectColumns[], int lengthOfColumns)
	{
		this->query = query;
		this->columnsLength = lengthOfColumns;
		this->result = new SqlResult(selectColumns, this->columnsLength);
		this->result->totalRows = 0;
		this->totalRows = 0;
		int maxrows = 0;
		try
		{
			SACommand cmd(this->con, query.c_str());						//Creating the query
			cmd.Execute();													//Executes it
			while(cmd.FetchNext())											//Loops through each row in the result of the query, one by one
			{
				if(maxrows > 1 && maxrows % 10 == 0)
				{
					this->result->AllocateMoreMemory();
				}
				for(int i = 0 ; i < this->columnsLength; i++)
				{
					std::string temp((const char*)cmd.Field(selectColumns[i].c_str()).asString());
					this->result->row[maxrows].column[i] = temp;
				}
				maxrows = maxrows+1;
			}
			this->result->totalRows = maxrows;
			this->totalRows = maxrows;
			cmd.Close();
			cmd.Destroy();
		}
		catch(SAException &e)
		{
			cgl::Error((std::string)e.ErrText());
		}
	}

	void SqlCommand::SetConnection(SqlConnection* sqlcon)
	{
		this->con = sqlcon->GetSqlConnection();
	}

	//Remove result set and the query form the memory
	void SqlCommand::ClearResult()
	{
		delete [] this->result;
	//	delete this->result;
	}
}