#include "Player.h"


void Player::InitPlayer()
{
	m_PlayerLife = PLAYER_LIFE;
	m_PlayerScore = 0;
	m_PlayerMotion = MOTION_STAND;
	m_PlayerYLocation = LOCATION_CHARACTER_HORIZON;
	m_PlayerXLocation = 0;
	m_PlayerDirection = DIRECTION_STAND;
}

void Player::DeadInit()
{
	m_PlayerMotion = MOTION_STAND;
	m_PlayerYLocation = LOCATION_CHARACTER_HORIZON;
	m_PlayerXLocation = 0;
	m_PlayerDirection = DIRECTION_STAND;
}

void Player::ChangeMotion(const int& State)
{
	m_PlayerMotion = State;

	if (MOTION_STAND == State)
		m_PlayerDirection = DIRECTION_STAND;
}

void Player::ChangeYLocation(bool IsUp)
{
	switch (IsUp)
	{
	case true:
		m_PlayerYLocation -= JUMP_PIXEL ;
		{
			if (JUMP_HEIGHT > m_PlayerYLocation)
				m_PlayerYLocation = JUMP_HEIGHT;
		}
		break;
	case false:
		m_PlayerYLocation += JUMP_PIXEL;
		{
			if (LOCATION_CHARACTER_HORIZON < m_PlayerYLocation)
				m_PlayerYLocation = LOCATION_CHARACTER_HORIZON;
		}
		break;
	}

	switch (m_PlayerDirection)
	{
	case DIRECTION_LEFT:
	case DIRECTION_RIGHT:
		ChangeXLocation(m_PlayerDirection);
		break;
	default:
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
			m_PlayerDirection = DIRECTION_LEFT;
		}
	}
		break;
	case VK_RIGHT:
	{
		m_PlayerXLocation += MOVE_PIXEL;
		m_PlayerDirection = DIRECTION_RIGHT;
	}
		break;
	}
}