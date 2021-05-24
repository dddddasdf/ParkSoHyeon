#include "GameManager.h"

void GameManager::WholeInit()
{
	ResourceMgr->InitImages();
	m_PlayerData = new Player;
	m_IsMoving = false;
}

void GameManager::MovingCharacter(const int& Key)
{
	switch (Key)
	{
	case VK_LEFT:
		m_PlayerData->ChangeMotion(MOTION_RUNNING);
		break;
	case VK_RIGHT:
		m_PlayerData->ChangeMotion(MOTION_RUNNING);
		break;
	}

	m_IsMoving = true;
}

void GameManager::JumpingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_JUMPING);
}

void GameManager::StandingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_STAND);

	m_IsMoving = false;
}

void GameManager::DrawCharacterOrder(HDC *hdc, HWND hWnd)
{
	DrawMgr->DrawImages(*hdc, hWnd, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterYLocation());
}