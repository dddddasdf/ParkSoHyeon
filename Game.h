#pragma once
#include "headers.h"
#include "Snake.h"
#include"BlockManager.h"


class Game
{
private:
	BlockManager m_BlockManager;
	//int m_iarrBlockXY[159][2];	//블럭 좌표 저장 2차원 배열
	//int m_iarrFeedXY[MAX_FEED][2];	//먹이 좌표 저장 2차원 배열
	//int m_iarrObsXY[MAX_OBS][2];	//장애물 좌표 저장 2차원 배열
	//Block Blocks;
	int m_iScore;
	int m_iFeedCount;	//먹이 개수
	int m_iFeedSpawnTimer;	//먹이 생성 시간 조절용-현재 시간
	int m_iFeedStandard;	//먹이 생성 시간 조절용-기준
	int m_iMovingTimer;	//움직이는 시간 조절용-현재 시간
	int m_iMovingStandard;	//움직이는 시간 조절용-기준
	Snake Player;
public:
	Game();
	void Init();	//장애물 위치 초기화 및 생성
	void PrintScore();	//점수 표기
	void StartGame();	//게임 시작
	void Menu();	//시작시 메뉴 보여줌
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

