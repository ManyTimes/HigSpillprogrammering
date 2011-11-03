#include "../Header/autoarray.h"

namespace cgl
{
	//DOES NOT WORK HAVING THESE FUNCTIONS HERE!
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

	/*template<class T>T* auto_array<T>::release() 
	{
		isReleased = true;
		return array;
	}*/
}

