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

		return true;
	}
	else
		return false;
}

void WordManager::CreatNewEnemy()
{
	int iRandomNumber = rand() % m_iNumberofWords;
	Words.NewDropWord(m_sWordArr[iRandomNumber]);
}

void WordManager::DeleteStringArr()
{
	delete[] m_sWordArr;
}

WordManager::~WordManager()
{

}