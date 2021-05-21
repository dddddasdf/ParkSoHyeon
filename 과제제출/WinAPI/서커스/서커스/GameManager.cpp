#include "GameManager.h"

void GameManager::WholeInit()
{
	ResourceMgr->InitImages();
	m_PlayerData = new Player;
}

void GameManager::MovingCharacter(int Key)
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


}

void GameManager::JumpingCharacter()
{
	m_PlayerData->ChangeMotion(MOTION_JUMPING);
}

void GameManager::DrawCharacterOrder(HDC *hdc)
{
	DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterYLocation());
}