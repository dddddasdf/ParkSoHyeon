#pragma once
#include "Headers.h"
#define MAKE_ITEM 6
#define DUMMYPOSITION -1
#define NO_ACCORDING_STRING -1

enum ITEM
{
	ITEM_NULL = 0,
	ITEM_SLOW = 1,
	ITEM_FAST = 2,
	ITEM_STOP = 3,
	ITEM_DELETE_ALL = 4,
	ITEM_HIDE = 5
};

struct WordStatus
{
	int iXPos;
	int iYPos;
	int iIsHaveItem;
	string sWord;
	WordStatus *Next;
};

class Word
{
private:
	WordStatus *FirstNode;
	WordStatus *LastNode;
public:
	void InitNodes();
	void MakeNewWordStruct(string NewWord);	//새 단어 구조체 생성
	bool Dropping();	//단어 떨구기
	void Print();
	int CheckCorrect(string GetWord);
	void DeleteAllWords();

	Word();
	~Word();
};

