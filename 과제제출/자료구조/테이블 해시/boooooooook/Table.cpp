#include "Table.h"

void TableInit(BookTable *TableTmp, HashFunction *KeyFunctionTmp, HashFunction *CategoryFunctionTmp)
{
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < MAX_TABLE; i++)
			(TableTmp->Table[j][i]).STATUS = SLOTSTATUS_EMPTY;
	}
	
	TableTmp->KeyFunction = KeyFunctionTmp;
	TableTmp->CategoryFunction = CategoryFunctionTmp;
}

void TableInsert(BookTable* TableTmp, Key KeyTmp, Book *NewBook)
{
	int iHashNumber = TableTmp->KeyFunction(KeyTmp);
	int iCategoryNumber = TableTmp->CategoryFunction(KeyTmp);
	TableTmp->Table[iCategoryNumber][iHashNumber].Value = NewBook;
	TableTmp->Table[iCategoryNumber][iHashNumber].kKey = KeyTmp;
	TableTmp->Table[iCategoryNumber][iHashNumber].STATUS = SLOTSTATUS_INUSE;
}

Book* TableDelete(BookTable* TableTmp, Key KeyTmp)
{
	int iHashNumber = TableTmp->KeyFunction(KeyTmp);
	int iCategoryNumber = TableTmp->CategoryFunction(KeyTmp);

	if (TableTmp->Table[iCategoryNumber][iHashNumber].STATUS != SLOTSTATUS_INUSE)
		return NULL;
	else
	{
		TableTmp->Table[iCategoryNumber][iHashNumber].STATUS = SLOTSTATUS_DELETED;
		return TableTmp->Table[iCategoryNumber][iHashNumber].Value;
	}
}

Book* TableSearch(BookTable* TableTmp, Key KeyTmp)
{
	int iHashNumber = TableTmp->KeyFunction(KeyTmp);
	int iCategoryNumber = TableTmp->CategoryFunction(KeyTmp);

	if (TableTmp->Table[iCategoryNumber][iHashNumber].STATUS != SLOTSTATUS_INUSE)
		return NULL;
	else
		return TableTmp->Table[iCategoryNumber][iHashNumber].Value;
}