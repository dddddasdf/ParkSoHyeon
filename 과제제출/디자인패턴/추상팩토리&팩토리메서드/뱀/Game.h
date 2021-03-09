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
	int m_iFeedCount;	//���� ����
	int m_iFeedSpawnTimer;	//���� ���� �ð� ������-���� �ð�
	int m_iFeedStandard;	//���� ���� �ð� ������-����
	int m_iMovingTimer;	//�����̴� �ð� ������-���� �ð�
	int m_iMovingStandard;	//�����̴� �ð� ������-����
	
public:
	Game();
	void Init();	//��ֹ� ��ġ �ʱ�ȭ �� ����
	void PrintScore();	//���� ǥ��
	void StartGame();	//���� ����
	void Menu();	//���۽� �޴� ������

	~Game();
};

