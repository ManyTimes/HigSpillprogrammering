#include "../Header/main.h"

void Initialize()
{
	InitConfigurationFromFile();
}

int main(int argc, char *argv[])
{
	Initialize();
	//Create connection to db
	cgl::SqlConnection* sqlcon = new cgl::SqlConnection("bergpc\\sqlexpress", "Temp", "Oyvind", "123",1);				//Creates a connection and stores it in this object.

	//Creates a command object that can execute queries towards db
	cgl::SqlCommand* cmd = new cgl::SqlCommand(sqlcon);

	//Create a simple query
	std::string q = "SELECT ID, carname FROM [Car] WHERE ID < 100";
	std::string columns[] = { "ID", "carname" };
	int columnsLength = cgl::GetArrayLength(columns);
	cgl::Cout("Exeuctiny query");
	cmd->Execute(q, columns, columnsLength);

	//Loop through the result, display it to command window
	for(int i = 0; i < cmd->totalRows; i++)
	{
		for(int ii = 0; ii < cmd->columnsLength; ii++)
		{
			std::cout << cmd->result->GetValue(i,ii) << " ";
		}
		std::cout << std::endl;
	} 
	return(0);
}
