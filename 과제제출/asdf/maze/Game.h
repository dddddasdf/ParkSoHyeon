#pragma once
#include "BlockManager.h"

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

