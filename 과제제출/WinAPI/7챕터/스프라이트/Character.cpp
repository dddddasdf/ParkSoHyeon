#include "Character.h"

void Character::Init()
{
	m_IsLeftLeg = true;
	m_IsNeutralFirst = true;
	m_CharacterLocationX = 600;
	m_CharacterLocationY = 300;
	m_CharacterDirection = DIRECTION_DOWN;
	m_CharacterGesture = GESTURE_FRONT_NEUTRAL1;
}


void Character::Moving(int Direction)
{	
	switch (Direction)
	{
	case VK_LEFT:
		m_CharacterDirection = DIRECTION_LEFT;
		m_CharacterLocationX -= MOVING_PIXEL;
		break;
	case VK_RIGHT:
		m_CharacterDirection = DIRECTION_RIGHT;
		m_CharacterLocationX += MOVING_PIXEL;
		break;
	case VK_UP:
		m_CharacterDirection = DIRECTION_UP;
		m_CharacterLocationY -= MOVING_PIXEL;
		break;
	case VK_DOWN:
		m_CharacterDirection = DIRECTION_DOWN;
		m_CharacterLocationY += MOVING_PIXEL;
		break;
	}
	
	//m_CharacterDirection = Direction;
	m_CharacterGesture = (m_CharacterGesture + 1) % CHARACTER_MAX_GESTURE;

	/*switch (Direction)
	{
	case DIRECTION_LEFT:
		m_CharacterLocationX -= MOVING_PIXEL;
		break;
	case DIRECTION_RIGHT:
		m_CharacterLocationX += MOVING_PIXEL;
		break;
	case DIRECTION_UP:
		m_CharacterLocationY -= MOVING_PIXEL;
		break;
	case DIRECTION_DOWN:
		m_CharacterLocationY += MOVING_PIXEL;
		break;
	}*/

	//PrintCharacter(hdc);
	//m_CharacterGesture = (m_CharacterGesture + 1) % CHARACTER_MAX_GESTURE;
	//PrintCharacter(hdc);
}

void Character::ChangeDirection(int Direction)
{
	switch (Direction)
	{
	case VK_LEFT:
		m_CharacterDirection = DIRECTION_LEFT;
		break;
	case VK_RIGHT:
		m_CharacterDirection = DIRECTION_RIGHT;
		break;
	case VK_UP:
		m_CharacterDirection = DIRECTION_UP;
		break;
	case VK_DOWN:
		m_CharacterDirection = DIRECTION_DOWN;
		break;
	}
}

void Character::ChangeLocation()
{
	switch (m_CharacterDirection)
	{
	case DIRECTION_LEFT:
		m_CharacterLocationX -= MOVING_PIXEL;
		break;
	case DIRECTION_RIGHT:
		m_CharacterLocationX += MOVING_PIXEL;
		break;
	case DIRECTION_UP:
		m_CharacterLocationY -= MOVING_PIXEL;
		break;
	case DIRECTION_DOWN:
		m_CharacterLocationY += MOVING_PIXEL;
		break;
	}
}

void Character::ChangeGesture()
{
	m_CharacterGesture = (m_CharacterGesture + 1) % CHARACTER_MAX_GESTURE;
}


void Character::PrintCharacter(HDC *hdc)
{
	BitMapMgr->PrintBitMap(*hdc, m_CharacterDirection, m_CharacterGesture, m_CharacterLocationX, m_CharacterLocationY);
}


/*
서있는 거 전부 같은 도트더라
숨쉬기 작업할 필요 없었다고



*/