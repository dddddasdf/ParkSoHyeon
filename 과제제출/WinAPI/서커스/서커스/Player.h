#pragma once
#include "Defines.h"


class Player
{
private:
	int m_PlayerLife;
	int m_PlayerScore;
	int m_PlayerMotion;
	int m_PlayerYLocation;
public:
	Player() { InitPlayer(); }

	void InitPlayer();
	void ChangeMotion(int State);

	int ReturnMotion() { return m_PlayerMotion; }
	int ReturnCharacterYLocation() { return m_PlayerYLocation; }
};

