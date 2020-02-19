#pragma once
#include "headers.h"
#include "Snake.h"
#include"BlockManager.h"


class Game
{
private:
	BlockManager m_BlockManager;
	//int m_iarrBlockXY[159][2];	//�� ��ǥ ���� 2���� �迭
	//int m_iarrFeedXY[MAX_FEED][2];	//���� ��ǥ ���� 2���� �迭
	//int m_iarrObsXY[MAX_OBS][2];	//��ֹ� ��ǥ ���� 2���� �迭
	//Block Blocks;
	int m_iScore;
	int m_iFeedCount;	//���� ����
	int m_iFeedSpawnTimer;	//���� ���� �ð� ������-���� �ð�
	int m_iFeedStandard;	//���� ���� �ð� ������-����
	int m_iMovingTimer;	//�����̴� �ð� ������-���� �ð�
	int m_iMovingStandard;	//�����̴� �ð� ������-����
	Snake Player;
public:
	Game();
	void Init();	//��ֹ� ��ġ �ʱ�ȭ �� ����
	void PrintScore();	//���� ǥ��
	void StartGame();	//���� ����
	void Menu();	//���۽� �޴� ������
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

