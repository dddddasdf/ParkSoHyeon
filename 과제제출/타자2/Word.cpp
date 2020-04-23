#include "Word.h"
#define DUMMYPOSITION -1

Word::Word()
{

}

void Word::InitNodes()
{
	FirstNode = new WordStatus;
	LastNode = new WordStatus;

	FirstNode->iXPos = DUMMYPOSITION;
	FirstNode->iYPos = DUMMYPOSITION;
	FirstNode->sWord = "";
	FirstNode->Next = NULL;

	LastNode->iXPos = DUMMYPOSITION;
	LastNode->iYPos = DUMMYPOSITION;
	LastNode->sWord = "";
	LastNode->Next = NULL;
}

void Word::NewDropWord(string NewWord)
{
	if (FirstNode->sWord == "")
	{

	}
}

Word::~Word()
{

}