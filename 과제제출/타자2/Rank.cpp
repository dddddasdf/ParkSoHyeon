#include "Rank.h"

Rank::Rank()
{

}

void Rank::GetNameAndScore(string Name, int Score, int Stage)
{
	ofstream RankFile;
	RankFile.open("Rank.txt", ios::app);

	if (RankFile.is_open())
		RankFile << Name << " " << Score << " " << Stage << "\n";

	RankFile.close();
}

Rank::~Rank()
{

}