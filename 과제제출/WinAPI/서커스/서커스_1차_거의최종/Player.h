#pragma once
#include "Defines.h"


class Player
{
private:
	int m_PlayerLife;
	int m_PlayerScore;
	int m_PlayerMotion;
	int m_PlayerYLocation;	//화면에서 보이는 플레이어의 Y좌표.
	int m_PlayerXLocation;	//전체 맵 길이에서 플레이어가 현재 위치한 X좌표. 화면에서 보이는 위치의 X좌표가 아님.
	int m_PlayerDirection;
public:
	Player() { InitPlayer(); }

	void InitPlayer();
	void DeadInit();	//아무튼 부딪쳐서 죽었을 때 일부분 초기화
	void ChangeMotion(const int& State);
	void ChangeXLocation(const int& Key);
	void ChangeYLocation(bool IsUp);

	int ReturnMotion() { return m_PlayerMotion; }
	int ReturnCharacterXLocation() { return m_PlayerXLocation; }
	int ReturnCharacterYLocation() { return m_PlayerYLocation; }
	int ReturnScore() { return m_PlayerScore; }
	int ReturnLife() { return m_PlayerLife; }
	void MinusLife() { m_PlayerLife--; }	//사망시 목숨 줄어듬
	void PlusScore(const int& Score) { m_PlayerScore += Score; }
	
	void SetYLocation(const int& Y) {
		m_PlayerYLocation = Y; //골인시 강제로 y좌표 고정
	}
};

