#include "WordManager.h"

WordManager::WordManager()
{

}

bool WordManager::LoadWordTextFile()
{
	ifstream WordFile;
	WordFile.open("Word.txt");

	if (WordFile.is_open())
	{
		WordFile >> m_iNumberofWords;
		m_sWordArr = new string[m_iNumberofWords];

		for (int i = 0; i < m_iNumberofWords; i++)
			WordFile >> m_sWordArr[i];

		Words.InitNodes();
		WordFile.close();
		return true;
	}
	else
		return false;
}

void WordManager::CreatNewEnemy()
{
	int iRandomNumber = rand() % m_iNumberofWords;
	Words.MakeNewWordStruct(m_sWordArr[iRandomNumber]);
}

bool WordManager::MoveEnemy()
{
	bool bTmp;
	bTmp = Words.Dropping();
	return bTmp;
}

void WordManager::PrintEnemy()
{
	Words.Print();
}

int WordManager::CheckIsCorrect(string InputString)
{
	int iTmp;
	iTmp = Words.CheckCorrect(InputString);

	return iTmp;
}

void WordManager::DeleteStringArray()
{
	Words.DeleteAllWords();
	delete[] m_sWordArr;
}

void WordManager::ClearWords()
{
	Words.DeleteAllWords();
	Words.InitNodes();
}

WordManager::~WordManager()
{

}