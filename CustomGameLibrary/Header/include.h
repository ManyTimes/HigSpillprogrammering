//STANDARD INCLUDES
#include <stdexcept>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "math.h"
#include <fstream>

namespace cgl
{
	#define DEBUG true
	#ifdef ISDLL
		#define DECLARE  __declspec( dllexport )
	#else
		#define DECLARE  __declspec( dllimport )
	#endif
}