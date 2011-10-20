#ifndef _FUNCTION_H
#define _FUNCTION_H

//THIS FILE SHOULD ONLY CONTAINS STANDARD FUNCTIONS; NOT SDL NOR OPENGL STUFF
//THINGS LIKE CONVERTING FROM ONE DATATYPE TO ANOTHER; PRINTING; ERROR; LENGTH OF STUFF; DATE TIME...
#include "include.h"
#include "SDL_net.h"

namespace cgl
{
	DECLARE int s2i(std::string value);
	DECLARE std::string i2s(int value);
	DECLARE char* s2c(std::string value);
	DECLARE void i2c (char returnChar[], int value);
	DECLARE double s2d(std::string value);
	DECLARE int d2i(double value, bool round);
	DECLARE int d2i(double value);
	DECLARE std::string d2s(double value);
	DECLARE double c2d(const char* value);
	DECLARE std::string c2s(char value[]);
	DECLARE void Error(std::string message);
	DECLARE void Cout(std::string message);
	DECLARE void Cout(std::string message, std::string message2);
	DECLARE void CoutIP(Uint8* IPaddress);
	DECLARE std::string GetIP(Uint8* IPaddress);
	DECLARE int GetArrayLength(int inputarray[]);
	DECLARE int GetArrayLength(char inputarray[]);
	DECLARE int GetArrayLength(std::string inputarray[]);

	/*template<class T> class DECLARE auto_array
	{
	private: 
		T* array;
		mutable bool isReleased;
	public:
		explicit auto_array(T* array_ = NULL):
		array(array_), isReleased(false)
		{
		}

		auto_array::auto_array(const auto_array<T> &array_);
		auto_array::~auto_array();
		T* release() ;
		void auto_array::reset(T* array_ = NULL);

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
		}

		T* get() const;
		T &operator*() const;
		void operator=(const auto_array<T> &array_);
		T* operator->() const;
		T* operator+(int i);
		T &operator[](int i);
	};*/

	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes); 
	
	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes); 
	
	//Reads the next four bytes as an integer, using little-endian form
	int readInt(std::ifstream &input);
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(std::ifstream &input);
	
	//Just like auto_ptr, but for arrays
	/*template<class T>
	class DECLARE auto_array 
	{
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) 
				{
			}	

			auto_array(const auto_array<T> &aarray);
			~auto_array();
			T* auto_array::get() const
			{
				return array;
			}
			T &operator*() const;
			
			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			T* operator->() const {
				return array;
			}
			
			T* release() {
				isReleased = true;
				return array;
			}
			
			void reset(T* array_ = NULL);
			
			T* operator+(int i) {
				return array + i;
			}
			
			T &operator[](int i) 
			{
				return array[i];
			}
	};*/
}
#endif