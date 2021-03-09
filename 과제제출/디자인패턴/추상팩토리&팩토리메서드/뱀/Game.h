#pragma once
#include "headers.h"
#include "Snake.h"
#include"BlockManager.h"
#include "Headers (2).h"
#include "BlockFactory.h"


class Game
{
private:
	BlockManager m_BlockManager;
	Snake Player;

	int m_iScore;
	int m_iFeedCount;	//먹이 개수
	int m_iFeedSpawnTimer;	//먹이 생성 시간 조절용-현재 시간
	int m_iFeedStandard;	//먹이 생성 시간 조절용-기준
	int m_iMovingTimer;	//움직이는 시간 조절용-현재 시간
	int m_iMovingStandard;	//움직이는 시간 조절용-기준
	
public:
	Game();
	void Init();	//장애물 위치 초기화 및 생성
	void PrintScore();	//점수 표기
	void StartGame();	//게임 시작
	void Menu();	//시작시 메뉴 보여줌

	~Game();
};

