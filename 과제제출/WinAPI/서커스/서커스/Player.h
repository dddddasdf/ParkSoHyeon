#pragma once
#include "Defines.h"


class Player
{
private:
	int m_PlayerLife;
	int m_PlayerScore;
	int m_PlayerMotion;
	int m_PlayerYLocation;	//ȭ�鿡�� ���̴� �÷��̾��� Y��ǥ.
	int m_PlayerXLocation;	//��ü �� ���̿��� �÷��̾ ���� ��ġ�� X��ǥ. ȭ�鿡�� ���̴� ��ġ�� X��ǥ�� �ƴ�.
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

