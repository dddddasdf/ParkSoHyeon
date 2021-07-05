#pragma once
#include "ResourceManager.h"
#include "TemplateSingleton.h"
#include "DrawManager.h"
#include "Player.h"

class GameManager : public Singleton <GameManager>
{
private:
	Player *m_PlayerData;

	bool m_IsMoving;	//움직이는 중인지 체크하는 용도
	bool m_IsJumping;	//점프하는 중인지 체크하는 용도
	bool m_IsHighest;	//점프할 때 Y축 조절을 위하여 최고 고도에 도달했는지 아닌지 확인하기


	int m_MovingDirection;	//링 위치 조절을 위한 방향 저장 멤버 변수

	bool m_IsDeadTrigger;	//사망 상태일 경우 화면 갱신을 잠시 멈추기 위한 변수, 살아있을 때는 true 죽었을 때는 false

	int m_BonusScore;	//보너스 점수
public:
	void WholeInit(HWND hWnd, HDC hdc);	//전체 초기화 총괄
	void PartialInit();	//화로나 고리에 부딪쳤을시 일부분 초기화
	void MovingCharacter(const int& Key);	//캐릭터 이동 시키기
	void JumpingCharacter();	//캐릭터 점프 시키기
	void ChangeCharacterYLocation();	//캐릭터 Y축 변경시키기
	void StandingCharacter();	//캐릭터 모션 변경
	bool ReturnIsMoving() { return m_IsMoving; }
	bool ReturnIsJumping() { return m_IsJumping; }
	bool ReturnIsDead() { return m_IsDeadTrigger; }

	void CalculateRings(float elapsed);
	void MinusBonusScore() { if (m_BonusScore > 0) m_BonusScore -= 10; }

	void CollisionCheck();	//충돌 체크 총괄
	bool GoalInCheck();	//골인 체크

	void Winning(HDC *hdc, HWND hWnd);	//골인 했을 때

	void DrawCharacterOrder(HDC *hdc, HWND hWnd) { DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation(), 
		m_PlayerData->ReturnLife(), m_PlayerData->ReturnScore(), m_BonusScore); }
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