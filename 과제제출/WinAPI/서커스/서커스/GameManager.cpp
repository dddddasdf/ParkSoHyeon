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
		m_PlayerData->ChangeXLocation(Key);
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
	m_IsHighest�� ���� ���� �����Ѵ�. 
	false�� �� ���� ���������� �ø��� �ְ� ���� �����ϸ� m_IsHighest�� true�� ��ü�� ���� ���� ���������� ������
	���� ��ǥ�� �����ϸ� m_IsHighest�� false�� ������ m_IsJumping ���� false�� ���� ���� ���������� ĳ������ ����� ���ĵ����� ��ü�Ѵ�
	*/
	
	switch (m_IsHighest)
	{
	case false:
	{
		m_PlayerData->ChangeYLocation(true);
		if (JUMP_HEIGHT >= m_PlayerData->ReturnCharacterYLocation())
		{
			m_IsHighest = true;
		}
	}
		break;
	case true:
	{
		m_PlayerData->ChangeYLocation(false);
		if (HORIZON_CHARACTER <= m_PlayerData->ReturnCharacterYLocation())
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
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		switch (m_PlayerData->ReturnMotion())
		{
		case MOTION_JUMPING:
			m_PlayerData->ChangeMotion(MOTION_RUNNING);
			break;
		case MOTION_RUNNING:
			m_PlayerData->ChangeMotion(MOTION_JUMPING);
			break;
		}
	}
	else
		m_PlayerData->ChangeMotion(MOTION_STAND);

	/*
	���� ���ϱ� ����� �޸��� �߿��� ĳ���� ��������Ʈ 2, 3�� �����ư��鼭 ��������
	�ϴ� ������ ���ؼ� �̷��� �Ͽ���... ����� �ٲٴ� �Լ��� �� �Լ��� ȣ��Ǵ� ���� Ű�Է��� ���������� �̷������ �ִٸ� �ٸ� �޸��� �������
	���ٸ� ���ĵ�����
	*/

	m_IsMoving = false;
}

void GameManager::DrawCharacterOrder(HDC *hdc, HWND hWnd)
{
	DrawMgr->DrawImages(*hdc, m_PlayerData->ReturnMotion(), m_PlayerData->ReturnCharacterXLocation(), m_PlayerData->ReturnCharacterYLocation());
}