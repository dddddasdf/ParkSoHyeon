#pragma once
#include "MapDraw.h"

class Play
{
private:
	MapDraw GameInterface;
	int m_iLife;
	int m_iScore;
	string m_sUserName;
public:
	void PlayMain();	//플레이 메인 함수 
	void PrintSynopsis();
	void CleaningSynopsisArea();	//시놉시스 출력 구간 청소
	void CleanParticularArea(int StartX, int EndX, int StartY, int EndY);	//특정 구간 청소
	void Init();
	void PrintBottomArea();
	void PrintLife();
	void PrintScore();
	void PrintName();
	void GetName();
	
	Play();
	~Play();
};

