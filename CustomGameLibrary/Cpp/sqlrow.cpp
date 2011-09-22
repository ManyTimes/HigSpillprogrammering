#include "../Header/sqlrow.h"

namespace cgl
{
	//***********CONSTRUCTOR***********
	SqlRow::SqlRow()
	{
	}
	
	SqlRow::~SqlRow()
	{
		delete [] this->column;
	}

	void SqlRow::Initialize(int numberOfColumns)
	{
		column = new std::string[numberOfColumns];
		for(int i = 0; i < numberOfColumns; i++)
		{
			column[i] = "";
		}
	}

	//***********FUNCTIONS***********
	//Sets value in column N
	/*void SqlCommandRow::SetValue(int columnIndex, string value)
	{
		column[columnIndex] = value;
	}

	//Returns value in column N
	std::string SqlCommandRow::GetValue(int columnIndex)
	{
		return column[columnIndex];
	}*/
}