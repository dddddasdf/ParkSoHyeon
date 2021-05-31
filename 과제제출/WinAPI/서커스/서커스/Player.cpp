#include "Player.h"


void Player::InitPlayer()
{
	m_PlayerLife = PLAYER_LIFE;
	m_PlayerScore = 0;
	m_PlayerMotion = MOTION_STAND;
	m_PlayerYLocation = HORIZON_CHARACTER;
	m_PlayerXLocation = 0;
}


void Player::ChangeMotion(const int& State)
{
	m_PlayerMotion = State;
}

void Player::ChangeYLocation(bool IsUp)
{
	switch (IsUp)
	{
	case true:
		m_PlayerYLocation -= JUMP_LENGTH;
		break;
	case false:
		m_PlayerYLocation += JUMP_LENGTH;
		break;
	}
}

void Player::ChangeXLocation(const int& Key)
{
	switch (Key)
	{
	case VK_LEFT:
	{
		if (0 < m_PlayerXLocation)
		{
			m_PlayerXLocation -= MOVE_PIXEL;
		}
	}
		break;
	case VK_RIGHT:
	{
		m_PlayerXLocation += MOVE_PIXEL;
	}
		break;
	}
}