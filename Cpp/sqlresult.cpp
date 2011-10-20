#include "../Header/sqlresult.h"

namespace cgl
{
	//***********CONSTRUCTOR***********
	SqlResult::SqlResult(std::string selectColumns[],int numberOfColumns)
	{
		this->totalRows = 0;
		this->allocateIncrementSize = 10;
		this->columnsLength = numberOfColumns;
		this->row = new SqlRow[allocateIncrementSize];
		for(int i = 0; i < allocateIncrementSize; i++)							//For all rows, init their column values
		{
			if(numberOfColumns > 0)
			{
				this->row[i].Initialize(this->columnsLength);
			}
		}
	}
	SqlResult::~SqlResult()
	{
		delete [] this->row;
	}

	//***********FUNCTIONS***********
	//Sets a value in row rowIndex at column columnIndex
	void SqlResult::SetValue(int rowIndex,int columnIndex, std::string value)
	{
		this->row[rowIndex].column[columnIndex] = value;
	}
	//Returns value in row rowIndex at column columnIndex
	std::string SqlResult::GetValue(int rowIndex, int columnIndex)
	{
		return 	this->row[rowIndex].column[columnIndex];
	}

	//Adds more space in memory for a total of 10 additional rows within the result.
	void SqlResult::AllocateMoreMemory()
	{
		this->allocateIncrementSize += 10;
		this->row = (SqlRow*) realloc(row, allocateIncrementSize * sizeof(row));
		for(int i = this->allocateIncrementSize-10; i < this->allocateIncrementSize; i++)	//Only initializing the ten new rows, which will be empty at this point
		{
			this->row[i].Initialize(columnsLength);
		}
	}
}
