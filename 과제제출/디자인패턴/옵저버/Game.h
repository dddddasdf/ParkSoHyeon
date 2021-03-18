#pragma once
#include "BlockManager.h"
#include "Alarm.h"

class Game
{
private:
	BlockManager *m_BlockManager;
	Player *User;
	ClearDragon *Dragon;

	int m_iDragonSpawnTime;
public:
	Game();
	void Init();	//���� ���۽� �ʱ�ȭ
	void NowPlaying();
	void ShowGuide();	//�ϴܺο� ���̵� ���
	void AlarmState();

	~Game();
};

/*
�ϴ� ������ ������ �����
ȭ�鿡 ���� �������� ����(�̵��� ����Ŵ)
�ٸ� �ǳ� �ϴܺο� �� 3������ �ֱ⿡ ���� �����ȴ�
������ �˶� ������ �ߴٸ� ��� ��� �˶� �ش�
�� �ϸ� �� �˷��ְ� ���� �Դٰ�����


*/