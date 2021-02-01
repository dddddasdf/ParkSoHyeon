#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct UserInformation
{
	string sName;
	int iScore;
	int iStageNumber;
};

class Rank
{
private:
	MapDraw RankInterface;

	UserInformation *UserStructs;
	int m_iNumberofStruct;
public:
	void LoadRankingFile();	//랭킹 불러오기
	void SortRanking();	//랭킹 정렬
	void ShowRanking();	//랭킹 보여주기
	void GetNameAndScore(string Name, int Score, int Stage);	//플레이가 완료되면 이름과 점수를 받아와서 데이터 파일에 저장한다
	void FreeDynamicArrays();
	
	Rank();
	~Rank();
};

