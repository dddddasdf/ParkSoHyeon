#pragma once
#include "BlockManager.h"
#include "Alarm.h"

class Game
{
private:
	BlockManager m_BlockManager;

public:
	Game();
	void Init();	//���� ���۽� �ʱ�ȭ
	void ShowGuide();	//�ϴܺο� ���̵� ���

	~Game();
};

/*
�ϴ� ������ ������ �����
ȭ�鿡 ���� �������� ����(�̵��� ����Ŵ)
�ٸ� �ǳ� �ϴܺο� �� 3������ �ֱ⿡ ���� �����ȴ�
������ �˶� ������ �ߴٸ� ��� ��� �˶� �ش�
�� �ϸ� �� �˷��ְ� ���� �Դٰ�����


*/