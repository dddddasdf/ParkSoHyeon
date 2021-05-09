#include "Character.h"

void Character::Init()
{
	m_IsLeftLeg = true;
	m_IsNeutralFirst = true;
	m_CharacterLocationX = 600;
	m_CharacterLocationX = 300;
	m_CharacterDirection = DIRECTION_UP;
}


void Character::Standing(HDC hdc)
{
	if (m_IsNeutralFirst)
	{
		switch (m_CharacterDirection)
		{
		case DIRECTION_LEFT:
			BitMapMgr->PrintCharacter(hdc, GESTURE_LEFT_NEUTRAL1, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_RIGHT:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL1, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_UP:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL1, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_DOWN:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL1, m_CharacterLocationX, m_CharacterLocationY);
			break;
		}
	}
	else
	{
		switch (m_CharacterDirection)
		{
		case DIRECTION_LEFT:
			BitMapMgr->PrintCharacter(hdc, GESTURE_LEFT_NEUTRAL2, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_RIGHT:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL2, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_UP:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL2, m_CharacterLocationX, m_CharacterLocationY);
			break;
		case DIRECTION_DOWN:
			BitMapMgr->PrintCharacter(hdc, GESTURE_RIGHT_NEUTRAL2, m_CharacterLocationX, m_CharacterLocationY);
			break;
		}
	}
}

void Character::ChangeNeutral()
{
	m_IsNeutralFirst = !(m_IsNeutralFirst);
}

void Character::Moving(HDC hdc, int Direction)
{	
	m_CharacterDirection = Direction;
	
	switch (Direction)
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
	
	
	switch (m_IsLeftLeg)
	{
	case true:
		m_IsLeftLeg = false;
		break;
	case false:
		m_IsLeftLeg = true;
		break;
	}
}