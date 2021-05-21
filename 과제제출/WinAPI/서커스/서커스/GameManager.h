#pragma once
#include "ResourceManager.h"
#include "TemplateSingleton.h"
#include "DrawManager.h"
#include "Player.h"

class GameManager : public Singleton <GameManager>
{
private:
	Player *m_PlayerData;
public:
	void WholeInit();	//전체 초기화 총괄
	void MovingCharacter(int Key);	//캐릭터 이동 시키기
	void JumpingCharacter();	//캐릭터 점프 시키기

	void DrawCharacterOrder(HDC *hdc);
};

#define GameMgr GameManager::GetInstance()


/*
조작해보니까 점프한 상태에서는 방햐잌 눌러도 이도응ㄹ 안 하더라
조작감을 유지할 것인가 변경할 것인가
변경하는 게 더 재밌을 거 같은데


캐릭터 X 좌표는 고정
Y좌표만 점프시에 바뀜

캐릭터 이동 매커니즘
방향키 한 번 누르면 움직이고 다시 스탠딩으로 돌아오는 총 2프레임이 진행


점프시...
점프하면 점프 상태 동안 점프 모션임
스페이스바 누르면 점프 시간으로 정해진 시간 동안 키입력 안 받도록 처리를
해야할 것 같음
*/