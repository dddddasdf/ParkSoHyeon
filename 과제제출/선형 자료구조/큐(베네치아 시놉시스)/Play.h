#pragma once
#include "MapDraw.h"
#include "WordManager.h"

struct SynopsisNode
{
	string sSentence;
	SynopsisNode *Next;
};

struct SynopsisQueue
{
	SynopsisNode *Front;
	SynopsisNode *Rear;
};

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
	void PlayMain(string &NameTmp, int &ScoreTmp, int &StageTmp);	//�÷��� ���� �Լ� 
	void PrintSynopsis();
	void EnQueueSynopsis(SynopsisQueue *Queue, string NewSentence);
	void DeQueueSynopsis(SynopsisQueue *Queue);
	void CleanParticularArea(int StartX, int EndX, int StartY, int EndY);	//Ư�� ���� û��
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

