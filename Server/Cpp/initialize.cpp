#include "../Header/initialize.h"

using namespace std;
using namespace cgl;

//Reads the whole ConfigurationServer.txt file and stores read values within global variables
void ReadConfigurationFile()
{
	ifstream configfile;
	configfile.open("ConfigurationServer.txt");
	string readline;
	int linenumber = 0;
	while(!configfile.eof() && linenumber < 10)
	{
		getline(configfile,readline);
		if(linenumber == 2)
		{
			IPADRESS = ReturnConfigurationValue(readline);
		}
		if(linenumber == 3)
		{
			PORTNUMBER = ReturnConfigurationValue(readline);
		}
		if(linenumber == 4)
		{
			SERVERNAME = ReturnConfigurationValue(readline);
		}
		if(linenumber == 5)
		{
			MAXIMUMPLAYERS = cgl::s2i(ReturnConfigurationValue(readline));
		}
		linenumber ++;
	}
	configfile.close();
	configfile.clear();
}

//Returns the value from the "Value Column" within the ConfigurationServer.txt where a line was read
string ReturnConfigurationValue(string readline)
{
	string temp;
	for(int i = 0; i < readline.length(); i++)
	{
		if(i > 15)
		{
			temp += readline[i];
		}
	}
	return temp;
}
