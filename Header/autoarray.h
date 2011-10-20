#ifndef _AUTOARRAY_H
#define _AUTOARRAY_H
#include "include.h"
#include "function.h"
#include <assert.h>

namespace cgl
{
	//Just like auto_ptr, but for arrays
	//Objects within this class gets destructed automatically when the auto_array object is destructed.
	//Usage: cgl::auto_array<int> colorRed(new int[256]);  
	//colorRed[25] = 10;	//Sets index 25 to 10
	//colorRed.get();		//Gets the whole INT array
	//The int array of colorRed of size 256 is automaticall destructed when needed: at the end of a function. We do not need to call delete ourselves
	template<class T>
	class DECLARE auto_array 
	{
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL)
			{
				array = array_;
				isReleased = false;
			}
			
			auto_array(const auto_array<T> &aarray)
			{
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			~auto_array()
			{
				if (!isReleased && array != NULL) 
				{
					delete[] array;
				}
			}
			
			T* Get() const 
			{
				return array;
			}
			
			T &operator*() const 
			{
				return *array;
			}
			
			void operator=(const auto_array<T> &aarray) 
			{
				if (!isReleased && array != NULL) 
				{
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			T* operator->() const 
			{
				return array;
			}
			
			T* Release()
			{
				isReleased = true;
				return array;
			}
			
			void Reset(T* array_ = NULL) 
			{
				if (!isReleased && array != NULL) 
				{
					delete[] array;
				}
				array = array_;
			}
			
			T* operator+(int i) 
			{
				return array + i;
			}
			
			T &operator[](int i) 
			{
				return array[i];
			}
	};
}

#endif