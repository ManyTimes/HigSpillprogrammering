#ifndef _INCLUDE_H
#define _INCLUDE_H
//STANDARD INCLUDES
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "math.h"
#include <fstream>
#include "settings.h"

namespace cgl
{
	
	#ifdef _CGLDLL
		#define DECLARE __declspec( dllexport )
	#else
		#define DECLARE  __declspec( dllimport )
	#endif

	
	#ifdef _CGLDEBUG
		#define CGL_DEBUG_MODE true
	#else
		#define CGL_DEBUG_MODE false
	#endif


}

#endif
