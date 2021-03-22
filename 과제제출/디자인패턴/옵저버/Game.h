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
	void Init();	//최초 시작시 초기화
	void NowPlaying();
	void ShowGuide();	//하단부에 가이드 출력
	void AlarmState();

	~Game();
};

/*
일단 옵저버 패턴을 만든다
화면에 유저 아이콘은 띄운다(이동은 못시킴)
다리 건너 하단부에 몹 3가지가 주기에 따라 생성된다
유저가 알람 설정을 했다면 출근 퇴근 알람 준다
안 하면 안 알려주고 몹만 왔다갔다함


*/