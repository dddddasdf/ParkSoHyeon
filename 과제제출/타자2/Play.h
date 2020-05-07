#pragma once
#include "MapDraw.h"
#include "WordManager.h"

class Play
{
private:
	MapDraw GameInterface;
	WordManager GameWordManager;

	int m_iLife;
	int m_iScore;
	int m_iStageNumber;
	int m_iSpawnSpeed;
	int m_iMovingSpeed;
	int m_iNumberOfKilledEnemy;
	string m_sUserName;
public:
	void PlayMain(string &NameTmp, int &ScoreTmp, int &StageTmp);	//플레이 메인 함수 
	void PrintSynopsis();
	void CleanParticularArea(int StartX, int EndX, int StartY, int EndY);	//특정 구간 청소
	void Init();
	void PrintBottomArea();
	void PrintLife();
	void PrintScore();
	void PrintName();
	void GetName();
	void PrintStageNumber();
	void MoveToNextStage();


	Play();
	~Play();
};

