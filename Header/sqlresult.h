#ifndef _SQLRESULT_H
#define _SQLRESULT_H
#include "include.h"
#include "sqlapi.h"
#include "sqlrow.h"

namespace cgl
{
	class DECLARE SqlResult
	{
	private:
		int allocateIncrementSize;
		int columnsLength;
	public:
		SqlRow* row;
		int totalRows;
		//***********CONSTRUCTOR***********
		SqlResult::SqlResult(std::string selectColumns[],int columnsLength);
		SqlResult::~SqlResult();

		//***********FUNCTIONS***********
		//Sets a value in row rowIndex at column columnIndex
		void SqlResult::SetValue(int rowIndex,int columnIndex, std::string value);
		//Returns value in row rowIndex at column columnIndex
		std::string SqlResult::GetValue(int rowIndex, int columnIndex);

		//Adds more space in memory for a total of 10 additional rows within the result.
		void SqlResult::AllocateMoreMemory();
	};
}

#endif