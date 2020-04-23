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
	string m_sUserName;
public:
	void PlayMain();	//�÷��� ���� �Լ� 
	void PrintSynopsis();
	void CleaningSynopsisArea();	//�ó�ý� ��� ���� û��
	void CleanParticularArea(int StartX, int EndX, int StartY, int EndY);	//Ư�� ���� û��
	void Init();
	void PrintBottomArea();
	void PrintLife();
	void PrintScore();
	void PrintName();
	void GetName();
	void PrintStageNumber();


	Play();
	~Play();
};

