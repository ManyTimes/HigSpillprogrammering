#ifndef _TIME_H
#define _TIME_H
#include "include.h"
#include <stdio.h>
#include <time.h>

namespace cgl
{
	//Class that gets the current time, locally
	class DECLARE Time
	{
	private:
		time_t rawtime;
		struct tm* timeinfo;
		void Time::SetTime();
	public:
		Time::Time();
		int Time::GetHour();
		int Time::GetMinute();
		int Time::GetSecond();
		int Time::GetDay();
		int Time::GetMonth();
		int Time::GetYear();
	};
}
#endif		//END NOT DEFINED