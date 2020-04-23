#pragma once
#include "Headers.h"

struct WordStatus
{
	int iXPos;
	int iYPos;
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
	void NewDropWord(string NewWord);
	void Die();

	Word();
	~Word();
};

