#pragma once
#include "Slot.h"

#define MAX_TABLE 100

typedef int HashFunction(int Key);

struct BookTable
{
	Slot Table[9][MAX_TABLE];
	HashFunction *KeyFunction;
	HashFunction *CategoryFunction;
};

void TableInit(BookTable *TableTmp, HashFunction *KeyFunctionTmp, HashFunction *CategoryFunctionTmp);

void TableInsert(BookTable* TableTmp, Key KeyTmp, Book *NewBook);

Book* TableDelete(BookTable* TableTmp, Key KeyTmp);

Book* TableSearch(BookTable* TableTmp, Key KeyTmp);