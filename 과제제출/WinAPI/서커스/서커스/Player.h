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
	void ChangeMotion(const int& State);
	void ChangeYLocation(bool IsUp);
	void ChangeXLocation(const int& Key);

	int ReturnMotion() { return m_PlayerMotion; }
	int ReturnCharacterYLocation() { return m_PlayerYLocation; }
	int ReturnCharacterXLocation() { return m_PlayerXLocation; }
};

