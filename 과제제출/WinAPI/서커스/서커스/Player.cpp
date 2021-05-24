#include "Player.h"


void Player::InitPlayer()
{
	m_PlayerLife = 4;
	m_PlayerScore = 0;
	m_PlayerMotion = MOTION_STAND;
	m_PlayerYLocation = 400;
}


void Player::ChangeMotion(const int& State)
{
	m_PlayerMotion = State;
}