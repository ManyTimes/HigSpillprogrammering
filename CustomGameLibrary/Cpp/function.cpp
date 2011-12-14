#include "../Header/function.h"

namespace cgl
{
	void CGLInitialize()
	{
		srand((unsigned)time(NULL));					//Initialize random seed with time
		cgl::GetRandomInt(1,3);							//First random runs silently from the library, to start off the fixed seed
		cgl::GetRandomFloat(1.0f, 2.0f);				//This function shoudl actually call on InitGLFW, InitOpengl, InitSDL, InitSDLNet, so calling this
	}													//Will automatically init all sub-libraries this library uses without the need of actually creating objects from this library
														//in a particular order for some objects to work...
	//Returns whether the system is little-endian
	bool isSystemLittleEndian() 
	{
		//The short value 1 has bytes (1, 0) in little-endian and (0, 1) in//big-endian
		short s = 1;
		return (((char*)&s)[0]) == 1;
	}

	int GetRandomInt(int low, int high)
	{
		//#define RANDOMINT(lownumber, highnumber) (int)((lownumber) + (highnumber + 1 - lownumber) * (rand() / (float) RAND_MAX));
		return (int)((low + (high + 1 - low) * rand() / (float) RAND_MAX));
	}

	float GetRandomFloat(float low, float high)
	{
		//#define RANDOMFLOAT(lownumer, highnumber) ((lownumer) + (highnumber - lownumer) * (rand() / (float) RAND_MAX));
		return (float)(low + (high - low) * rand() / (float) RAND_MAX);
	}

	int RANDOMINT(int low, int high)
	{
		//#define RANDOMINT(lownumber, highnumber) (int)((lownumber) + (highnumber + 1 - lownumber) * (rand() / (float) RAND_MAX));
		return (int)((low + (high + 1 - low) * rand() / (float) RAND_MAX));
	}

	float RANDOMFLOAT(float low, float high)
	{
		//#define RANDOMFLOAT(lownumer, highnumber) ((lownumer) + (highnumber - lownumer) * (rand() / (float) RAND_MAX));
		return (float)(low + (high - low) * rand() / (float) RAND_MAX);
	}


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

	int GetArrayLength(std::string inputarray[])
	{
		int length = 0;
		for(int i = 0; inputarray[i].c_str() != '\0'; i++)
		{
			length ++;
		}
		return length;
	}

	//Print out an error message in the command window
	//Automatically calls SDLNet_GetError();
	void Error(std::string message)
	{
		//if(CGL_DEBUG_MODE)						//Displays error only upon "DEBUG mode", change it to a preprocessor.
		//{
			std::cout << std::endl << "Error: " << std::endl << message << ": " << SDLNet_GetError() << std::endl;
	//	}										//Always exit
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

	float s2f(std::string value)
	{
		return c2f((char*)value.c_str());
	}

	int d2i(double value)
	{
		return (int)value;
	}

	int d2i(double value, bool round)
	{
		if(round == true)
		{
			return (int) value+0.5;
		}
		return (int)value;
	}

	std::string i2s(int value)
	{
		std::stringstream out;
		out << value;
		return out.str();
	}

	std::string c2s(char value[])
	{
		return (std::string)value;
	}
	std::string d2s(double value)
	{
		return 0;
		//return (std::string)value;
	}
	void i2c (char returnChar[], int value)
	{
		itoa(value, returnChar, 10);
		return;
	}

	float c2f(char* charNumber)
	{
		return std::atof(charNumber);
	}	

	//DOES NOT WORK!? Not even with .c_str() nor with a cast to char*...
	const char* f2c(float value)
	{
		std::stringstream str;
		str << value;
		return str.str().c_str();
	}

	std::string f2s(float value)
	{	
		std::stringstream str;
		str << value;
		return str.str();
	}

	double c2d(const char* value)
	{
		return atof(value);
	}

	double s2d(std::string value)
	{
		return atof(value.c_str());
	}

	char* s2c(std::string value)
	{
		return (char*)value.c_str();
	}

	void Sleep(int ms)
	{
		SDL_Delay(ms);
	}
	void Sleep(float ms)
	{
		SDL_Delay(ms);
	}

	void Delay(int ms)
	{
		SDL_Delay(ms);
	}

	void Delay(float ms)
	{
		SDL_Delay(ms);
	}

	void Wait(int ms)
	{
		SDL_Delay(ms);
	}

	void Wait(float ms)
	{
		SDL_Delay(ms);
	}
	
	/************///////////NOTE 
	/************///////////Cout and Exit() are always being called. The idea was to have them based on a preprocessor.
	/************///////////If preprocessor was defined, then do either print it out or not, for debug purposes...
	//Print a string message
	void Cout(std::string message)
	{
		//if(CGL_DEBUG_MODE)
	//	{
			std::cout << message <<  std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "_CGLDEBUG IS NOT DECLARED"<< std::endl;
	//	}
	}

	//Print two string messages
	void Cout(std::string message, std::string message2)
	{
	//	if(CGL_DEBUG_MODE)
	//	{
			std::cout << message << " " << message2;
	//	}
	}

	//Print out an IP address if debug mode is true
	void CoutIP(Uint8* IPaddress)
	{
	//	if(CGL_DEBUG_MODE)
	//	{
		std::cout << "IP: " << (unsigned short)IPaddress[0] << "."
			<< (unsigned short)IPaddress[1] << "."
			<< (unsigned short)IPaddress[2] << "."
			<< (unsigned short)IPaddress[3];
	//	}
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



	/*explicit auto_array(T* array_ = NULL) : array(array_), isReleased(false)
	{
	}*/
	
	
	/*auto_array::auto_array(const auto_array<T> &aarray) 
	{
		array = aarray.array;
		isReleased = aarray.isReleased;
		aarray.isReleased = true;
	}
	auto_array::~auto_array() 
	{
		if (!isReleased && array != NULL) 
		{
			delete[] array;
		}
	}
	T* auto_array::release() 
	{
		isReleased = true;
		return array;
	}
	void auto_array::reset(T* array_ = NULL) 
	{
		if (!isReleased && array != NULL) 
		{
			delete[] array;
		}
		array = array_;
	}*/



	/*
	T* auto_array::get() const 
	{
		return array;
	}
	T auto_array::&operator*() const 
	{
		return *array;
	}
	void auto_array::operator=(const auto_array<T> &aarray) 
	{
		if (!isReleased && array != NULL) 
		{
			delete[] array;
		}
		array = aarray.array;
		isReleased = aarray.isReleased;
		aarray.isReleased = true;
	}
	T* auto_array::operator->() const 
	{
		return array;
	}
	T* auto_array::operator+(int i) 
	{
		return array + i;
	}
	T auto_array::&operator[](int i) 
	{
		return array[i];
	}*/

	
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes)
	{
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
	
	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes)
	{
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}
	
	//Reads the next four bytes as an integer, using little-endian form
	int readInt(std::ifstream &input)
	{
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(std::ifstream &input)
	{
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}



	/*template<class T>auto_array<T>::~auto_array() 
	{
		if (!isReleased && array != NULL) 
		{
			delete[] array;
		}
	}
	template<class T>auto_array<T>::auto_array(const auto_array<T> &aarray)
	{
		array = aarray.array;
		isReleased = aarray.isReleased;
		aarray.isReleased = true;
	}*/

	/*template<class T>T* auto_array<T>::get() const
	{
		return array;
	}*/

	/*template<class T>T& auto_array<T>::operator*() const 
	{
		return *array;
	}

	template<class T>void auto_array<T>::reset(T* array_ = NULL) 
	{
		if (!isReleased && array != NULL) 
		{
			delete[] array;
		}
		array = array_;
	}*/

}