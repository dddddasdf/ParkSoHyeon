#include "GameManager.h"

void GameManager::WholeInit(HWND hWnd)
{
	ResourceMgr->InitImages();
	DrawMgr->Init(hWnd);
	m_PlayerData = new Player;
	m_IsMoving = false;
	m_IsHighest = false;
}

void GameManager::MovingCharacter(const int& Key)
{
	switch (Key)
	{
	case VK_LEFT:
	case VK_RIGHT:
		m_PlayerData->ChangeMotion(MOTION_RUNNING);
		m_IsMoving = true;
		break;
	}
}

void GameManager::JumpingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_JUMPING);

	m_IsJumping = true;
}

void GameManager::ChangeCharacterYLocation()
{
	/*
	m_IsHighest를 통해 고도를 조절한다. 
	false일 때 고도를 순차적으로 올리고 최고 고도에 도달하면 m_IsHighest를 true로 교체한 다음 고도를 순차적으로 내린다
	지평선 좌표에 도달하면 m_IsHighest를 false로 돌리고 m_IsJumping 또한 false로 돌린 다음 마지막으로 캐릭터의 모션을 스탠딩으로 교체한다
	*/
	
	switch (m_IsHighest)
	{
	case false:
	{
		m_PlayerData->ChangeYLocation(true);
		if (JUMP_HEIGHT == m_PlayerData->ReturnCharacterYLocation())
			m_IsHighest = true;
	}
		break;
	case true:
	{
		m_PlayerData->ChangeYLocation(false);
		if (HORIZON_HEIGHT == m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = false;
			m_IsJumping = false;
			StandingCharacter();
		}
	}
		break;
	}
}

void GameManager::StandingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_STAND);

	m_IsMoving = false;
}

void GameManager::DrawCharacterOrder(HDC *hdc, HWND hWnd)
{
	DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterYLocation());
}