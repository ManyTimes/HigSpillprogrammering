#ifndef _SQLROW_H
#define _SQLROW_H
#include "include.h"
#include "function.h"
#include "SQLAPI.h"

namespace cgl
{
	class DECLARE SqlRow									//A row from an SQL select statement
	{
	private:
	public:
		std::string* column;							//Holds the value in the column N, as a string
		//***********CONSTRUCTOR***********
		SqlRow::SqlRow();
		SqlRow::~SqlRow();
		//Initializes number of columns within this row
		void SqlRow::Initialize(int numberOfColumns);
		//***********FUNCTIONS***********
		//Sets value in column N
		//void SqlCommandRow::SetValue(int columnIndex, string value);
		//Returns value in column N
		//std::string SqlCommandRow::GetValue(int columnIndex);
	};
}

#endif