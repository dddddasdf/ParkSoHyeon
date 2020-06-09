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
	void LoadRankingFile();	//��ŷ �ҷ�����
	void SortRanking();	//��ŷ ����
	void ShowRanking();	//��ŷ �����ֱ�
	void GetNameAndScore(string Name, int Score, int Stage);	//�÷��̰� �Ϸ�Ǹ� �̸��� ������ �޾ƿͼ� ������ ���Ͽ� �����Ѵ�
	void FreeDynamicArrays();
	
	Rank();
	~Rank();
};

