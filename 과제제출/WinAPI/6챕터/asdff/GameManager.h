#pragma once
#include "TemplateSingleton.h"
#include "Enums.h"
#include "BitMapManager.h"
#include "CardOrdering.h"

class GameManager : public Singleton <GameManager>
{
private:
	int m_NumberOfRevealed;	//현재 "임시로" 뒤집혀져 있는 카드의 개수
	int m_IndexFirst, m_IndexSecond;	//뒤집었을 때 인덱스 받아오는 용도
	int m_NumberOfCorrect;	//짝을 맞춘 개수
	bool m_IsPenalty;	//만약 잘못된 짝을 찾았을 경우 홀드용
	int m_PenaltyTime;

public:
	void InitMemberVariable();	//멤버변수 초기화

	bool ReturnIsPenalty() { return m_IsPenalty; }	//패넕티 상태임을 리턴
	void MouseLeftButtonAction(int MouseX, int MouseY);	//마우스 왼쪽 버튼 눌렀을 때 동작할 함수
	void PenaltyTimeAction();	//패널티 시간 중일 때 상태
	bool IsAllCorrect();	//전부 짝을 맞췄는가 확인
};
#define GameMgr GameManager::GetInstance()

/*
출력함수는 어디서 호출할 것인가->메인 함수가 하는 게 맞는 거 같음
매니저가 호출할 것인가
메인이 호출할 것인가

*/

/*
벌칙 관련 명칭은 Penalty가 함수 명칭에 들어갈 것...


*/