#pragma once
#include "Headers.h"
#include "Word.h"

class WordManager
{
private:
	Word Words;
	string *m_sWordArr;
	int m_iNumberofWords;
public:
	bool LoadWordTextFile();
	void CreatNewEnemy();
	void MoveEnemy();
	void CheckIsCorrect(string InputString);
	void DeleteStringArr();
	
	WordManager();
	~WordManager();
};

