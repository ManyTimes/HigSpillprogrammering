#ifndef _INCLUDE_H
#define _INCLUDE_H
//STANDARD INCLUDES
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "math.h"
#include <fstream>

namespace cgl
{
	#define DEBUG true
	#ifdef _ISDLL
		#define DECLARE __declspec( dllexport )
	#else
		#define DECLARE  __declspec( dllimport )
	#endif
}

#endif
