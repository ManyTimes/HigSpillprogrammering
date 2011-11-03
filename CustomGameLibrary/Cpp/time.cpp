#include "../Header/time.h"

namespace cgl
{
	/************* PRIVATE FUNCTIONS ************/
	void Time::SetTime()
	{
		time ( &this->rawtime );
		this->timeinfo = localtime(&this->rawtime);
	}

	/************* CONSTRUCTOR ************/
	Time::Time()
	{
	}

	/************* PUBLIC FUNCTIONS ************/
	int Time::GetHour()
	{
		this->SetTime();
		return this->timeinfo->tm_hour;
	}

	int Time::GetMinute()
	{
		this->SetTime();
		return this->timeinfo->tm_min;
	}

	int Time::GetSecond()
	{
		this->SetTime();
		return this->timeinfo->tm_sec;
	}

	int Time::GetDay()
	{
		this->SetTime();
		return this->timeinfo->tm_mday;
	}

	int Time::GetMonth()
	{
		this->SetTime();
		return this->timeinfo->tm_mon;
	}

	int Time::GetYear()
	{
		this->SetTime();
		return this->timeinfo->tm_year;
	}
}