#include "../Header/function.h"

namespace cgl
{
	int GetArrayLength(int inputarray[])
	{
		std::cout << sizeof(inputarray) / sizeof(inputarray[0]) << std::endl;
		return 0;
	}

	int GetArrayLength(char inputarray[])
	{
		int length = 0;
		for(int i = 0; inputarray[i] != '\0'; i++)
		{
			length ++;
		}
		return length;
	}

	//string array can max be 1000
	int GetArrayLength(std::string inputarray[])
	{
		int length = 0;
		std::string temp;
		for(int i = 0; i < 1000; i++)
		{
			try
			{
				temp = inputarray[i];
				length++;
			}
			catch(std::exception &e)
			{
				i = 1000;
			}
		}
		return length;
	}

	//Print out an error message in the command window
	//Automatically calls SDLNet_GetError();
	void Error(std::string message)
	{
		if(DEBUG == true)						//Displays error only upon "DEBUG mode"
		{
			std::cout << message;
			std::cout << message << ": " << SDLNet_GetError() << std::endl;
		}										//Always exit
		exit(-1);
	}

	int s2i(std::string value)
	{
		int returnvalue = atoi(value.c_str());
		if(returnvalue > 10000000)				//10 millions
		{
			return 10000000;
		}
		if(returnvalue < -10000000)		
		{
			return -10000000;
		}
		if(returnvalue == NULL)
		{
			return 0;
		}
		return returnvalue;
	}

	std::string i2s(int value)
	{
		std::stringstream out;
		out << value;
		return out.str();
	}

	//Print a string message
	void Cout(std::string message)
	{
		 std::cout << message <<  std::endl;
	}

	//Print two string messages
	void Cout(std::string message, std::string message2)
	{
		 std::cout << message << " " << message2;
	}

	//Print out an IP address if debug mode is true
	void CoutIP(Uint8* IPaddress)
	{
		std::cout << "Success to host: " << (unsigned short)IPaddress[0] << "."
		<< (unsigned short)IPaddress[1] << "."
		<< (unsigned short)IPaddress[2] << "."
		<< (unsigned short)IPaddress[3];
	}

	//Return an IP address on the format: xxx.xxx.xxx.xxx
	std::string GetIP(Uint8* IPaddress)
	{
		std::string temp =(unsigned short)IPaddress[0] + ".";
		temp += (unsigned short)IPaddress[1] + ".";
		temp += (unsigned short)IPaddress[2] + ".";
		temp += (unsigned short)IPaddress[3] + ".";
		return temp;
	}
}