#pragma once
#include "Slot.h"
#include "LinkedList.h"

#define MAX_TABLE 100

typedef double HashFunction(Key KeyTmp);

struct BookTable
{
	Slot Table[9][MAX_TABLE];
	HashFunction *KeyFunction;
	HashFunction *CategoryFunction;
};

void TableInit(BookTable *TableTmp, HashFunction *KeyFunctionTmp, HashFunction *CategoryFunctionTmp);

void TableInsert(BookTable* TableTmp, Key KeyTmp, Book *NewBook);

bool TableIsEmpty(BookTable* TableTmp, Key KeyTmp);

Book* TableDelete(BookTable* TableTmp, Key KeyTmp);

Book* TableSearch(BookTable* TableTmp, Key KeyTmp);