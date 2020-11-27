#pragma once
#include "BlockManager.h"

class Game
{
private:
	BlockManager m_BlockManager;

public:
	Game();
	void Init();	//최초 시작시 초기화
	void ShowGuide();	//하단부에 가이드 출력

	~Game();
};

